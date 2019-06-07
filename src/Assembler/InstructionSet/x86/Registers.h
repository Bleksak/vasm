#pragma once

#include <stdbool.h>

enum REGISTER_NUMBERS
{
    AL  = 0,
    AH  = 4,
    AX  = 0,
    EAX = 0,
    RAX = 0,

    CL  = 1,
    CH  = 5,
    CX  = 1,
    ECX = 1,
    RCX = 1,

    DL  = 2,
    DH  = 6,
    DX  = 2,
    EDX = 2,
    RDX = 2,
    
    BL  = 3,
    BH  = 7,
    BX  = 3,
    EBX = 3,
    RBX = 3,

    SPL = 4,
    SP  = 4,
    ESP = 4,
    RSP = 4,

    BPL = 5,
    BP  = 5,
    EBP = 5,
    RBP = 5,

    SIL = 6,
    SI  = 6,
    ESI = 6,
    RSI = 6,

    DIL = 7,
    DI  = 7,
    EDI = 7,
    RDI = 7,

    NO_X86_REGISTER
};

enum OperandType
{
    REGISTER,
    //[eax] not sure what it's called
    IMM8,
    IMM16,
    IMM32,
    IMM64
};

enum RegisterSize
{
    BYTE,
    WORD,
    DWORD,
    QWORD,
    SIZE_UNSPECIFIED,
};

struct Operand
{
    bool exists;
    enum RegisterSize reg_size;
    enum OperandType type;
    bool deref;

    union
    {
        enum REGISTER_NUMBERS reg;
        unsigned char uimm8;
        unsigned short uimm16;
        unsigned int uimm32;
        unsigned long long uimm64;

        signed char imm8;
        signed short imm16;
        signed int imm32;
        signed long long imm64;
    };
};

enum get_x86_operand_errors
{
    X86_OK = 0,
    X86_OVERFLOW,
    X86_INVALID_FORMAT,
};

int get_x86_operand(struct Operand* operand, char* name);