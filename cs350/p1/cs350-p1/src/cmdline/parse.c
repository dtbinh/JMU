/* ************************************************************************* *
 * parse.c                                                                   *
 * -------                                                                   *
 *  Author:   CONNER TURNBULL                                                *
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
 * Local function prototypes                                                 *
 * ************************************************************************* */


/* ************************************************************************* *
 * Global variable declarations                                              *
 * ************************************************************************* */
uint8_t verbose = 0, map_mode = 0, building = 0, area = 0, distance = 0,
    decimal = 0, octal = 0, help = 0;
const char *file_name, *building_arg, *area_arg;
char *distance_arg;

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
    int c;

    while ((c = getopt(argc, argv, "vdomb:a:q:h")) != -1)
    {
        switch (c)
        {
            case 'v':   verbose = 1;
                        printf("Running in verbose mode\n");
                        break;
            case 'd':   decimal = 1;
                        break;
            case 'o':   octal = 1;
                        break;
            case 'm':   map_mode = 1;
                        break;
            case 'b':   building = 1;
                        building_arg = optarg;
                        break;
            case 'a':   area = 1;
                        area_arg = optarg;
                        break;
            case 'q':   distance = 1;
                        distance_arg = optarg;
                        break;
            case 'h':   help = 1;
                        break;
            default:    return 1;     
        }
    }

    if (decimal == 1 && octal == 1) return 1; //Invalid input
    if (map_mode == 1 && building == 0 && area == 0 && distance == 0) return 1;
    
    file_name = argv[optind];
    

    return 0;
}
