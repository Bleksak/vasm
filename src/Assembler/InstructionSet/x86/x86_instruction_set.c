#include "x86_instruction_set.h"
#include <string.h>

#include "aaa.h"
#include "aad.h"
#include "aam.h"
#include "aas.h"
#include "adc.h"

static const struct X86_Instruction x86_instruction_set[] = 
{
    {
        .name = "aaa",
        .takes_args = 0,
        .supports_lock = false,
        .parse = aaa,
    },
    {
        .name = "aad",
        .takes_args = 1,
        .arg_optional = true,
        .supports_lock = false,
        .parse = aad,
    },
    {
        .name = "aam",
        .takes_args = 1,
        .arg_optional = true,
        .supports_lock = false,
        .parse = aam,
    },
    {
        .name = "aas",
        .takes_args = 0,
        .supports_lock = false,
        .parse = aas,
    },
    {
        .name = "adc",
        .takes_args = 2,
        .arg_optional = false,
        .supports_lock = true,
        .parse = adc,
    },
};

const struct X86_Instruction* find_x86_instruction(const char* name)
{
    for(unsigned int i = 0; i < sizeof(x86_instruction_set) / sizeof(x86_instruction_set[0]); ++i)
    {
        if(strcmp(x86_instruction_set[i].name, name) == 0)
        {
            return &x86_instruction_set[i];
        }
    }

    return 0;
}