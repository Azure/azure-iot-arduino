#include <stdio.h>
#define STRINGIFY(a) (#a)

/*
ESP8266 has limited RAM so we force all logging strings to PROGMEM (flash)
and we leverage os_printf rather than printf.

Time inclusion in errors is possible if NTP was successful, and can be added
in a later revision.
*/

#if defined(ARDUINO_ARCH_ESP8266)
#include <pgmspace.h>
#define LogUsage(FORMAT, ...) (void)os_printf(PSTR(FORMAT), ##__VA_ARGS__);
#define LogInfo(FORMAT, ...) (void)os_printf(PSTR(FORMAT), ##__VA_ARGS__);
#define LogError(FORMAT, ...) (void)os_printf(PSTR(FORMAT), ##__VA_ARGS__);
#elif defined(ARDUINO_ARCH_SAMD)
#define LogUsage (void)printf
#define LogInfo(...) (void)printf("Info: " __VA_ARGS__)
#if defined _MSC_VER
#define LogError(FORMAT, ...) { time_t t = time(NULL); (void)fprintf(stderr,"Error: Time:%.24s File:%s Func:%s Line:%d " FORMAT, ctime(&t), __FILE__, __FUNCDNAME__, __LINE__, __VA_ARGS__); }
#else
#define LogError(FORMAT, ...) { time_t t = time(NULL); (void)fprintf(stderr,"Error: Time:%.24s File:%s Func:%s Line:%d " FORMAT, ctime(&t), __FILE__, __func__, __LINE__, ##__VA_ARGS__); }
#endif
#endif



