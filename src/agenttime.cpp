#include "sdk/agenttime.h"
#include "sdk/iot_logging.h"

#include "util/NTPClient.h"

#define NTP_RETRY_COUNT 5
#define MAX_CACHE_DELTA 60

long epochTimeFetch = 0;
uint32_t epochTime = (time_t)-1;

time_t get_time(time_t* currentTime)
{
    NTPClient ntpClient;

    if (epochTime == (time_t)-1 || (((millis() - epochTimeFetch) / 1000) > MAX_CACHE_DELTA)) {
        ntpClient.begin();
        for (int i = 0; (i < NTP_RETRY_COUNT) && (epochTime == (uint32_t)-1); i++) {
            epochTime = ntpClient.getEpochTime("0.pool.ntp.org");

            if (epochTime == (uint32_t)-1) {
                LogError("Fetching NTP epoch time failed, attempt: %d/%d\n", i, NTP_RETRY_COUNT);
            } else {
                LogInfo("epoch time is: %lu\n", epochTime);
            }
        }
        ntpClient.end();

        epochTimeFetch = millis();
    } else {
        epochTime += ((millis() - epochTimeFetch) / 1000);
    }

    if (currentTime) {
        *currentTime = epochTime;
    }

    return epochTime;
}

double get_difftime(time_t stopTime, time_t startTime)
{
    return difftime(stopTime, startTime);
}

struct tm* get_gmtime(time_t* currentTime)
{
    return localtime(currentTime);
}

char* get_ctime(time_t* timeToGet)
{
    return ctime(timeToGet);
}
