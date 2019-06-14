#pragma once
#include <stdbool.h>
#include "Registers.h"
#include "EncodedInstruction.h"
#include "x86.h"

struct X86_Instruction
{
    const char* name;
    unsigned int takes_args;
    bool supports_lock;
    bool arg_optional;
    struct EncodedInstruction (*parse)(struct Operand* operand1, struct Operand* operand2, struct Operand* operand3, struct Operand* operand4, struct x86_instruction_arguments* args);
};

const struct X86_Instruction* find_x86_instruction(const char* name);