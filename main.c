#include <stdio.h>
#include "string_table.h"
#include "options.h"

void print_help_menu(){
    printf("Usage: table [OPTION]... FILE\n");
    printf("Formats FILE, or standard input, to standard output.\n");
    printf("\n");
    printf("  -C, --counter      prefix each line of output with the line number\n");
    printf("  -h, --header       treats the first line as header and separates it\n");
    printf("  -v, --version      display the version of table\n");
    printf("  -f, --frame        print a frame around the output\n");
    printf("  -c, --colors       use colors in the output\n");
    printf("  -h, --help         display this help\n");
}

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

int main(int argc, char *argv[]) {
    options_t *options = parse_options(argc, argv);
    if (options->flags & HELP) {
        print_help_menu();
    }
    do_the_magic(options);
    return 0;
}

