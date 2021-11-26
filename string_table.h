#include "string_array.h"
#include "options.h"

#ifndef TABLE_PRINTER_STRING_TABLE_H
#define TABLE_PRINTER_STRING_TABLE_H
#define TABLE_FRAME_SEPARATOR "|"

typedef struct {
    string_array_t **string;
    int length;
    int capacity;
    int width;
    int *max_column_length;
} string_table_t;

string_table_t *create_string_table(int width);

void recalculate_max_column_length(string_table_t *string_table, string_array_t *new_row);

void add_row_to_table(string_table_t *string_table, string_array_t *new_row);

void print_table(string_table_t *string_table, options_t *option);

void print_aligned_string(const char *format,void *data,int padding,int align_left);

void set_console_color(int color);

enum COLORS
{
    BLUE = 0,
    GREEN = 1,
    CYAN = 2,
    RED = 3,
    YELLOW = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHTBLUE = 7,
    LIGHTCYAN = 8,
    LIGHTRED = 9,
    LIGHTMAGENTA = 10,
    WHITE = 14,
    BLACK = 15,
    BLINK = 128,
    RESET = 256,
};

#endif
