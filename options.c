#include "options.h"
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

options_t *create_options() {
    options_t *options = (options_t *) malloc(sizeof(options_t));
    options->delimiter = ',';
    options->flags = 0;
    options->stream = stdin;
    options->out_stream = stdout;
    return options;
}

int compare_tag(const char *input, const char *tag, const char *short_tag) {
    if (strcasecmp(input, tag) == 0)
        return 0;
    return strcmp(input, short_tag);
}

void print_help_menu() {
    printf("Usage: table [OPTION]... FILE\n");
    printf("Formats FILE, or standard input, to standard output.\n");
    printf("\n");
    printf("  -C, --counter      prefix each line of output with the line number\n");
    printf("  -h, --header       treats the first line as header and separates it\n");
    printf("  -v, --version      display the version of table\n");
    printf("  -f, --frame        print a frame around the output\n");
    printf("  -c, --colors       use colors in the output\n");
    printf("  -H, --help         display this help\n");
    printf("  -l, --left-align   align text to the left side of the frame\n");
    printf("  -o, --output-file  output to file instead of stdout\n");
    printf("  -F, --force        used to override output file if file exists\n");
    printf("  -d, --delimiter    delimiter char to separate fields\n");
}

int parse_argument(char *argument) {
    if (compare_tag(argument, "--help", "-H") == 0) {
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
    } else if (compare_tag(argument, "--left-align", "-l") == 0) {
        return ALIGN_LEFT;
    } else if (compare_tag(argument, "--force", "-F") == 0) {
        return FORCE;
    } else {
        return UNKNOWN;
    }
}

int check_color_capability() {
    char *term = getenv("TERM");
    if (term == NULL) {
        return 0;
    }
    if (strcmp(term, "xterm-256color") == 0) {
        return 1;
    }
    return 0;
}

options_t *parse_options(int argc, char *argv[]) {
    char *out_file = NULL;
    options_t *options = create_options();
    for (int i = 1; i < argc; ++i) {
        char *argument = argv[i];
        if (compare_tag(argument, "--delimiter", "-d") == 0) {
            if (i >= argc - 1) {
                fprintf(stderr, "Error: %s can no be used as last argument.\n", argument);
                continue;
            }
            if (argv[i + 1][1] != 0) {
                fprintf(stderr, "Error: Delimiter can not be longer then 1 char.\n");
                continue;
            }
            options->delimiter = argv[i + 1][0];
            i++;
            continue;
        }
        if (compare_tag(argument, "--output-file", "-o") == 0) {
            if (i >= argc - 1) {
                fprintf(stderr, "Error: %s can no be used as last argument.\n", argument);
                continue;
            }
            if (out_file != NULL) {
                fprintf(stderr, "Error: Only 1 output file can be specified\n");
                continue;
            }
            out_file = argv[i + 1];
            i++;
            continue;
        }
        int parsed = parse_argument(argument);
        if (parsed & UNKNOWN) {
            if (access(argument, R_OK) == 0) {
                if (options->stream != stdin) {
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
    if (out_file != NULL) {
        if (strcasecmp(out_file, "stdout") == 0) {
            options->out_stream = stdout;
        } else if (strcasecmp(out_file, "stderr") == 0) {
            options->out_stream = stderr;
        } else if (access(out_file, F_OK) == 0) {
            if (options->flags & FORCE) {
                options->out_stream = fopen(out_file, "w");
            } else {
                fprintf(stderr, "Error: File exits and --force was not set defaulting to stdout\n");
            }
        } else {
            FILE *file = fopen(out_file, "w");
            if (file == NULL) {
                fprintf(stderr, "Error: Failed to create file defaulting to stdout\n");
            } else {
                options->out_stream = file;
            }
        }
    }
    if (check_color_capability()) {
        options->flags |= COLORS;
    }
    return options;
}

void free_options(options_t *options) {
    if (options->stream != stdin) {
        fclose(options->stream);
    }
    if (options->out_stream != stdout && options->out_stream != stderr) {
        fclose(options->out_stream);
    }
    free(options);
}