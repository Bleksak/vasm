#include "x86_instruction_set.h"
#include <string.h>

static const struct X86_Instruction x86_instruction_set[] = 
{
    {
        .name = "aaa",
        .takes_args = 0,
        .supports_lock = false,
        .parse = aaa,
    }
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