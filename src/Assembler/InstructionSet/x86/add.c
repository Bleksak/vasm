#include "add.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

struct EncodedInstruction add(struct Operand* operand1, struct Operand* operand2, struct Operand* operand3, struct Operand* operand4, bool lock)
{
    return (struct EncodedInstruction) 
    {
        .ok = false,
    };
}

#pragma GCC diagnostic pop