#include <stdio.h>
#include "string_table.h"
#include "options.h"

#define VERSION_NAME "0.0.1"

void print_version(){
    printf("Table printer version: %s\n", VERSION_NAME);
}

int main(int argc, char *argv[]) {
    options_t *options = parse_options(argc, argv);
    if (options->flags & HELP) {
        print_help_menu();
    }
    if (options->flags & VERSION) {
        print_version();
        return 0;
    }
    string_table_t *table= get_string_table(options);
    print_table(table,options);
    free_string_table(table);
    free_options(options);
    return 0;
}

