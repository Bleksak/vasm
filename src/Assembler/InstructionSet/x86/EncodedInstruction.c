#include "EncodedInstruction.h"

#include <stdio.h>

struct EncodedInstruction encode_byte_instr(unsigned char opcode, bool direction, enum X86_MOD mod, int reg, int rm, bool rex, bool size_override, unsigned char value[], unsigned char value_size)
{
    unsigned char primary_opcode = (unsigned char) (opcode | (unsigned char)direction << 1);
    unsigned char modregrm = (unsigned char)((mod << 6) | ((unsigned char)reg << 3) | rm);

    if(rex)
    {
        struct EncodedInstruction ret = 
        {
            .ok = true,
            .size = 3 + value_size,
            .value[0] = 0x48,
            .value[1] = primary_opcode,
            .value[2] = modregrm,
        };

        for(unsigned int i = 0; i < value_size; ++i)
        {
            ret.value[i + 3] = value[i];
        }
        
        return ret;
    }

    if(size_override)
    {
        struct EncodedInstruction ret =
        {
            .ok = true,
            .size = 3 + value_size,
            .value[0] = 0x66,
            .value[1] = primary_opcode,
            .value[2] = modregrm,
        };

        for(unsigned int i = 0; i < value_size; ++i)
        {
            ret.value[i + 3] = value[i];
        }
        
        return ret;

    }

    struct EncodedInstruction ret = 
    {
        .ok = true,
        .size = 2 + value_size,
        .value[0] = primary_opcode,
        .value[1] = modregrm,
    };

    for(unsigned int i = 0; i < value_size; ++i)
    {
        ret.value[i + 2] = value[i];
    }
    
    return ret;

}