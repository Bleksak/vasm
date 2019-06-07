#include "aam.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

struct EncodedInstruction aam(struct Operand* operand1, struct Operand* operand2, struct Operand* operand3, struct Operand* operand4, bool lock)
{
    if(!operand1->exists)
        return (struct EncodedInstruction)
        {
            .ok = true,
            .size = 2,
            .value[0] = 0xD4,
            .value[1] = 0x0A,
        };

    if(operand1->type != IMM8)
        return (struct EncodedInstruction)
        {
            .ok = false,
            .error_message = "Instruction aam expects uimm8",
        };
    
    return (struct EncodedInstruction)
    {
        .ok = true,
        .size = 2,
        .value[0] = 0xD4,
        .value[1] = operand1->uimm8,
    };
}

#pragma GCC diagnostic pop