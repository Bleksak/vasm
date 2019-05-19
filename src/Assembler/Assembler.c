#include "Assembler.h"
#include "InstructionSet/Instruction.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static void closef(FILE** file)
{
    if(*file)
        fclose(*file);
}

int assemble_file(const char* restrict filename, unsigned char* restrict * restrict output)
{
    *output = 0; // initialize to 0

    __attribute__((cleanup(closef))) FILE* file;
    errno_t error_code = fopen_s(&file, filename, "r");
    
    if(error_code)
    {
        //something is wrong with the file
        return error_code;
    }

    char line[2048];

    while(fgets(line, 2048, file))
    {
        char instruction_name[32];
        bool lock = false;

        int offset;

        if(line[0] == ';')
            continue; // comment

        if(sscanf_s(line, "%s%n", instruction_name, 32, &offset) != 1)
        {
            // probably empty line
            continue;
        }

        const char* line_value = (line + offset + 1);

        for (char* _str_copy = instruction_name; *_str_copy; ++_str_copy) *_str_copy = (char)tolower(*_str_copy);
        if(strcmp(instruction_name, "lock") == 0)
        {
            lock = true;
            if(sscanf_s(line_value, "%s%n", instruction_name, 32, &offset) != 0)
            {
                // maybe we continue on the next line, ignore for now
                return 0;
            }
            for (char* _str_copy = instruction_name; *_str_copy; ++_str_copy) *_str_copy = (char)tolower(*_str_copy);
            line_value = (line_value + offset + 1);
        }

        const struct X86_Instruction* instr = find_x86_instruction(instruction_name);
        
        if(!instr)
        {
            return 0; // instruction wasnt found, return an error
        }
        
        if(lock && !instr->supports_lock)
        {
            //lock used on instruction that doesnt support it
            return 0;
        }
        
        /*
            get all operands
        */

        struct Operand operands[4];

        for(unsigned int i = 0; i < instr->takes_args; ++i)
        {
            char operand[256];
            if(sscanf_s(line_value, "%s,%n", operand, 256, &offset) != 1)
            {
                // not enough operands supplied
                return 0;
            }

            for (char* _str_copy = operand; *_str_copy; ++_str_copy) *_str_copy = (char)tolower(*_str_copy);

            line_value = (line_value + offset + 1);

            get_x86_operand(&operands[i], operand);
        }

        struct EncodedInstruction encoded = instr->parse(&operands[0], &operands[1], &operands[2], &operands[3], lock);
        printf("%x\n", encoded.value[0]);
    }

    return 0;
}