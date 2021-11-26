cmake_minimum_required(VERSION 3.21)
project(table_printer)

set(CMAKE_CXX_STANDARD 14)

add_executable(table_printer
        main.c
        custom_string.c
        custom_string.h string_array.c string_array.h string_table.c string_table.h options.c options.h)