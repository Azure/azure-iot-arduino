#if defined(ARDUINO_ARCH_ESP8266)
#include "azcpgmspace.h"

char* az_c_strncpy_P(char* dest, PGM_P src, size_t size) {
    return strncpy_P(dest, src, size);
}

size_t az_c_strlen_P(PGM_P s) {
    return strlen_P(s);
}
#endif