#include "options.h"
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

options_t* create_options(){
    options_t *options = (options_t*) malloc(sizeof(options_t));
    options->delimiter = ',';
    options->flags = 0;
    options->stream = stdin;
    return options;
}
int compare_tag(const char *input, const char *tag, const char *short_tag) {
    if (strcasecmp(input, tag) == 0)
        return 0;
    return strcasecmp(input, short_tag);
}
int parse_argument(char *argument) {
    if (compare_tag(argument, "--help", "-h") == 0) {
        return HELP;
    } else if (compare_tag(argument, "--version", "-v") == 0) {
        return VERSION;
    } else if (compare_tag(argument, "--counter", "-C") == 0) {
        return COUNTER;
    } else if (compare_tag(argument, "--header", "-h") == 0) {
        return HEADER;
    } else if (compare_tag(argument, "--colors", "-c") == 0) {
        return COLORS;
    } else if (compare_tag(argument, "--frame", "-f") == 0) {
        return FRAME;
    } else {
        return UNKNOWN;
    }
}
int check_color_capability() {
    char* term=getenv("TERM");
    if (term==NULL) {
        return 0;
    }
    if (strcmp(term,"xterm-256color")==0) {
        return 1;
    }
    return 0;
}
options_t *parse_options(int argc, char *argv[]) {
    options_t *options = create_options();
    for (int i = 1; i < argc; ++i) {
        char *argument = argv[i];
        if(strcmp(argument,"-d")==0 && i < argc-1) {
            options->delimiter = argv[i+1][0];
            i++;
            continue;
        }
        int parsed = parse_argument(argument);
        if(parsed & UNKNOWN) {
            if( access( argument, R_OK ) == 0 ) {
                if(options->stream != stdin) {
                    fprintf(stderr, "Error: Only one input file can be specified.\n");
                    exit(1);
                }
                options->stream = fopen(argument, "r");
                continue;
            }
            printf("Unknown option: %s\n", argument);
            options->flags |= HELP;
            continue;
        }
        options->flags |= parsed;
    }
    if(check_color_capability()) {
        options->flags |= COLORS;
    }
    return options;
}