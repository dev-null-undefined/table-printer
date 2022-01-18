#include "string_array.h"
#include "options.h"

#ifndef TABLE_PRINTER_STRING_TABLE_H
#define TABLE_PRINTER_STRING_TABLE_H
#define TABLE_FRAME_SEPARATOR "|"

typedef struct {
    string_array_t **rows;
    int length;
    int capacity;
    int width;
    int *max_column_length;
} string_table_t;

string_table_t *string_table_new(int width);

string_table_t *string_table_create(options_t *options);

void string_table_recalculate(string_table_t *string_table, string_array_t *new_row);

void string_table_add_row(string_table_t *string_table, string_array_t *new_row);

void string_table_print(string_table_t *string_table, options_t *option);

void set_console_color(int color, options_t *options);

void string_table_free(string_table_t *table);

void rotate_color(int *color, int color_count, options_t *options);

void reset_console_color(options_t *options);

#define COLOR_COUNT 10

enum COLORS {
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
