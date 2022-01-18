#ifndef TABLE_PRINTER_CUSTOM_STRING_H
#define TABLE_PRINTER_CUSTOM_STRING_H
typedef struct {
    char *chars;
    int char_count;
    int length;
    // -1 meaning not dynamic
    int capacity;
} string_t;

string_t *string_new(char *chars, int buffer_size);

string_t *string_new_empty(int buffer_size);

void string_append(string_t *string, char *c, int length);

void string_free(string_t *string);

#endif
