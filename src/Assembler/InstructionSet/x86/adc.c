#include "adc.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <stdio.h>

struct EncodedInstruction adc(struct Operand* operand1, struct Operand* operand2, struct Operand* operand3, struct Operand* operand4, bool lock)
{
    if(!operand1->deref)
    {
        if(operand1->type == IMM8 || operand1->type == IMM16 || operand1->type == IMM32 || operand1->type == IMM64)
        {
            return (struct EncodedInstruction)
            {
                .ok = false,
                .error_message = "Instruction adc expects a valid memory operand or a register as first operand.",
            };
        }

        if(lock)
        {
            return (struct EncodedInstruction)
            {
                .ok = false,
                .error_message = "Instruction adc can be used with lock prefix only when destination is memory operand",
            };
        }
        
        // operand1 is a register here

        if(operand1->reg == AX)
        {
            if(operand2->type != REGISTER)
            {
                switch(operand1->reg_size)
                {
                    case BYTE: 
                    {
                        return (operand2->type == IMM8) ? (struct EncodedInstruction)
                        {
                            .ok = true,
                            .size = 2,
                            .value[0] = 0x14,
                            .value[1] = operand2->uimm8,
                        } : (struct EncodedInstruction)
                        {
                            .ok = false,
                            .error_message = "Unmatched operand sizes",
                        };
                    }

                    case WORD:
                    {
                        return (operand2->type == IMM16 || operand2->type == IMM8) ? (struct EncodedInstruction)
                        {
                            .ok = true,
                            .size = 3,
                            .value[0] = 0x15,
                            .value[1] = operand2->uimm32 & 0xFF,
                            .value[2] = (operand2->uimm32 >> 8) & 0xFF,
                        } : (struct EncodedInstruction)
                        {
                            .ok = false,
                            .error_message = "Unmatched operand sizes",
                        };
                    }

                    case DWORD:
                    {
                        return (operand2->type == IMM32 || operand2->type == IMM16 || operand2->type == IMM8) ? (struct EncodedInstruction)
                        {
                            .ok = true,
                            .size = 5,
                            .value[0] = 0x15,
                            .value[1] = operand2->uimm32 & 0xFF,
                            .value[2] = (operand2->uimm32 >> 8) & 0xFF,
                            .value[3] = (operand2->uimm32 >> 16) & 0xFF,
                            .value[4] = (operand2->uimm32 >> 24) & 0xFF,
                        } : (struct EncodedInstruction)
                        {
                            .ok = false,
                            .error_message = "Unmatched operand sizes",
                        };
                    }

                    case QWORD:
                    {
                        return (operand2->type == IMM64 || operand2->type == IMM32 || operand2->type == IMM16 || operand2->type == IMM8) ? (struct EncodedInstruction)
                        {
                            .ok = true,
                            .size = 10,
                            .value[0] = 0x66,
                            .value[1] = 0x15,
                            .value[2] = operand2->uimm64 & 0xFF,
                            .value[3] = (operand2->uimm64 >> 8) & 0xFF,
                            .value[4] = (operand2->uimm64 >> 16) & 0xFF,
                            .value[5] = (operand2->uimm64 >> 24) & 0xFF,
                            .value[6] = (operand2->uimm64 >> 32) & 0xFF,
                            .value[7] = (operand2->uimm64 >> 40) & 0xFF,
                            .value[8] = (operand2->uimm64 >> 48) & 0xFF,
                            .value[9] = (operand2->uimm64 >> 56) & 0xFF,
                        } : (struct EncodedInstruction)
                        {
                            .ok = false,
                            .error_message = "Unmatched operand sizes",
                        };
                    }

                    case SIZE_UNSPECIFIED: {}
                }
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

            switch(operand1->reg_size)
            {
                case BYTE:
                {
                    return encode_byte_instr(0x10, false, REGISTER_ADDRESSING, operand2->reg, (unsigned char)operand1->reg, false, false);
                }

                case WORD:
                {
                    return encode_byte_instr(0x11, false, REGISTER_ADDRESSING, operand2->reg, (unsigned char)operand1->reg, false, true); // LAST TRUE DEPENDS ON BITS, IF 32 OR 64 IS TRUE, IF 16 IS FALSE
                }

                case DWORD:
                {
                    return encode_byte_instr(0x11, false, REGISTER_ADDRESSING, operand2->reg, (unsigned char)operand1->reg, false, false); // SAME AS BEFORE BUT NEGATED
                }

                case QWORD:
                {
                    // 64 bit is different for some reason
                    return encode_byte_instr(0x11, false, REGISTER_ADDRESSING, operand2->reg, (unsigned char)operand1->reg, true, false);
                }

                case SIZE_UNSPECIFIED: {}
            }

        }
        // operand2 is immediate
       

    }
}

#pragma GCC diagnostic pop