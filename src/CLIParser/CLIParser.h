#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

enum ARG_VALUE
{
    ARG_VALUE_NONE,
    ARG_VALUE_INT,
    ARG_VALUE_UINT,
    ARG_VALUE_STRING,
    ARG_VALUE_COUNT,
};

enum ARG_LIST
{
    ARG_INPUT,
    ARG_OUTPUT,
    ARG_OUTPUT_TYPE,
    ARG_COUNT,
};

enum CLI_ERROR_CODES
{
    CLI_NOT_SUPPORTED = -1,
    CLI_INVALID_ARGUMENT = -2,
    CLI_REQUIRES_VALUE = -3,
    CLI_FILENAME_EMPTY = -4,
    CLI_OUTPUT_SET = -5,
    CLI_INPUT_SET = -6,
    CLI_OUT_OF_MEMORY = -7,
    CLI_NO_INPUT_OUTPUT_FILE = -8,
    CLI_PRINT_HELP = -9,
};

struct Argument
{
    enum ARG_LIST arg;
    enum ARG_VALUE type;

    union
    {
        long intVal;
        unsigned long uintVal;
        const char* strVal;
    };
};

struct Arguments
{
    const char* input_file;
    const char* output_file;
    size_t count;
    struct Argument* arguments;
};

int parse_cli(int argc, const char* argv[], struct Arguments* restrict arguments);

inline void free_cli(struct Arguments* restrict arguments)
{
    free(arguments->arguments);
}

__attribute__((const)) inline const char* cli_get_error_string(int code)
{
    const char* error_strings[] = 
    {
        "Feature not supported",
        "Invalid argument supplied",
        "Argument requires value",
        "File name is empty",
        "Output file is already set",
        "Input file is already set",
        "Out of memory",
        "No input file",
        "No output file",
    };

    return error_strings[code];
}