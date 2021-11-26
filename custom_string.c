#include "custom_string.h"
#include <stdlib.h>
#include <string.h>

string_t *create_string(char *chars, int buffer_size) {
    string_t *string = (string_t *) malloc(sizeof(string_t));
    string->chars = chars;
    string->length = (int) strlen(chars);
    string->capacity = buffer_size;
    return string;
}

string_t *create_string_empty(int buffer_size) {
    string_t *string = (string_t *) malloc(sizeof(string_t));
    string->chars = (char *) malloc(buffer_size * sizeof(char));
    string->length = 0;
    string->capacity = buffer_size;
    return string;
}


void append_char_to_string(string_t *string, char c) {
    if (string->length + 2 > string->capacity) {
        string->capacity *= 2;
        string->chars = (char *) realloc(string->chars, sizeof(*string->chars) * string->capacity);
    }
    string->chars[string->length] = c;
    string->length++;
    string->chars[string->length] = '\0';
}