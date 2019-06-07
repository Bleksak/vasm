#include "EncodedInstruction.h"

#include <stdio.h>

struct EncodedInstruction encode_byte_instr(unsigned char opcode, bool direction, enum X86_MOD mod, int reg, unsigned char rm, bool rex, bool size_override)
{
    unsigned char primary_opcode = (unsigned char) (opcode | (unsigned char)direction << 1);
    unsigned char modregrm = (unsigned char)((mod << 6) | ((unsigned char)reg << 3) | rm);

    if(rex)
    {
        return (struct EncodedInstruction)
        {
            .ok = true,
            .size = 3,
            .value[0] = 0x48,
            .value[1] = primary_opcode,
            .value[2] = modregrm,
        };
    }

    if(size_override)
    {
        return (struct EncodedInstruction)
        {
            .ok = true,
            .size = 3,
            .value[0] = 0x66,
            .value[1] = primary_opcode,
            .value[2] = modregrm,
        };
    }

    return (struct EncodedInstruction) 
    {
        .ok = true,
        .size = 2,
        .value[0] = primary_opcode,
        .value[1] = modregrm,
    };
}