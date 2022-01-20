#include <stdio.h>
#include "string_table.h"
#include "options.h"

#define VERSION_NAME "0.0.5"

void print_version() {
    printf("Table printer version: %s\n", VERSION_NAME);
}

int main(int argc, char *argv[]) {
    options_t *options = parse_options(argc, argv);
    if (options->flags & HELP) {
        print_help_menu();
        return 0;
    }
    if (options->flags & VERSION) {
        print_version();
        return 0;
    }
    string_table_t *table = string_table_create(options);
    string_table_print(table, options);
    string_table_free(table);
    options_free(options);
    return 0;
}

