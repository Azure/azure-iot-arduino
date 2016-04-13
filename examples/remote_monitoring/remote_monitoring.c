// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "AzureIoTHub.h"
#include "sdk/schemaserializer.h"
#include "bme280.h"


static const char* deviceId = "[device-id]";
static const char* deviceKey = "[device-key]";
static const char* hubName = "[hub-name]";
static const char* hubSuffix = "azure-devices.net";

// Define the Model
BEGIN_NAMESPACE(Contoso);

DECLARE_STRUCT(SystemProperties,
    ascii_char_ptr, DeviceID,
    _Bool, Enabled
);

DECLARE_STRUCT(DeviceProperties,
ascii_char_ptr, DeviceID,
_Bool, HubEnabledState
);

DECLARE_MODEL(Thermostat,

    /* Event data (temperature, external temperature and humidity) */
    WITH_DATA(int, Temperature),
    WITH_DATA(int, ExternalTemperature),
    WITH_DATA(int, Humidity),
    WITH_DATA(ascii_char_ptr, DeviceId),

    /* Device Info - This is command metadata + some extra fields */
    WITH_DATA(ascii_char_ptr, ObjectType),
    WITH_DATA(_Bool, IsSimulatedDevice),
    WITH_DATA(ascii_char_ptr, Version),
    WITH_DATA(DeviceProperties, DeviceProperties),
    WITH_DATA(ascii_char_ptr_no_quotes, Commands),

    /* Commands implemented by the device */
    WITH_ACTION(SetTemperature, int, temperature),
    WITH_ACTION(SetHumidity, int, humidity)
);

END_NAMESPACE(Contoso);

EXECUTE_COMMAND_RESULT SetTemperature(Thermostat* thermostat, int temperature)
{
    LogInfo("Received temperature %d\r\n", temperature);
    thermostat->Temperature = temperature;
    return EXECUTE_COMMAND_SUCCESS;
}

EXECUTE_COMMAND_RESULT SetHumidity(Thermostat* thermostat, int humidity)
{
    LogInfo("Received humidity %d\r\n", humidity);
    thermostat->Humidity = humidity;
    return EXECUTE_COMMAND_SUCCESS;
}

static void sendMessage(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, const unsigned char* buffer, size_t size)
{
    IOTHUB_MESSAGE_HANDLE messageHandle = IoTHubMessage_CreateFromByteArray(buffer, size);
    if (messageHandle == NULL)
    {
        LogInfo("unable to create a new IoTHubMessage\r\n");
    }
    else
    {
        if (IoTHubClient_LL_SendEventAsync(iotHubClientHandle, messageHandle, NULL, NULL) != IOTHUB_CLIENT_OK)
        {
            LogInfo("failed to hand over the message to IoTHubClient");
        }
        else
        {
            LogInfo("IoTHubClient accepted the message for delivery\r\n");
        }

        IoTHubMessage_Destroy(messageHandle);
    }
    free((void*)buffer);
}

/*this function "links" IoTHub to the serialization library*/
static IOTHUBMESSAGE_DISPOSITION_RESULT IoTHubMessage(IOTHUB_MESSAGE_HANDLE message, void* userContextCallback)
{
    IOTHUBMESSAGE_DISPOSITION_RESULT result;
    const unsigned char* buffer;
    size_t size;
    if (IoTHubMessage_GetByteArray(message, &buffer, &size) != IOTHUB_MESSAGE_OK)
    {
        LogInfo("unable to IoTHubMessage_GetByteArray\r\n");
        result = EXECUTE_COMMAND_ERROR;
    }
    else
    {
        /*buffer is not zero terminated*/
        char* temp = malloc(size + 1);
        if (temp == NULL)
        {
            LogInfo("failed to malloc\r\n");
            result = EXECUTE_COMMAND_ERROR;
        }
        else
        {
            EXECUTE_COMMAND_RESULT executeCommandResult;

            memcpy(temp, buffer, size);
            temp[size] = '\0';
            executeCommandResult = EXECUTE_COMMAND(userContextCallback, temp);
            result =
                (executeCommandResult == EXECUTE_COMMAND_ERROR) ? IOTHUBMESSAGE_ABANDONED :
                (executeCommandResult == EXECUTE_COMMAND_SUCCESS) ? IOTHUBMESSAGE_ACCEPTED :
                IOTHUBMESSAGE_REJECTED;
            free(temp);
        }
    }
    return result;
}

void remote_monitoring_run(void)
{
        initBme();

        srand((unsigned int)time(NULL));
        if (serializer_init(NULL) != SERIALIZER_OK)
        {
            LogInfo("Failed on serializer_init\r\n");
        }
        else
        {
            IOTHUB_CLIENT_CONFIG config;
            IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle;

            config.deviceId = deviceId;
            config.deviceKey = deviceKey;
            config.iotHubName = hubName;
            config.iotHubSuffix = hubSuffix;
            config.protocol = HTTP_Protocol;

            iotHubClientHandle = IoTHubClient_LL_Create(&config);
            if (iotHubClientHandle == NULL)
            {
                LogInfo("Failed on IoTHubClient_CreateFromConnectionString\r\n");
            }
            else
            {
#ifdef MBED_BUILD_TIMESTAMP
                // For mbed add the certificate information
                if (IoTHubClient_LL_SetOption(iotHubClientHandle, "TrustedCerts", certificates) != IOTHUB_CLIENT_OK)
                {
                    LogInfo("failure to set option \"TrustedCerts\"\r\n");
                }
#endif // MBED_BUILD_TIMESTAMP

                Thermostat* thermostat = CREATE_MODEL_INSTANCE(Contoso, Thermostat);
                if (thermostat == NULL)
                {
                    LogInfo("Failed on CREATE_MODEL_INSTANCE\r\n");
                }
                else
                {
                    STRING_HANDLE commandsMetadata;

                    if (IoTHubClient_LL_SetMessageCallback(iotHubClientHandle, IoTHubMessage, thermostat) != IOTHUB_CLIENT_OK)
                    {
                        LogInfo("unable to IoTHubClient_SetMessageCallback\r\n");
                    }
                    else
                    {

                        /* send the device info upon startup so that the cloud app knows
                        what commands are available and the fact that the device is up */
                        thermostat->ObjectType = "DeviceInfo";
                        thermostat->IsSimulatedDevice = false;
                        thermostat->Version = "1.0";
                        thermostat->DeviceProperties.HubEnabledState = true;
                        thermostat->DeviceProperties.DeviceID = (char*)deviceId;

                        commandsMetadata = STRING_new();
                        if (commandsMetadata == NULL)
                        {
                            LogInfo("Failed on creating string for commands metadata\r\n");
                        }
                        else
                        {
                            /* Serialize the commands metadata as a JSON string before sending */
                            if (SchemaSerializer_SerializeCommandMetadata(GET_MODEL_HANDLE(Contoso, Thermostat), commandsMetadata) != SCHEMA_SERIALIZER_OK)
                            {
                                LogInfo("Failed serializing commands metadata\r\n");
                            }
                            else
                            {
                                unsigned char* buffer;
                                size_t bufferSize;
                                thermostat->Commands = (char*)STRING_c_str(commandsMetadata);

                                /* Here is the actual send of the Device Info */
                                if (SERIALIZE(&buffer, &bufferSize, thermostat->ObjectType, thermostat->Version, thermostat->IsSimulatedDevice, thermostat->DeviceProperties, thermostat->Commands) != IOT_AGENT_OK)
                                {
                                    LogInfo("Failed serializing\r\n");
                                }
                                else
                                {
                                    sendMessage(iotHubClientHandle, buffer, bufferSize);
                                }

                            }

                            STRING_delete(commandsMetadata);
                        }

                        thermostat->DeviceId = (char*)deviceId;
                        int sendCycle = 10;
                        int currentCycle = 0;
                        while (1)
                        {
                            if(currentCycle >= sendCycle) {
                                float Temp;
                                float Humi;
                                getNextSample(&Temp, &Humi);
                                //thermostat->Temperature = 50 + (rand() % 10 + 2);
                                thermostat->Temperature = (int)round(Temp);
                                thermostat->ExternalTemperature = 55 + (rand() % 5 + 2);
                                //thermostat->Humidity = 50 + (rand() % 8 + 2);
                                thermostat->Humidity = (int)round(Humi);
                                currentCycle = 0;
                                unsigned char*buffer;
                                size_t bufferSize;

                                LogInfo("Sending sensor value Temperature = %d, Humidity = %d\r\n", thermostat->Temperature, thermostat->Humidity);

                                if (SERIALIZE(&buffer, &bufferSize, thermostat->DeviceId, thermostat->Temperature, thermostat->Humidity, thermostat->ExternalTemperature) != IOT_AGENT_OK)
                                {
                                    LogInfo("Failed sending sensor value\r\n");
                                }
                                else
                                {
                                    sendMessage(iotHubClientHandle, buffer, bufferSize);
                                }
                            }

                            IoTHubClient_LL_DoWork(iotHubClientHandle);
                            ThreadAPI_Sleep(100);
                            currentCycle++;
                        }
                    }

                    DESTROY_MODEL_INSTANCE(thermostat);
                }
                IoTHubClient_LL_Destroy(iotHubClientHandle);
            }
            serializer_deinit();

    }
}
