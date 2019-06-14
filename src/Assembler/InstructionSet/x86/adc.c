#include "adc.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

struct EncodedInstruction adc(struct Operand* operand1, struct Operand* operand2, struct Operand* operand3, struct Operand* operand4, struct x86_instruction_arguments* args)
{
    if(!operand1->deref)
    {
        if (args->lock)
        {
            return (struct EncodedInstruction){
                .ok = false,
                .error_message = "Instruction adc can be used with lock prefix only when destination is memory operand",
            };
        }

        if(operand1->type == IMM8 || operand1->type == IMM16 || operand1->type == IMM32 || operand1->type == IMM64)
        {
            return (struct EncodedInstruction)
            {
                .ok = false,
                .error_message = "Instruction adc expects a valid memory operand or a register as first operand.",
            };
        }

        // operand1 is a register here
        if(operand1->reg == AX && operand2->type != REGISTER)
        {
            if((int)operand2->type > (int)operand1->reg_size)
            {
                return (struct EncodedInstruction)
                {
                    .ok = false,
                    .error_message = "Unmatched operand sizes",
                };
            }

            switch(operand1->reg_size)
            {
                case BYTE:
                {
                    return (struct EncodedInstruction)
                    {
                        .ok = true,
                        .size = 2,
                        .value[0] = 0x14,
                        .value[1] = operand2->uimm8,
                    };
                }

                case WORD:
                {
                    return (args->config->bits == BITS16) ? (struct EncodedInstruction)
                    {
                        .ok = true,
                        .size = 3,
                        .value[0] = 0x15,
                        .value[1] = operand2->uimm32 & 0xFF,
                        .value[2] = (operand2->uimm32 >> 8) & 0xFF,
                    } : (struct EncodedInstruction)
                    {
                        .ok = true,
                        .size = 4,
                        .value[0] = 0x66,
                        .value[1] = 0x15,
                        .value[2] = operand2->uimm32 & 0xFF,
                        .value[3] = (operand2->uimm32 >> 8) & 0xFF,
                    };
                }

                case DWORD:
                {
                    return (args->config->bits == BITS32) ? (struct EncodedInstruction)
                    {
                        .ok = true,
                        .size = 5,
                        .value[0] = 0x15,
                        .value[1] = operand2->uimm32 & 0xFF,
                        .value[2] = (operand2->uimm32 >> 8) & 0xFF,
                        .value[3] = (operand2->uimm32 >> 16) & 0xFF,
                        .value[4] = (operand2->uimm32 >> 24) & 0xFF,
                    }
                    : (struct EncodedInstruction)
                    {
                        .ok = true,
                        .size = 6,
                        .value[0] = 0x66,
                        .value[1] = 0x15,
                        .value[2] =  operand2->uimm32        & 0xFF,
                        .value[3] = (operand2->uimm32 >>  8) & 0xFF,
                        .value[4] = (operand2->uimm32 >> 16) & 0xFF,
                        .value[5] = (operand2->uimm32 >> 24) & 0xFF,
                    };
                }

                case QWORD:
                {
                    return (struct EncodedInstruction)
                    {
                        .ok = true,
                        .size = 10,
                        .value[0] = 0x48,
                        .value[1] = 0x15,
                        .value[2] = operand2->uimm64 & 0xFF,
                        .value[3] = (operand2->uimm64 >> 8) & 0xFF,
                        .value[4] = (operand2->uimm64 >> 16) & 0xFF,
                        .value[5] = (operand2->uimm64 >> 24) & 0xFF,
                        .value[6] = (operand2->uimm64 >> 32) & 0xFF,
                        .value[7] = (operand2->uimm64 >> 40) & 0xFF,
                        .value[8] = (operand2->uimm64 >> 48) & 0xFF,
                        .value[9] = (operand2->uimm64 >> 56) & 0xFF,
                    };
                }

                case SIZE_UNSPECIFIED: {}
            }
        }

        /*
            operand1 is register
        */
        if(operand2->type == REGISTER)
        {
            if(operand2->reg_size != operand1->reg_size)
            {
                return (struct EncodedInstruction)
                {
                    .ok = false,
                    .error_message = "Unmatched operand sizes",
                };
            }


            // operand2 is register

            unsigned char opcode = 0x10 | (operand1->reg_size > BYTE);
            bool rex = operand1->reg_size == QWORD;
            bool operand_size_override = (rex || operand1->reg_size == BYTE) ? false : ((int)args->config->bits != (int)operand1->reg_size);

            return encode_byte_instr(opcode, false, REGISTER_ADDRESSING, operand2->reg, operand1->reg, rex, operand_size_override, 0, 0);
        }
        
        if((int)operand2->type > (int)operand1->reg_size)
        {
            return (struct EncodedInstruction)
            {
                .ok = false,
                .error_message = "Unmatched operand sizes",
            };
        }

        unsigned char opcode = 0x80 | (operand1->reg_size > BYTE) | (operand2->reg_size == BYTE) ? 3 : 0;
        


        switch(operand1->reg_size)
        {
            case BYTE:
            {
                return encode_byte_instr(opcode, false, REGISTER_ADDRESSING, 2, (unsigned char)operand1->reg, false, false, &operand2->uimm8, 1);
            }

            case WORD:
            {
                return encode_byte_instr(opcode, false, REGISTER_ADDRESSING, 2, (unsigned char)operand1->reg, false, args->config->bits != BITS16, &operand2->uimm8, (operand2->type == IMM8) ? 1 : 2);
            }

            case DWORD:
            {
                return encode_byte_instr(opcode, false, REGISTER_ADDRESSING, 2, (unsigned char)operand1->reg, false, args->config->bits == BITS16, &operand2->uimm8, (operand2->type == IMM8) ? 1 : 4);
            }

            case QWORD:
            {
                if(operand2->type == IMM64)
                {
                    return (struct EncodedInstruction)
                    {
                        .ok = false,
                        .error_message = "Unmatched operand sizes",
                    };
                }

                return encode_byte_instr(opcode, false, REGISTER_ADDRESSING, 2, (unsigned char)operand1->reg, true, false, &operand2->uimm8, (operand2->type == IMM8) ? 1 : 4);
            }

            case SIZE_UNSPECIFIED: {}
        }
    }

    /*
        deref happens
    */
}

#pragma GCC diagnostic pop