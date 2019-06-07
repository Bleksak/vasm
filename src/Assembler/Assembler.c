#include "Assembler.h"
#include "InstructionSet/Instruction.h"
#include <string.h>
#include <ctype.h>
#include "InstructionSet/x86/x86.h"

#include <stdlib.h>

static void closef(FILE** file)
{
    if(*file)
        fclose(*file);
}

static void freeptr(struct x86_config** ptr)
{
    if(*ptr)
        free(*ptr);
}

struct AssemblerError assemble_file(const char* restrict filename, unsigned char* restrict * restrict output)
{
    *output = 0; // initialize to 0

    __attribute__((cleanup(closef))) FILE* file;
    errno_t error_code = fopen_s(&file, filename, "r");
    
    if(error_code)
    {
        //something is wrong with the file
        return (struct AssemblerError)
        {
            .type = ASSEMBLER_ERROR_FILE,
            .code = error_code
        };
    }

    __attribute__((cleanup(freeptr))) struct x86_config* config = calloc(1, sizeof(struct x86_config));

    char line[2048];

    for(int line_num = 1; fgets(line, 2048, file); ++line_num)
    {
        char instruction_name[32];
        bool lock = false;

        int offset;

        if(sscanf_s(line, "%s%n", instruction_name, 32, &offset) != 1)
        {
            // probably empty line
            continue;
        }

        if(instruction_name[0] == ';')
            continue; // comment

        const char* line_value = (line + offset);

        for (char* _str_copy = instruction_name; *_str_copy; ++_str_copy) *_str_copy = (char)tolower(*_str_copy);
        if(strcmp(instruction_name, "lock") == 0)
        {
            lock = true;
            if(sscanf_s(line_value, "%s%n", instruction_name, 32, &offset) != 0)
            {
                // maybe we continue on the next line, ignore for now
                return (struct AssemblerError)
                {
                    .type = ASSEMBLER_ERROR_ASM,
                    .code = ASSEMBLER_SYNTAX_ERROR,
                    .line = line_num,
                };
            }
            for (char* _str_copy = instruction_name; *_str_copy; ++_str_copy) *_str_copy = (char)tolower(*_str_copy);
            line_value = (line_value + offset + 1);
        }

        const struct config_keyword* conf = get_assembler_keyword(instruction_name);

        if(conf)
        {
            const struct x86_option opt = conf->handle(config, line_value);
            if(!opt.ok)
            {
                return (struct AssemblerError)
                {
                    .type = ASSEMBLER_ERROR_ASM,
                    .code = ASSEMBLER_INSTRUCTION_ERROR_CUSTOM,
                    .line = line_num,
                    .error_message = opt.message,
                };
            }
            continue;
        }

        const struct X86_Instruction* instr = find_x86_instruction(instruction_name);
        
        if(!instr)
        {
            return (struct AssemblerError)
            {
                .type = ASSEMBLER_ERROR_ASM,
                .code = ASSEMBLER_NO_INSTR,
                .line = line_num,
            };  // instruction wasnt found, return an error
        }

        if(lock && !instr->supports_lock)
        {
            //lock used on instruction that doesnt support it
            return (struct AssemblerError)
            {
                .type = ASSEMBLER_ERROR_ASM,
                .code = ASSEMBLER_NO_LOCK,
                .line = line_num,
            };
        }
        
        /*
            get all operands
        */
        struct Operand operands[4] = {{0}, {0}, {0}, {0}};
        
        for(unsigned int i = 0; i < instr->takes_args; ++i)
        {
            char operand[256] = {0};
            if(sscanf_s(line_value, "%s%n", operand, 256, &offset) != 1)
            {
                if(instr->arg_optional) // if they were optional, just skip
                {
                    break;
                }
                // not enough operands supplied
                return (struct AssemblerError)
                {
                    .type = ASSEMBLER_ERROR_ASM,
                    .code = ASSEMBLER_NOT_ENOUGH_OPERANDS,
                    .line = line_num,
                    // maybe add instruction name and some value so we could specify how many operands does the instruction expect
                };
            }

            for (char* _str_copy = operand; *_str_copy; ++_str_copy) *_str_copy = (char)tolower(*_str_copy);
            
            line_value = (line_value + offset + 1);
            
            get_x86_operand(&operands[i], operand);
        }

        struct EncodedInstruction encoded = instr->parse(&operands[0], &operands[1], &operands[2], &operands[3], lock);
        if(!encoded.ok)
        {
            return (struct AssemblerError)
            {
                .type = ASSEMBLER_ERROR_ASM, 
                .code = ASSEMBLER_INSTRUCTION_ERROR_CUSTOM, 
                .error_message = encoded.error_message,
                .line = line_num,
            };
        }


        for(unsigned int i = 0; i < encoded.size; ++i)
        {
            printf("%x ", encoded.value[i]);
        }
        printf("\n");
    }

    return (struct AssemblerError)
    {
        .type = ASSEMBLER_ERROR_NONE
    };
}