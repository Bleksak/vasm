#include <stdio.h>
#include <string.h>
#include "CLIParser/CLIParser.h"
#include "Assembler/Assembler.h"

int main(int argc, const char* argv[])
{
    /*for(int i = 1; i < argc; ++i)
    {
        printf("%s\n", argv[i]);
    }*/

    struct Arguments args;
    int error_code = parse_cli(argc, argv, &args);
    if(error_code)
    {
        printf("%s\n", cli_get_error_string(error_code));
        return 0;
    }
    // when CLI arguments are processed now we need to parse the assembly file
    unsigned char* machine_code;
    struct AssemblerError error = assemble_file(args.input_file, &machine_code);
    

    if(error.type != ASSEMBLER_ERROR_NONE)
    {
        char buffer[128] = {0};

        if(error.type == ASSEMBLER_ERROR_FILE)
            strerror_s(buffer, 128, error_code);
        else
            get_assembler_error_str(&error, buffer, sizeof(buffer));
        
        printf("%s : %s\n", args.input_file, buffer);
        
        return 0;
    }

    free_cli(&args);
}