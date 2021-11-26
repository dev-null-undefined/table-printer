#ifndef TABLE_PRINTER_OPTIONS_H
#define TABLE_PRINTER_OPTIONS_H

#include "custom_string.h"
#include <stdio.h>

typedef struct {
    char delimiter;
    int flags;
    FILE *stream;
    int color_count;
} options_t;

int compare_tag(const char *input, const char *tag, const char *short_tag);
int parse_argument(char *argument);
int check_color_capability();
options_t *parse_options(int argc, char *argv[]);
void print_help_menu();

enum OPTION_FLAGS {
    HEADER = 1 << 1,
    COUNTER = 1 << 2,
    COLORS = 1 << 3,
    FRAME = 1 << 4,
    ALIGN_LEFT = 1 << 5,
    VERSION = 1 << 28,
    HELP = 1 << 29,
    UNKNOWN = 1 << 30,
};

#endif //TABLE_PRINTER_OPTIONS_H
