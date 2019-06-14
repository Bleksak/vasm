#pragma once
#include <stdbool.h>

struct x86_config
{
    enum BITS
    {
        BITS16 = 1,
        BITS32 = 2,
        BITS64 = 3
    } bits;
};

struct x86_option
{
    bool ok;
    const char* message;
};

struct config_keyword
{
    const char* name;
    unsigned int args;
    struct x86_option (*handle)(struct x86_config* cfg, const char* value);
};

struct x86_instruction_arguments
{
    struct x86_config* config;
    bool lock;
};

const struct config_keyword* get_assembler_keyword(const char* name);