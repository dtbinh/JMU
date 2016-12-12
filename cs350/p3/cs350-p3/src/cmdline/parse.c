/* ************************************************************************* *
 * parse.c                                                                   *
 * -------                                                                   *
 *  Author:   Conner Turnbull                                                *
 *  Purpose:  This code is used to parse the command-line arguments for      *
 *            CS 350 project 3.                                              *
 * ************************************************************************* */


/* ************************************************************************* *
 * Library includes here.                                                    *
 * ************************************************************************* */

#include <stdio.h>              /* standard I/O */
#include <unistd.h>             /* gives us getopt() */
#include <ctype.h>              /* gives us isprint() */
#include <stdlib.h>

#include "parse.h"              /* prototypes for exported functions */

/* ************************************************************************* *
 * Global variable declarations                                              *
 * ************************************************************************* */
const char * input_file, * output_file;
int produce_ast = 0, produce_xml = 0, verbose = 0;

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
parse_command_line (int argc, char ** argv)
{
	int c; //getopt option character

    while ((c = getopt(argc, argv, "co:")) != -1)
    {
        switch (c)
        {
			case 'c':
                produce_ast = 1;
				break;
            case 'o':
                produce_xml = 1;
                output_file = optarg;
            case 'v':
                verbose = 1;
                printv("Running in verbose mode\n");
			default:
				return 1;
        }
    }
    input_file = argv[optind];
    return 0;
}

/* ************************************************************************* *
 * printv -- When verbose, prints  messages in green. This is a near direct  *
 *           copy of printf                                                  *
 *                                                                           *
 * Parameters                                                                *
 *   msg -- the message to be printed                                        *
 *                                                                           * 
 * Returns                                                                   *
 *   If successful, the total number of characters written is returned.      *
 *   On failure, a negative number is returned.                              *
 *   http://www.tutorialspoint.com/c_standard_library/c_function_printf.htm  *
 * ************************************************************************* */

 int
 printv (char *format, ...)
 {
    va_list arg;
    int done;

    if (verbose)
    {
        va_start (arg, format);
        done = vfprintf (stdout, format, arg);
        va_end (arg);

    }
    else
    {
        va_start (arg, format);
        done = 0;
        va_end (arg);
    }

    return done;
 }
