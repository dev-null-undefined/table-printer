#include "custom_string.h"
#ifndef TABLE_PRINTER_STRING_ARRAY_H
#define TABLE_PRINTER_STRING_ARRAY_H

typedef struct {
    string_t **strings;
    int length;
    int capacity;
} string_array_t;

string_array_t *create_string_array(int capacity);

void add_string_to_array(string_array_t *string_array, string_t *string);

void free_string_array(string_array_t *array);

#endif
