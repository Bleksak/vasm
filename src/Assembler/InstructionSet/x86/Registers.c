#include "Registers.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "../../Assembler.h"


static int setOperandFromValue(unsigned long long value, struct Operand* operand)
{
    if(operand->reg_size != SIZE_UNSPECIFIED)
    {
        switch(operand->reg_size)
        {
            case BYTE:
            {
                operand->uimm64 = value & 0xFF;
                if(value > 255)
                {
                    return X86_OVERFLOW;
                }
            } break;

            case WORD:
            {
                operand->uimm64 = value & 0xFFFF;
                if(value > 65535)
                {
                    return X86_OVERFLOW;
                }
            } break;

            case DWORD:
            {
                operand->uimm64 = value & 0xFFFFFFFF;
                if(value > 4294967295)
                {
                    return X86_OVERFLOW;
                }
            } break;

            case QWORD:
            {
                operand->uimm64 = value;
            } break;

            case SIZE_UNSPECIFIED: {}
        }
    }

    operand->uimm64 = value;

    if(value < 256)
    {
        operand->type = IMM8;
    }
    else if(value < 65536)
    {
        operand->type = IMM16;
    }
    else if(value < 4294967296)
    {
        operand->type = IMM32;
    }
    else
    {
        operand->type = IMM64;
    }

    return 0;
}

int get_x86_operand(struct Operand* operand, char* name)
{
    operand->exists = true;
    operand->reg_size = SIZE_UNSPECIFIED;

    if(name[strlen(name)-1] == ',')
        name[strlen(name)-1] = 0;

    if(strncmp("byte ", name, 5) == 0)
    {
        name += 5;
        operand->reg_size = BYTE;
    }

    else if(strncmp("word ", name, 5) == 0)
    {
        name += 5;
        operand->reg_size = WORD;
    }

    else if(strncmp("dword ", name, 6) == 0)
    {
        name += 6;
        operand->reg_size = DWORD;
    }

    else if(strncmp("qword ", name, 6) == 0)
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

    if(name[0] == '-')
    {
        ++name;
    }

    if(name[0] == '0')
    {
        if(name[1] == 'x')
        {
            // hexadecimal format
            name += 2;
            
            if(name[strspn(name, "-0123456789abcdef")] != 0)
            {
                // not valid hex
                return X86_INVALID_FORMAT;
            }

            return setOperandFromValue((unsigned long long)strtoll(name, NULL, 16), operand);
        }    
        
        if(name[1] == 'b')
        {
            // binary format
            name += 2;

            if(name[strspn(name, "-01")] != 0)
            {
                // not valid hex
                return X86_INVALID_FORMAT;
            }
            
            return setOperandFromValue((unsigned long long)strtoll(name, NULL, 2), operand);
        }
    }

    if(name[strspn(name, "-0123456789")] != 0)
    {
        return X86_INVALID_OPERAND;
    }

    return setOperandFromValue((unsigned long long)strtoll(name, NULL, 10), operand);
}