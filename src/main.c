#include <stdio.h>
#include <string.h>
#include "CLIParser/CLIParser.h"
#include "Assembler/Assembler.h"

int main(int argc, const char* argv[])
{
    struct Arguments args;
    int error_code = parse_cli(argc, argv, &args);
    if(error_code)
    {
        printf("%s\n", cli_get_error_string(error_code));
    }
    // when CLI arguments are processed now we need to parse the assembly file
    unsigned char* machine_code;
    error_code = assemble_file(args.input_file, &machine_code);

    if(error_code)
    {
        char buffer[128];
        strerror_s(buffer, 128, error_code);
        
        printf("%s : %s\n", args.input_file, buffer);
        return 0;
    }

    free_cli(&args);
}