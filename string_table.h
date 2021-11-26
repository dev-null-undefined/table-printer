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

string_table_t *create_string_table(int width);

string_table_t *get_string_table(options_t *options);

void recalculate_max_column_length(string_table_t *string_table, string_array_t *new_row);

void add_row_to_table(string_table_t *string_table, string_array_t *new_row);

void print_table(string_table_t *string_table, options_t *option);

void print_separator(int counter_length, const int max_column_length[], int width, options_t *options);

void print_aligned_string(const char *format, void *data, int padding, int align_left, options_t *options);

void set_console_color(int color, options_t *options);

void free_string_table(string_table_t *table);

void rotate_color(int *color, int color_count, options_t *options);

void set_frame_color(options_t *options);

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