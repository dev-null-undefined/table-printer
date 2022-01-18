#include "custom_string.h"

#ifndef TABLE_PRINTER_STRING_ARRAY_H
#define TABLE_PRINTER_STRING_ARRAY_H

typedef struct {
    string_t **strings;
    int length;
    int capacity;
} string_array_t;

string_array_t *string_array_new(int capacity);

void string_array_add(string_array_t *string_array, string_t *string);

void string_array_free(string_array_t *array);

#endif
