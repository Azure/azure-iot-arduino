// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <time.h>
#include <sys/time.h>

#include <RTCZero.h>

RTCZero rtc;

extern "C" {
    int _gettimeofday(struct timeval* tp, void* /*tzvp*/)
    {
        struct tm tm;

        tm.tm_isdst = -1;
        tm.tm_yday = 0;
        tm.tm_wday = 0;
        tm.tm_year = rtc.getYear() + 100;
        tm.tm_mon = rtc.getMonth() + 1;
        tm.tm_mday = rtc.getDay();
        tm.tm_hour = rtc.getHours();
        tm.tm_min = rtc.getMinutes();
        tm.tm_sec = rtc.getSeconds();

        tp->tv_sec = mktime(&tm);
        tp->tv_usec = 0;

        return 0;
    }

    int settimeofday(const struct timeval* tp, const struct timezone* /*tzp*/)
    {
        struct tm* tmp = gmtime(&tp->tv_sec);

        rtc.begin();
        rtc.setDate(tmp->tm_mday, tmp->tm_mon - 1, tmp->tm_year - 100);
        rtc.setTime(tmp->tm_hour, tmp->tm_min, tmp->tm_sec);

        return 0;
    }
}
