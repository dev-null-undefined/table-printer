#include "string_table.h"
#include <stdlib.h>
#include <stdio.h>

string_table_t *create_string_table(int width) {
    string_table_t *string_table = (string_table_t*) malloc(sizeof(string_table_t));
    string_table->capacity = 4;
    string_table->string = (string_array_t **) malloc(sizeof(string_array_t *) * string_table->capacity);
    string_table->length = 0;
    string_table->width = width;
    string_table->max_column_length = (int*) malloc(sizeof(int) * width);
    for (int i = 0; i < width; ++i) {
        string_table->max_column_length[i] = -1;
    }
    return string_table;
}

void recalculate_max_column_length(string_table_t *string_table, string_array_t *new_row) {
    for (int i = 0; i < string_table->width; ++i) {
        int max_length = string_table->max_column_length[i];
        if (i < new_row->length) {
            if (new_row->strings[i]->length > max_length) {
                max_length = new_row->strings[i]->length;
            }
        }else{
            fprintf(stderr, "Error: column %d is not defined\n", i);
        }
        string_table->max_column_length[i] = max_length;
    }
}

void add_row_to_table(string_table_t *string_table, string_array_t *new_row) {
    if (string_table->length + 1 > string_table->capacity) {
        string_table->capacity *= 2;
        string_table->string = (string_array_t **) realloc(string_table->string, sizeof(*string_table->string)*string_table->capacity);
    }
    recalculate_max_column_length(string_table, new_row);
    string_table->string[string_table->length] = new_row;
    string_table->length++;
}

void print_table(string_table_t *string_table, options_t *options) {
    for (int i = 0; i < string_table->length; ++i) {
        string_array_t *row = string_table->string[i];
        for (int j = 0; j < row->length; ++j) {
            if(options->flags & FRAME){
                printf("| ");
            }
            string_t *string = row->strings[j];
            int max_length = string_table->max_column_length[j];
            printf("%s", string->chars);
            int padding = max_length - string->length;
            for (int k = 0; k < padding; ++k) {
                printf(" ");
            }
            if(options->flags & FRAME ){
                printf(" ");
                if(j == row->length - 1){
                    printf("|");
                }
            }
        }
        printf("\n");
    }
}
