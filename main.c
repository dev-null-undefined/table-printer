#include <stdio.h>
#include "string_table.h"
#include "options.h"

#define VERSION_NAME "0.0.1"

void do_the_magic(options_t* options){
    string_table_t *table = NULL;
    string_t *buffer = create_string_empty(12);
    string_array_t *line = create_string_array(3);

    int input;
    int width = 0;
    while ((input = getc(options->stream)) != EOF){
        if(input==options->delimiter){
//            printf("%s\n", buffer->chars);
            add_string_to_array(line, buffer);
            buffer = create_string_empty(12);
            width++;
            continue;
        }
        if (input == '\n'){

            add_string_to_array(line, buffer);
            buffer = create_string_empty(12);
            width++;

            if(table==NULL) {
                table = create_string_table(width);
            }
            add_row_to_table(table, line);
            line = create_string_array(3);
            width = 0;
        } else {
            append_char_to_string(buffer, (char) input);
        }
    }
    if(table!=NULL) {
        print_table(table, options);
    }
}

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
    do_the_magic(options);
    return 0;
}

