#ifndef TABLE_PRINTER_CUSTOM_STRING_H
#define TABLE_PRINTER_CUSTOM_STRING_H
typedef struct {
    char *chars;
    int length;
    // -1 meaning not dynamic
    int capacity;
} string_t;

string_t *create_string(char *chars, int buffer_size);

string_t *create_string_empty(int buffer_size);

void append_char_to_string(string_t *string, char c);

void free_string(string_t *string);

#endif
