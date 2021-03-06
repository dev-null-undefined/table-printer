#include "custom_string.h"
#include <stdlib.h>
#include <string.h>

string_t *string_new(char *chars, int buffer_size) {
    string_t *string = (string_t *) malloc(sizeof(string_t));
    string->chars = (char *) malloc(buffer_size * sizeof(char));
    strncpy(string->chars, chars, buffer_size);
    string->length = (int) strlen(chars);
    string->capacity = buffer_size;
    string->char_count = 0;
    string->chars[0] = 0;
    return string;
}

string_t *string_new_empty(int buffer_size) {
    string_t *string = (string_t *) malloc(sizeof(string_t));
    string->chars = (char *) malloc(buffer_size * sizeof(char));
    string->length = 0;
    string->capacity = buffer_size;
    string->char_count = 0;
    string->chars[0] = 0;
    return string;
}


void string_append(string_t *string, char *c, int length) {
    while (string->length + 1 + length > string->capacity) {
        string->capacity *= 2;
        string->chars = (char *) realloc(string->chars, sizeof(*string->chars) * string->capacity);
    }
    for (int i = 0; i < length; ++i) {
        string->chars[string->length] = (char) *c;
        string->length++;
        c++;
    }
    string->char_count++;
    string->chars[string->length] = '\0';
}

void string_free(string_t *string) {
    free(string->chars);
    free(string);
}
