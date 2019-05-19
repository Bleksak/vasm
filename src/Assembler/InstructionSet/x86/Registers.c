#include "Registers.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int get_x86_operand(struct Operand* operand, char* name)
{
    if(strncpy("byte ", name, 5) == 0)
    {
        name += 5;
        operand->reg_size = BYTE;
    }

    else if(strncpy("word ", name, 5) == 0)
    {
        name += 5;
        operand->reg_size = WORD;
    }

    else if(strncpy("dword ", name, 6) == 0)
    {
        name += 6;
        operand->reg_size = DWORD;
    }

    else if(strncpy("qword ", name, 6) == 0)
    {
        name += 6;
        operand->reg_size = QWORD;
    }
    
    if(name[0] == '[' && name[strlen(name) - 1] == ']')
    {
        operand->deref = true;
        name[strlen(name) - 1] = 0;
        ++name;
    }

    if(strcmp(name, "rax") == 0)
    {
        operand->reg_size = QWORD;
        operand->type = REGISTER;
        operand->reg = RAX;
        return 0;
    }
    
    if(strcmp(name, "eax") == 0)
    {
        operand->reg_size = DWORD;
        operand->type = REGISTER;
        operand->reg = EAX;
        return 0;
    }

    if(strcmp(name, "ax") == 0)
    {
        operand->reg_size = WORD;
        operand->type = REGISTER;
        operand->reg = AX;
        return 0;
    }

    if(strcmp(name, "ah") == 0)
    {
        operand->reg_size = BYTE;
        operand->type = REGISTER;
        operand->reg = AH;
        return 0;
    }

    if(strcmp(name, "al") == 0)
    {
        operand->reg_size = BYTE;
        operand->type = REGISTER;
        operand->reg = AL;
        return 0;
    }

    if(strcmp(name, "rbx") == 0)
    {
        operand->reg_size = QWORD;
        operand->type = REGISTER;
        operand->reg = RBX;
        return 0;
    }
    
    if(strcmp(name, "ebx") == 0)
    {
        operand->reg_size = DWORD;
        operand->type = REGISTER;
        operand->reg = EBX;
        return 0;
    }

    if(strcmp(name, "bx") == 0)
    {
        operand->reg_size = WORD;
        operand->type = REGISTER;
        operand->reg = BX;
        return 0;
    }

    if(strcmp(name, "bh") == 0)
    {
        operand->reg_size = BYTE;
        operand->type = REGISTER;
        operand->reg = BH;
        return 0;
    }

    if(strcmp(name, "bl") == 0)
    {
        operand->reg_size = BYTE;
        operand->type = REGISTER;
        operand->reg = BL;
        return 0;
    }

    if(strcmp(name, "rcx") == 0)
    {
        operand->reg_size = QWORD;
        operand->type = REGISTER;
        operand->reg = RCX;
        return 0;
    }
    
    if(strcmp(name, "ecx") == 0)
    {
        operand->reg_size = DWORD;
        operand->type = REGISTER;
        operand->reg = ECX;
        return 0;
    }

    if(strcmp(name, "cx") == 0)
    {
        operand->reg_size = WORD;
        operand->type = REGISTER;
        operand->reg = CX;
        return 0;
    }

    if(strcmp(name, "ch") == 0)
    {
        operand->reg_size = BYTE;
        operand->type = REGISTER;
        operand->reg = CH;
        return 0;
    }

    if(strcmp(name, "cl") == 0)
    {
        operand->reg_size = BYTE;
        operand->type = REGISTER;
        operand->reg = CL;
        return 0;
    }

    if(strcmp(name, "rdx") == 0)
    {
        operand->reg_size = QWORD;
        operand->type = REGISTER;
        operand->reg = RDX;
        return 0;
    }
    
    if(strcmp(name, "edx") == 0)
    {
        operand->reg_size = DWORD;
        operand->type = REGISTER;
        operand->reg = EDX;
        return 0;
    }

    if(strcmp(name, "dx") == 0)
    {
        operand->reg_size = WORD;
        operand->type = REGISTER;
        operand->reg = DX;
        return 0;
    }

    if(strcmp(name, "dh") == 0)
    {
        operand->reg_size = BYTE;
        operand->type = REGISTER;
        operand->reg = DH;
        return 0;
    }

    if(strcmp(name, "dl") == 0)
    {
        operand->reg_size = BYTE;
        operand->type = REGISTER;
        operand->reg = DL;
        return 0;
    }

    if(strcmp(name, "rsp") == 0)
    {
        operand->reg_size = QWORD;
        operand->type = REGISTER;
        operand->reg = RSP;
        return 0;
    }

    if(strcmp(name, "esp") == 0)
    {
        operand->reg_size = DWORD;
        operand->type = REGISTER;
        operand->reg = ESP;
        return 0;
    }

    if(strcmp(name, "sp") == 0)
    {
        operand->reg_size = WORD;
        operand->type = REGISTER;
        operand->reg = SP;
        return 0;
    }

    if(strcmp(name, "spl") == 0)
    {
        operand->reg_size = BYTE;
        operand->type = REGISTER;
        operand->reg = SPL;
        return 0;
    }

    if(strcmp(name, "rbp") == 0)
    {
        operand->reg_size = QWORD;
        operand->type = REGISTER;
        operand->reg = RBP;
        return 0;
    }

    if(strcmp(name, "ebp") == 0)
    {
        operand->reg_size = DWORD;
        operand->type = REGISTER;
        operand->reg = EBP;
        return 0;
    }

    if(strcmp(name, "bp") == 0)
    {
        operand->reg_size = WORD;
        operand->type = REGISTER;
        operand->reg = BP;
        return 0;
    }

    if(strcmp(name, "bpl") == 0)
    {
        operand->reg_size = BYTE;
        operand->type = REGISTER;
        operand->reg = BPL;
        return 0;
    }

    if(strcmp(name, "rsi") == 0)
    {
        operand->reg_size = QWORD;
        operand->type = REGISTER;
        operand->reg = RSI;
        return 0;
    }

    if(strcmp(name, "esi") == 0)
    {
        operand->reg_size = DWORD;
        operand->type = REGISTER;
        operand->reg = ESI;
        return 0;
    }

    if(strcmp(name, "si") == 0)
    {
        operand->reg_size = WORD;
        operand->type = REGISTER;
        operand->reg = SI;
        return 0;
    }

    if(strcmp(name, "sil") == 0)
    {
        operand->reg_size = BYTE;
        operand->type = REGISTER;
        operand->reg = SIL;
        return 0;
    }

    if(strcmp(name, "rdi") == 0)
    {
        operand->reg_size = QWORD;
        operand->type = REGISTER;
        operand->reg = RDI;
        return 0;
    }

    if(strcmp(name, "edi") == 0)
    {
        operand->reg_size = DWORD;
        operand->type = REGISTER;
        operand->reg = EDI;
        return 0;
    }

    if(strcmp(name, "di") == 0)
    {
        operand->reg_size = WORD;
        operand->type = REGISTER;
        operand->reg = DI;
        return 0;
    }

    if(strcmp(name, "dil") == 0)
    {
        operand->reg_size = BYTE;
        operand->type = REGISTER;
        operand->reg = DIL;
        return 0;
    }

    /*
        here we need to check if the string is in hex, binary or decimal format and whether it's positive or negative
    */

    bool sign = false;

    if(name[0] == '-')
    {
        ++name;
        sign = true;
    }

    if(name[0] == '0')
    {
        if(name[1] == 'x')
        {
            // hexadecimal format
            name += 2;
            
            if(name[strspn(name, "0123456789abcdefABCDEF")] != 0)
            {
                // not valid hex
                return X86_INVALID_FORMAT;
            }

            long long value = strtoll(name, NULL, 16);
            operand->reg = NO_X86_REGISTER;

            switch(operand->reg_size)
            {
                case BYTE:
                {
                    if((sign && ((value > 127) || (value < -128))) || value > 255)
                    {
                        // value overflows 1 BYTE, throw an error
                        return X86_OVERFLOW;
                    }

                    operand->type = IMM8;
                    
                    if(sign)
                        operand->imm8 = (signed char) value;
                    else
                        operand->uimm8 = (unsigned char) value;

                    return 0;

                } break;

                case WORD:
                {
                    if((sign && ((value > 32767) || (value < -32768))) || value > 65535)
                    {
                        // value overflows or underflows 1 WORD, throw an error
                        return X86_OVERFLOW;
                    }

                    operand->type = IMM16;
                    
                    if(sign)
                        operand->imm16 = (signed short) value;
                    else
                        operand->uimm16 = (unsigned short) value;

                    return 0;
                } break;

                case DWORD:
                {
                    if((sign && ((value > 2147483647) || value < -2147483648)) || value > 4294967295)
                    {
                        // value overflows or underflows 1 WORD, throw an error
                        return X86_OVERFLOW;
                    }

                    operand->type = IMM32;
                    
                    if(sign)
                        operand->imm32 = (signed int) value;
                    else
                        operand->uimm32 = (unsigned int) value;

                    return 0;
                } break;

                case QWORD:
                {
                    if((sign && ((value > 9223372036854775807LL) || value < -9223372036854775808LL)) || (unsigned long long)value > 18446744073709551615ULL)
                    {
                        //value overflows or underflows 1 QWORD, throw an error
                        return X86_OVERFLOW;
                    }

                    if(sign)
                        operand->imm64 = value;
                    else
                        operand->uimm64 = (unsigned long long) value;

                    return 0;
                } break;

                default:
                {
                    operand->reg_size = SIZE_UNDEFINED;
                    operand->imm64 = value;
                } break;
            }

            return 0;
        }
        else if(name[1] == 'b')
        {
            // binary format
            name += 2;

            return 0;
        }
    }

    // decimal format
    return 0;
}