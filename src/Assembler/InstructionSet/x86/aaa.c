#include "aaa.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

struct EncodedInstruction aaa(struct Operand* operand1, struct Operand* operand2, struct Operand* operand3, struct Operand* operand4, bool lock)
{
    return (struct EncodedInstruction) { .ok = true, .size = 1, .value[0] = 0x37 };
}

#pragma GCC diagnostic pop