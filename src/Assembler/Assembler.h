#pragma once
#include <stdio.h>
#include <string.h>

enum ASSEMBLER_ERRORS
{
    ASSEMBLER_NO_INSTR,
    ASSEMBLER_NO_LOCK,
    ASSEMBLER_NOT_ENOUGH_OPERANDS,
    ASSEMBLER_SYNTAX_ERROR,
    X86_OVERFLOW,
    X86_INVALID_FORMAT,
    X86_INVALID_OPERAND,
    ASSEMBLER_INSTRUCTION_ERROR_CUSTOM,
    ASSEMBLER_MACRO_ERROR,
};

enum ASSEMBLER_ERROR_TYPE
{
    ASSEMBLER_ERROR_NONE,
    ASSEMBLER_ERROR_FILE,
    ASSEMBLER_ERROR_ASM,
};

struct AssemblerError
{
    enum ASSEMBLER_ERROR_TYPE type;
    int code;
    int line;
    const char* error_message;
};

struct AssemblerError assemble_file(const char* restrict filename, unsigned char* restrict * restrict output);

static inline void get_assembler_error_str(const struct AssemblerError* error, char* buffer, size_t buffer_size)
{
    const char* error_strings[] = 
    {
        "Instruction not found on line %d",
        "Instruction does not support LOCK prefix on line %d",
        "Not enough operands supplied for a function on line %d",
        "Unexpected newline on line %d",
        "Value overflows on line %d",
        "Invalid hex/binary format on line %d",
        "Invalid operand on line %d",
    };

    if(error->code == ASSEMBLER_INSTRUCTION_ERROR_CUSTOM)
        sprintf_s(buffer, buffer_size, "%s on line %d", error->error_message, error->line);
    else
        sprintf_s(buffer, buffer_size, error_strings[error->code], error->line);
}