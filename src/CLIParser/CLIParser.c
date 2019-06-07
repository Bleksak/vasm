#include "CLIParser.h"
#include <string.h>

struct cli_check
{
    bool input_file;
    bool output_file;
};

// returns how many positions we increment index by
// or -1 for error

static int parse_argument(int index, int max_index, const char * restrict argv[], struct Argument * restrict arg, struct cli_check * restrict check)
{
    if(argv[index][0] == '-')
    {
        if(argv[index][1] == '-')
        {
            return CLI_NOT_SUPPORTED; // long names not supported yet
        }

        if(strlen(argv[index]) != 2) /* -o => 2 chars ! */
            return CLI_INVALID_ARGUMENT;

        switch(argv[index][1])
        {
            case 'o':
            {
                if((index + 1) == max_index)
                    return CLI_REQUIRES_VALUE; // we cannot access index + 1 because index is the last element

                if(check->output_file)
                    return CLI_OUTPUT_SET; // output file is already set, why set it twice?

                if(strlen(argv[index+1]) == 0)
                    return CLI_FILENAME_EMPTY; // output file name is empty

                arg->type = ARG_VALUE_STRING;
                arg->arg = ARG_OUTPUT;
                arg->strVal = argv[index + 1];

                check->output_file = true;

                return 1; // skip 1
            }


            default: return CLI_INVALID_ARGUMENT;
        }
    }

    if(strlen(argv[index]) == 0)
      return CLI_FILENAME_EMPTY; // input file name is empty

    if(check->input_file)
      return CLI_INPUT_SET; // input file already set, why set it again

    arg->type = ARG_VALUE_STRING;
    arg->arg = ARG_INPUT;
    arg->strVal = argv[index];
    
    check->input_file = true;

    return 0; // dont skip any
}

int parse_cli(int argc, const char* argv[], struct Arguments* restrict arguments)
{
    if(argc < 2) // probably print help here
        return -(CLI_PRINT_HELP + 1);

    arguments->arguments = 0;
    arguments->count = 0;

    struct cli_check check = {0};

    for(int i = 1; i < argc; ++i)
    {
        struct Argument arg;
        int result = parse_argument(i, argc, argv, &arg, &check);

        if(result < 0)
        {
            free(arguments->arguments);
            return -(result + 1);
        }

        if(arg.arg == ARG_INPUT)
        {
            arguments->input_file = arg.strVal;
        }
        else if(arg.arg == ARG_OUTPUT)
        {
            arguments->output_file = arg.strVal;
        }
        else
        {
            void* tmp = realloc(arguments->arguments, (arguments->count + 1) * sizeof(struct Argument));
            if(!tmp)
            {
                free(arguments->arguments); // out of memory
                return -(CLI_OUT_OF_MEMORY + 1);
            }

            arguments->arguments = (struct Argument*)tmp;
            memcpy_s(&arguments->arguments[arguments->count], sizeof(struct Argument), &arg, sizeof(struct Argument));
        }
        
        i += result;
    }

    if(!check.input_file)
    {
        return -(CLI_NO_INPUT_FILE + 1); // no input file or output file specified
    }

    if(!check.output_file)
    {
        return -(CLI_NO_OUTPUT_FILE + 1);
    }

    return 0;
}