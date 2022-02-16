#ifndef TABLE_PRINTER_OPTIONS_H
#define TABLE_PRINTER_OPTIONS_H

#include "custom_string.h"
#include <stdio.h>

typedef struct {
    char delimiter;
    unsigned int flags;
    FILE *stream;
    FILE *out_stream;
} options_t;

typedef enum {
    HEADER = 1 << 1,
    COUNTER = 1 << 2,
    COLORS = 1 << 3,
    FRAME = 1 << 4,
    ALIGN_RIGHT = 1 << 5,
    FORCE = 1 << 6,
    VERSION = 1 << 28,
    HELP = 1 << 29,
    UNKNOWN = 1 << 30,
} OPTION_FLAGS;

OPTION_FLAGS parse_argument(char *argument);

int check_color_capability();

options_t *parse_options(int argc, char *argv[]);

void print_help_menu();

void options_free(options_t *options);

#endif //TABLE_PRINTER_OPTIONS_H
