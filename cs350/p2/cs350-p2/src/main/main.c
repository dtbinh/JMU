/* ************************************************************************* *
 * main.c                                                                    *
 * ------                                                                    *
 *  Author:   Conner Turnbull                                                *
 *  Purpose:  Entry point of the program                                     *
 * ************************************************************************* */


/* ************************************************************************* *
 * Library includes here.  For documentation of standard C library           *
 * functions, see the list at:                                               *
 *   http://pubs.opengroup.org/onlinepubs/009695399/functions/contents.html  *
 * ************************************************************************* */
 
#include <stdio.h>              /* standard I/O */
#include <stdbool.h>            /* bool types */
#include <stdint.h>             /* uint32_t, uint8_t, and similar types */

#include "../cmdline/parse.h"   /* command line parser */
#include "../output/print.h"
#include "../machine/disassemble.h"
#include "../machine/interpret.h"


/* ************************************************************************* *
 * Local function declarations                                               *
 * ************************************************************************* */
int open_file (const char **, uint8_t **);
int fsize (FILE **);
int allocate_array (uint8_t **, uint32_t);

/* ************************************************************************* *
 * Global variable declarations                                              *
 * ************************************************************************* */
uint8_t *memory;
uint32_t arr_size;

/* ************************************************************************* *
 * main -- main entry point into the program.                                *
 *                                                                           *
 * Parameters                                                                *
 *   argc -- the number of command-line arguments                            *
 *   argv -- the array of command-line arguments (array of pointers to char) *
 *                                                                           *
 * Returns                                                                   *
 *   Program exit status. The standard is to return 0 for normal exit (no    *
 *   errors occurred). If something unusual happens, return some number      *
 *   other than 0, which can then indicate to the user what happened.        *
 *                                                                           *
 * Notes                                                                     *
 *   This function is similar to the "public static void Main" method used   *
 *   in Java classes.                                                        *
 * ************************************************************************* */

int
main (int argc, char **argv)
{
    int return_code;
    
    //Parse command line
    return_code = parse_command_line (argc, argv);
    if (return_code)
    {
        printv("main/main.c/main:\tparse_command_line() did not return "
                    "successfully. Exiting program.\n");
        printv ("Return code is %d\n", return_code);
        return return_code;
    }

    // Open code file
    memory = NULL;
    arr_size = open_file (&pep8_code_file, &memory);
    if (arr_size == 0)
    {
        printv("main/main.c/main:\topen_file() did not successfully open "
                    "pep8_code_file. Exiting program.\n");
        printv ("Return code is %d\n", 1);
        return 1;
    }

    //Disassemble
    if (interpreter == 0)
    {
        //build instruction list
        instruction_t *list = NULL;
        //NOTE: I did not implement the symbol table. Input that contains
        //data, symbols, or pseudo ops cannot be disambiguated and may
        //result in incorrect output, or a segmentation fault
        return_code = disassemble (&list, &memory, arr_size);
        if (return_code)
        {
            printv("main/main.c/main():\tError disassembling. Exiting.\n");
            printv ("Return code is %d\n", 1);
            return return_code;
        }
        
        //Print list
        print_dis(&list);
        free_list (&list);
    }

    // Interpret
    else
    {
        return_code = interpret(&memory, arr_size);
        if (return_code)
        {
            printv("main/main.c/main():\tError interpreting. Exiting.\n");
            printv ("Return code is %d\n", 1);
            return return_code;
        }
    }

    free (memory);
    memory = NULL;
    //End of main
    printv ("Return code is %d\n", return_code);
    return return_code;
}


/* ************************************************************************* *
 * open_file -- places the steps for opening a file here instead of          *
 *              cluttering main(). First, opens the file. Second,            *
 *              dynamically allocates the array. Third, populates the array  *
 *              data from the file. Finally, closes the file.                *
 *                                                                           *
 * Parameters                                                                *
 *   file -- the file in question                                            *
 *   array -- Null pointer to be populated by the file                       *
 *                                                                           * 
 * Returns                                                                   *
 *   Size of the file. If 0 is returned, an error occured                    *
 * ************************************************************************* */

 int
 open_file (const char ** file, uint8_t ** memory)
 {
    //Local variables
    FILE * fstream;
    int return_code;
    const char * fname = * file;
    uint8_t * mem = * memory;
    int bytes_in_file = 0;

    // Open file
    printv ("Opening file \"%s\"\n", fname);
    fstream = fopen (fname, "rb");
    if (fstream == NULL)
    {
        printv ("main/main.c/open_file:\tFILE does not exist. Returning to "
                    "main.\n");
        return 0;
    }
    
    bytes_in_file = fsize(&fstream);
    printv ("File contains %" PRIu32 " bytes of data\n", bytes_in_file);
    
    //Allocate array
    return_code = allocate_array (&mem, bytes_in_file);
    if (return_code)
    {
        printv("main/main.c/open_file:\tallocate_array did not return "
                    "correctly. Returning to main.");
        return 0;
    }

    //Populate array with file data
    fread( mem, 1, bytes_in_file, fstream);   
    fclose (fstream);
    
    if (mem == NULL)
    {
        printv("main/main.c/open_file:\tarray returned null. Returning to main.\n");

        return 0;
    }
    * memory = mem;
    return bytes_in_file;
 }

/* ************************************************************************* *
 * fsize -- calculates size of a given file                                  *
 *                                                                           *
 * Parameters                                                                *
 *   file -- reference to file in question                                   *
 *                                                                           * 
 * Returns                                                                   *
 *   File size.                                                              *
 * ************************************************************************* */

int
fsize (FILE ** fp)
{
    FILE * file = * fp;
    uint32_t size = NULL;

    fseek (file, 0, SEEK_END);
    size = ftell(file);
    fseek (file, 0, SEEK_SET);

    return size;
}

/* ************************************************************************* *
 * allocate_array -- dynamically allocates an array                          *
 *                                                                           *
 * Parameters                                                                *
 *   array - pass-by-reference to the array                                  *
 *   size - required size                                                    *
 *                                                                           * 
 * Returns                                                                   *
 *   Program exit status. Returns 0 for normal exit (no erros occured). If   *
 *   something unusual occurs, returns 1.                                    *
 * ************************************************************************* */
int
allocate_array (uint8_t ** array, uint32_t size)
{
    uint8_t * arr = * array;
    arr = malloc (size * sizeof(uint8_t));
    if (arr == NULL) return 1;
    * array = arr;
    return 0;
}
