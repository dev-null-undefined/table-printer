#include "string_array.h"
#include "options.h"
#ifndef TABLE_PRINTER_STRING_TABLE_H
#define TABLE_PRINTER_STRING_TABLE_H

typedef struct {
    string_array_t **string;
    int length;
    int capacity;
    int width;
    int *max_column_length;
}string_table_t;

string_table_t *create_string_table(int width);

void recalculate_max_column_length(string_table_t *string_table, string_array_t *new_row);

void add_row_to_table(string_table_t *string_table, string_array_t *new_row);

void print_table(string_table_t *string_table, options_t *option);
#endif
