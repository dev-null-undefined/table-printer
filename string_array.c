#include "string_array.h"
#include <stdlib.h>

string_array_t *create_string_array(int capacity) {
    string_array_t *string_array = (string_array_t *) malloc(sizeof(string_array_t));
    string_array->strings = (string_t **) malloc(sizeof(string_t *) * capacity);
    string_array->length = 0;
    string_array->capacity = capacity;
    return string_array;
}

void add_string_to_array(string_array_t *string_array, string_t *string) {
    if (string_array->length + 1 > string_array->capacity) {
        string_array->capacity *= 2;
        string_array->strings = (string_t **) realloc(string_array->strings, sizeof(*string_array->strings)*string_array->capacity);
    }
    string_array->strings[string_array->length] = string;
    string_array->length++;
}

void free_string_array(string_array_t *array){
    for (int i = 0; i < array->length; ++i){
        free_string(array->strings[i]);
    }
    free(array->strings);
    free(array);
}