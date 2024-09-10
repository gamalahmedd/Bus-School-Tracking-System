#ifndef STRING_FIND_H_
#define STRING_FIND_H_
#include <string.h>

unsigned char find_string(const char *string, const char* string_find);
void find_get_string(const char *string, const char* from, const char _from, const char* to, const char _to, char *get_text);

#endif