#pragma once
#include <stdbool.h>
#include "EncodedInstruction.h"
#include "aaa.h"

struct X86_Instruction
{
    const char* name;
    unsigned int takes_args;
    bool supports_lock;
    struct EncodedInstruction (*parse)(struct Operand* operand1, struct Operand* operand2, struct Operand* operand3, struct Operand* operand4, bool lock);
};

const struct X86_Instruction* find_x86_instruction(const char* name);