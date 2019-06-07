#pragma once
#include <stdbool.h>
#include "Registers.h"

enum X86_MOD
{
    SIB = 0,
    INDIRECT = 0,
    DISPLACEMENT_ONLY = 0,

    DISPLACEMENT_ONE_B = 0b01,
    DISPLACEMENT_FOUR_B = 0b10,
    REGISTER_ADDRESSING = 0b11,
};

struct EncodedInstruction
{
    bool ok;
    union {
        const char* error_message;
        struct 
        {
            unsigned int size;
            unsigned char value[16];
        };
    };
};

__attribute__((const)) struct EncodedInstruction encode_byte_instr(unsigned char opcode, bool direction, enum X86_MOD mod, int reg, unsigned char rm, bool rex, bool size_override);
