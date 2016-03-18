#include <stdio.h>
#define STRINGIFY(a) (#a)

/*
ESP8266 has limited RAM so we force all logging strings to PROGMEM (flash)
and we leverage os_printf rather than printf.

Time inclusion in errors is possible if NTP was successful, and can be added
in a later revision.
*/

#if defined(ARDUINO_ARCH_ESP8266)
#include "esp8266/azcpgmspace.h"
#define LogUsage(FORMAT, ...) { \
        const char* __localFORMAT = PSTR(FORMAT); \
        size_t __localFORMATSIZE = az_c_strlen_P(__localFORMAT) + 1; \
        char* __localREALSTR = (char*)malloc(__localFORMATSIZE * sizeof(char)); \
        __localREALSTR[__localFORMATSIZE-1] = '\0'; \
        az_c_strncpy_P(__localREALSTR, __localFORMAT, __localFORMATSIZE); \
        os_printf(__localREALSTR, ##__VA_ARGS__); \
        free(__localREALSTR); \
}
#define LogInfo(FORMAT, ...) { \
        const char* __localFORMAT = PSTR(FORMAT); \
        size_t __localFORMATSIZE = az_c_strlen_P(__localFORMAT) + 1; \
        char* __localREALSTR = (char*)malloc(__localFORMATSIZE * sizeof(char)); \
        __localREALSTR[__localFORMATSIZE-1] = '\0'; \
        az_c_strncpy_P(__localREALSTR, __localFORMAT, __localFORMATSIZE); \
        os_printf(__localREALSTR, ##__VA_ARGS__); \
        free(__localREALSTR); \
}

#define LogError(FORMAT, ...) { \
        const char* __localFORMAT = PSTR(FORMAT); \
        size_t __localFORMATSIZE = az_c_strlen_P(__localFORMAT) + 1; \
        char* __localREALSTR = (char*)malloc(__localFORMATSIZE * sizeof(char)); \
        __localREALSTR[__localFORMATSIZE-1] = '\0'; \
        az_c_strncpy_P(__localREALSTR, __localFORMAT, __localFORMATSIZE); \
        os_printf(__localREALSTR, ##__VA_ARGS__); \
        free(__localREALSTR); \
}

#elif defined(ARDUINO_ARCH_SAMD)
#define LogUsage (void)printf
#define LogInfo(...) (void)printf("Info: " __VA_ARGS__)
#if defined _MSC_VER
#define LogError(FORMAT, ...) { time_t t = time(NULL); (void)fprintf(stderr,"Error: Time:%.24s File:%s Func:%s Line:%d " FORMAT, ctime(&t), __FILE__, __FUNCDNAME__, __LINE__, __VA_ARGS__); }
#else
#define LogError(FORMAT, ...) { time_t t = time(NULL); (void)fprintf(stderr,"Error: Time:%.24s File:%s Func:%s Line:%d " FORMAT, ctime(&t), __FILE__, __func__, __LINE__, ##__VA_ARGS__); }
#endif
#endif



