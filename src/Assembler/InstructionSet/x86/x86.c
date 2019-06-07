#include "x86.h"
#include <string.h>
#include <stdlib.h>

static struct x86_option setBits(struct x86_config* cfg, const char* value)
{
    switch(atoi(value))
    {
        case 16:
        {
            cfg->bits = BITS16;
        } break;

        case 32:
        {
            cfg->bits = BITS32;
        } break;

        case 64:
        {
            cfg->bits = BITS64;
        } break;

        default:
        {
            return (struct x86_option)
            {
                .ok = false,
                .message = "Invalid BITS value supplied, possible values are: 16, 32, 64",
            };
        }
    }

    return (struct x86_option)
    {
        .ok = true,
    };
}



static const struct config_keyword keywords[] = 
{
    {
        .name = "bits",
        .args = 1,
        .handle = setBits
    },
};

const struct config_keyword* get_assembler_keyword(const char* name)
{
    for(unsigned int i = 0; i < (sizeof(keywords) / sizeof(keywords[0])); ++i)
    {
        if(strcmp(keywords[i].name, name) == 0)
        {
            return &keywords[i];
        }
    }

    return 0;
}