#include "string_table.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

string_table_t *create_string_table(int width) {
    string_table_t *string_table = (string_table_t *) malloc(sizeof(string_table_t));
    string_table->capacity = 4;
    string_table->rows = (string_array_t **) malloc(sizeof(string_array_t *) * string_table->capacity);
    string_table->length = 0;
    string_table->width = width;
    string_table->max_column_length = (int *) malloc(sizeof(int) * width);
    for (int i = 0; i < width; ++i) {
        string_table->max_column_length[i] = -1;
    }
    return string_table;
}

string_table_t *get_string_table(options_t *options) {
    string_table_t *table = NULL;
    string_t *buffer = create_string_empty(12);
    string_array_t *line = create_string_array(3);

    int input;
    int width = 0;
    while ((input = getc(options->stream)) != EOF) {
        if (input == options->delimiter) {
            add_string_to_array(line, buffer);
            buffer = create_string_empty(12);
            width++;
            continue;
        }
        if (input == '\n' || input == '\r') {
            if(buffer->length == 0) continue;
            add_string_to_array(line, buffer);
            buffer = create_string_empty(12);
            width++;

            if (table == NULL) {
                table = create_string_table(width);
            }
            add_row_to_table(table, line);
            line = create_string_array(3);
            width = 0;
        } else {
            append_char_to_string(buffer, (char) input);
        }
    }
    free_string(buffer);
    free_string_array(line);
    return table;
}

void recalculate_max_column_length(string_table_t *string_table, string_array_t *new_row) {
    for (int i = 0; i < string_table->width; ++i) {
        int max_length = string_table->max_column_length[i];
        if (i < new_row->length) {
            if (new_row->strings[i]->length > max_length) {
                max_length = new_row->strings[i]->length;
            }
        } else {
            fprintf(stderr, "Error: column %d is not defined\n", i);
        }
        string_table->max_column_length[i] = max_length;
    }
}

void add_row_to_table(string_table_t *string_table, string_array_t *new_row) {
    if (string_table->length + 1 > string_table->capacity) {
        string_table->capacity *= 2;
        string_table->rows = (string_array_t **) realloc(string_table->rows,
                                                         sizeof(*string_table->rows) * string_table->capacity);
    }
    recalculate_max_column_length(string_table, new_row);
    string_table->rows[string_table->length] = new_row;
    string_table->length++;
}

int digit_count(int number) {
    int count = 0;
    while (number > 0) {
        number /= 10;
        count++;
    }
    return count == 0 ? 1 : count;
}

void print_aligned_string(const char *format, void *data, int padding, int align_left, options_t *options) {
    if (!align_left) {
        for (int i = 0; i < padding; ++i) {
            fprintf(options->out_stream, " ");
        }
    }
    fprintf(options->out_stream, format, data);
    if (align_left) {
        for (int i = 0; i < padding; ++i) {
            fprintf(options->out_stream, " ");
        }
    }
}

void print_separator(int counter_length, const int max_column_length[], int width, options_t *options) {
    if (counter_length > 0) {
        fprintf(options->out_stream, "+");
        for (int j = 0; j < counter_length + 1; ++j) {
            fprintf(options->out_stream, "-");
        }
    }
    fprintf(options->out_stream, "+");
    for (int i = 0; i < width; ++i) {
        int max_length = max_column_length[i];
        for (int j = 0; j < max_length + 2; ++j) {
            fprintf(options->out_stream, "-");
        }
        fprintf(options->out_stream, "+");
    }
    fprintf(options->out_stream, "\n");
}

void rotate_color(int *color, int color_count, options_t *options) {
    set_console_color(*color, options);
    *color = (*color + 1) % color_count;
}

void set_frame_color(options_t *options) {
    set_console_color(RESET, options);
}

void print_table(string_table_t *string_table, options_t *options) {
    if (string_table == NULL) return;
    int max_counter_length = (options->flags & COUNTER) ? digit_count(string_table->length) : 0;
    if (options->flags & FRAME)
        print_separator(max_counter_length, string_table->max_column_length, string_table->width, options);
    for (int line_number = 0; line_number < string_table->length; ++line_number) {
        int color_index = 0;
        if (line_number == 1 && options->flags & HEADER && options->flags & FRAME) {
            print_separator(max_counter_length, string_table->max_column_length, string_table->width, options);
        }
        string_array_t *row = string_table->rows[line_number];
        if (options->flags & COUNTER) {
            if (options->flags & FRAME) {
                fprintf(options->out_stream, TABLE_FRAME_SEPARATOR);
            }
            fprintf(options->out_stream, " ");
            rotate_color(&color_index, COLOR_COUNT, options);
            print_aligned_string("%d", (void *) (intptr_t) line_number,
                                 max_counter_length - digit_count(line_number),
                                 options->flags & ALIGN_LEFT, options);
            set_frame_color(options);
        }
        for (int j = 0; j < row->length; ++j) {
            if (options->flags & FRAME) {
                fprintf(options->out_stream, TABLE_FRAME_SEPARATOR);
            }
            fprintf(options->out_stream, " ");
            string_t *string = row->strings[j];
            int padding = string_table->max_column_length[j] - string->length;
            rotate_color(&color_index, COLOR_COUNT, options);
            print_aligned_string("%s", string->chars, padding, options->flags & ALIGN_LEFT, options);
            set_frame_color(options);
            if (options->flags & FRAME) {
                fprintf(options->out_stream, " ");
                if (j == row->length - 1) {
                    fprintf(options->out_stream, TABLE_FRAME_SEPARATOR);
                }
            }
        }
        fprintf(options->out_stream, "\n");
    }
    if (options->flags & FRAME)
        print_separator(max_counter_length, string_table->max_column_length, string_table->width, options);

}

void set_console_color(int color, options_t *options) {
    const char *s;
    switch (color) {
        case BLACK:
            s = "\x1b[30m";
            break;
        case BLUE:
            s = "\x1b[34m";
            break;
        case GREEN:
            s = "\x1b[32m";
            break;
        case CYAN:
            s = "\x1b[36m";
            break;
        case RED:
            s = "\x1b[31;1m";
            break;
        case MAGENTA:
            s = "\x1b[35m";
            break;
        case BROWN:
            s = "\x1b[31m";
            break;
        case LIGHTBLUE:
            s = "\x1b[34;1m";
            break;
        case LIGHTCYAN:
            s = "\x1b[36;1m";
            break;
        case LIGHTRED:
            s = "\x1b[31;1m";
            break;
        case LIGHTMAGENTA:
            s = "\x1b[35;1m";
            break;
        case YELLOW:
            s = "\x1b[33;1m";
            break;
        case WHITE:
            s = "\x1b[37;1m";
            break;
        case BLINK:
            s = "\x1b[30m";
            break;
        case RESET:
            s = "\x1b[0m";
            break;
        default:
            return;
    }
    fprintf(options->out_stream, "%s", s);
}

void free_string_table(string_table_t *table) {
    for (int i = 0; i < table->length; i++) {
        free_string_array(table->rows[i]);
    }
    free(table->rows);
    free(table->max_column_length);
    free(table);
}