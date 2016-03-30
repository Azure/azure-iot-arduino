// Copyright (c) Attunix. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <Arduino.h>
#include <time.h>

#ifdef ARDUINO
#include "AzureIoT.h"
#else
#include "serializer.h"
#include "iothub_client_ll.h"
#include "iothubtransporthttp.h"
#include "threadapi.h"
#endif

#include "rem_ctrl_http.h"


static char connectionString[MAX_CONNECTION_STRING_LEN + 1];
static int redLedPin = 12;
static int greenLedPin = 11;
char buff[11];
int timeNow = 0;

// Define the Model
BEGIN_NAMESPACE(RemoteMonitorExample);

DECLARE_MODEL(
  BME280_data
, WITH_DATA(ascii_char_ptr, DeviceId)
, WITH_DATA(ascii_char_ptr, EventTime)
, WITH_DATA(float, MTemperature) // Celcius
, WITH_DATA(float, Humidity) // Relative percent
, WITH_DATA(float, Pressure) // hPa
, WITH_ACTION(TurnFanOn)
, WITH_ACTION(TurnFanOff)
);

END_NAMESPACE(RemoteMonitorExample);
BME280_data* myWeather = NULL;
IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle = NULL;

DEFINE_ENUM_STRINGS(IOTHUB_CLIENT_CONFIRMATION_RESULT, IOTHUB_CLIENT_CONFIRMATION_RESULT_VALUES);

EXECUTE_COMMAND_RESULT TurnFanOn(BME280_data* device)
{
    (void)device;
    (void)printf("Turning Green LED on.\r\n");
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    return EXECUTE_COMMAND_SUCCESS;
}

EXECUTE_COMMAND_RESULT TurnFanOff(BME280_data* device)
{
    (void)device;
    (void)printf("Turning red LED on.\r\n");
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    return EXECUTE_COMMAND_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
bool rem_ctrl_set_connection_string(const char * Connection_string__cp)
{
  size_t Len = strlen(Connection_string__cp);
  if (Len > MAX_CONNECTION_STRING_LEN) return false;

  strcpy(connectionString, Connection_string__cp);

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void sendCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void* userContextCallback)
{
    int messageTrackingId = (intptr_t)userContextCallback;

    (void)printf("Message Id: %d Received.\r\n", messageTrackingId);

    (void)printf("Result Call Back Called! Result is: %s \r\n", ENUM_TO_STRING(IOTHUB_CLIENT_CONFIRMATION_RESULT, result));
}

///////////////////////////////////////////////////////////////////////////////////////////////////
static void sendMessage(IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle, const unsigned char* buffer, size_t size)
{
    static unsigned int messageTrackingId;
    IOTHUB_MESSAGE_HANDLE messageHandle = IoTHubMessage_CreateFromByteArray(buffer, size);
    if (messageHandle == NULL)
    {
        printf("unable to create a new IoTHubMessage\r\n");
    }
    else
    {
        if (IoTHubClient_LL_SendEventAsync(iotHubClientHandle, messageHandle, sendCallback, (void*)(uintptr_t)messageTrackingId) != IOTHUB_CLIENT_OK)
        {
            printf("failed to hand over the message to IoTHubClient");
        }
        else
        {
            printf("IoTHubClient accepted the message for delivery\r\n");
        }
        IoTHubMessage_Destroy(messageHandle);
    }
    free((void*)buffer);
    messageTrackingId++;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// This function "links" IoTHub to the serialization library.
static IOTHUBMESSAGE_DISPOSITION_RESULT IoTHubMessage(IOTHUB_MESSAGE_HANDLE message, void* userContextCallback)
{
    IOTHUBMESSAGE_DISPOSITION_RESULT result;
    const unsigned char* buffer;
    size_t size;
    if (IoTHubMessage_GetByteArray(message, &buffer, &size) != IOTHUB_MESSAGE_OK)
    {
        printf("unable to IoTHubMessage_GetByteArray\r\n");
        result = EXECUTE_COMMAND_ERROR;
    }
    else
    {
        // Buffer is not zero terminated
        char* temp = malloc(size + 1);
        if (temp == NULL)
        {
            printf("failed to malloc\r\n");
            result = EXECUTE_COMMAND_ERROR;
        }
        else
        {
            memcpy(temp, buffer, size);
            temp[size] = '\0';
            EXECUTE_COMMAND_RESULT executeCommandResult = EXECUTE_COMMAND(userContextCallback, temp);
            result =
                (executeCommandResult == EXECUTE_COMMAND_ERROR) ? IOTHUBMESSAGE_ABANDONED :
                (executeCommandResult == EXECUTE_COMMAND_SUCCESS) ? IOTHUBMESSAGE_ACCEPTED :
                IOTHUBMESSAGE_REJECTED;
            free(temp);
        }
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
int Init_level__i = 0;
int rem_ctrl_http_init(void)
{
    digitalWrite(redLedPin, LOW);
    pinMode(redLedPin, OUTPUT);
    
    digitalWrite(greenLedPin, LOW);
    pinMode(greenLedPin, OUTPUT);
    
    if (serializer_init(NULL) != SERIALIZER_OK)
    {
        (void)printf("Failed on serializer_init\r\n");
    }
    else
    {
        Init_level__i = 1;

        iotHubClientHandle = IoTHubClient_LL_CreateFromConnectionString(connectionString, HTTP_Protocol);
        if (iotHubClientHandle == NULL)
        {
            (void)printf("Failed on IoTHubClient_LL_Create\r\n");
        }
        else
        {
            Init_level__i = 2;
            
            unsigned int minimumPollingTime = 9; // Because it can poll "after 9 seconds" polls will happen effectively at ~10 seconds.
            if (IoTHubClient_LL_SetOption(iotHubClientHandle, "MinimumPollingTime", &minimumPollingTime) != IOTHUB_CLIENT_OK)
            {
                printf("failure to set option \"MinimumPollingTime\"\r\n");
            }

            myWeather = CREATE_MODEL_INSTANCE(RemoteMonitorExample, BME280_data);
            if (myWeather == NULL)
            {
                (void)printf("Failed on CREATE_MODEL_INSTANCE\r\n");
            }
            else
            {
                Init_level__i = 3;

                if (IoTHubClient_LL_SetMessageCallback(iotHubClientHandle, IoTHubMessage, myWeather) != IOTHUB_CLIENT_OK)
                {
                    printf("unable to IoTHubClient_SetMessageCallback\r\n");
                }
                else
                {
                    Init_level__i = 4;
                }
            }
        }
    }

    return Init_level__i;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void rem_ctrl_http_deinit(void)
{
    if (Init_level__i >= 3) {
        DESTROY_MODEL_INSTANCE(myWeather);
        myWeather = NULL;
        Init_level__i = 2;
    }

    if (Init_level__i >= 2) {
        IoTHubClient_LL_Destroy(iotHubClientHandle);
        iotHubClientHandle = NULL;
        Init_level__i = 1;
    }

    if (Init_level__i >= 1) {
        serializer_deinit();
        Init_level__i = 0;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void rem_ctrl_http_send_data(float Temp_c__f, float Pres_hPa__f, float Humi_pct__f)
{
    // Don't run this function unless the initialization succeeded.
    if (Init_level__i < 4) return;

    timeNow = (int)time(NULL);
    sprintf(buff, "%d", timeNow);
    
    myWeather->DeviceId = "FeatherM0_w_BME280";
    myWeather->MTemperature = Temp_c__f;
    myWeather->Pressure = Pres_hPa__f;
    myWeather->Humidity = Humi_pct__f;
    myWeather->EventTime = timeNow;
    
    unsigned char* destination;
    size_t destinationSize;
    if (SERIALIZE(&destination, &destinationSize, myWeather->DeviceId, myWeather->EventTime, myWeather->MTemperature, myWeather->Pressure, myWeather->Humidity) != IOT_AGENT_OK)
    {
        (void)printf("Failed to serialize\r\n");
    }
    else
    {
        IOTHUB_MESSAGE_HANDLE messageHandle = IoTHubMessage_CreateFromByteArray(destination, destinationSize);
        if (messageHandle == NULL)
        {
            printf("unable to create a new IoTHubMessage\r\n");
        }
        else
        {
            if (IoTHubClient_LL_SendEventAsync(iotHubClientHandle, messageHandle, sendCallback, (void*)1) != IOTHUB_CLIENT_OK)
            {
                printf("failed to hand over the message to IoTHubClient");
            }
            else
            {
                printf("IoTHubClient accepted the message for delivery\r\n");
            }
    
            IoTHubMessage_Destroy(messageHandle);
        }
        free(destination);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void rem_ctrl_http_run(void)
{
    IoTHubClient_LL_DoWork(iotHubClientHandle);
}


