#pragma once
#include <stdbool.h>

struct x86_config
{
    enum BITS
    {
        BITS16,
        BITS32,
        BITS64
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

const struct config_keyword* get_assembler_keyword(const char* name);