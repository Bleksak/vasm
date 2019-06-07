
#include "aad.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <stdio.h>

struct EncodedInstruction aad(struct Operand* operand1, struct Operand* operand2, struct Operand* operand3, struct Operand* operand4, bool lock)
{
    if(operand1->exists)
    {
        if(operand1->type != IMM8)
            return (struct EncodedInstruction) { .ok = false, .error_message = "Instruction aad expects imm8"};

        return (struct EncodedInstruction) { .ok = true, .value[0] = 0xD5, .value[1] = operand1->uimm8, .size = 2 };
    }

    return (struct EncodedInstruction) { .ok = true, .value[0] = 0xD5, .value[1] = 0x0A, .size = 2 };
}

#pragma GCC diagnostic pop