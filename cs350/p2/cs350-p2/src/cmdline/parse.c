/* ************************************************************************* *
 * parse.c                                                                   *
 * -------                                                                   *
 *  Author:   Conner Turnbull                                                *
 *  Purpose:  This code is used to parse the command-line arguments for      *
 *            CS 350 project 1.                                              *
 * ************************************************************************* */


/* ************************************************************************* *
 * Library includes here.                                                    *
 * ************************************************************************* */

#include <stdio.h>              /* standard I/O */
#include <unistd.h>             /* declares getopt() */
#include <ctype.h>              /* declares isprint() */

#include "parse.h"              /* prototypes for exported functions */

/* ************************************************************************* *
 * Global variable declarations                                              *
 * ************************************************************************* */
const char *pep8_code_file, *sym_list_file;
uint32_t verbose = 0, interpreter = 0, symbol = 0;;

/* ************************************************************************* *
 * parse_command_line -- parses the command-line arguments using getopt()    *
 *                                                                           *
 * Parameters                                                                *
 *   argc -- the number of command-line arguments                            *
 *   argv -- the array of command-line arguments (array of pointers to char) *
 *                                                                           *
 * Returns                                                                   *
 *   Parsing success status. If the command-line arguments are successfully  *
 *   parsed with no errors, we return the value 0. If any errors occur (such *
 *   as passing an invalid flag or passing a file that does not exist), we   *
 *   return 1 back to the calling function and stop processing               *
 *                                                                           *
 * Notes                                                                     *
 *   This function is designed to be extensible for multiple command-line    *
 *   options. In C, though, you can only return a single value. We get       *
 *   around this restriction by using call-by-reference parameters. For      *
 *   instance, if we want to set a boolean value, the parameter list would   *
 *   be modified as:                                                         *
 *                                                                           *
 *     parse_command_line (..., bool * boolval)                              *
 *                                                                           *
 *   Then, the function would be called from somewhere else like:            *
 *                                                                           *
 *     bool my_bool_value;                                                   *
 *     int return_code;                                                      *
 *     return_code = parse_command_line (..., &my_bool_value);               *
 * ************************************************************************* */

int
parse_command_line (int argc, char **argv)
{
    /*
    uint8_t bin[] = {0xC1, 0x00, 0x0C, 0x18, 0xF1, 0x00, 0x0B, 0x51, 0x00, 0x0B, 0x00, 0x00, 0xF0, 0xD4};
    FILE *fp = fopen("bin1.pep8", "w");
    fwrite(bin, 1, sizeof(bin), fp);
    fclose(fp);
    */

	int c; //getopt option character

    while ((c = getopt(argc, argv, "ivs:")) != -1)
    {
        switch (c)
        {
			case 'i':
                printv("Interpreter invoked.\n");
                interpreter = 1;
				break;
            case 's':
                sym_list_file = optarg;
                symbol = 1;
            case 'v':
                verbose = 1;
                printv("Running in verbose mode\n");
                break;
			default:
				return 1;
        }
    }

    if (interpreter == 0)
    {
        printv("Disassembler invoked.\n");
    }
    pep8_code_file = argv[optind]; //get file name for binary pep8 code

	return 0;
}
