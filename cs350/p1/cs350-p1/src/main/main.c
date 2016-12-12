/* ************************************************************************* *
 * main.c                                                                    *
 * ------                                                                    *
 *  Author:   CONNER TURNBULL                                                *
 *  Purpose:  This is a template for project 1.                              *
 * ************************************************************************* */


/* ************************************************************************* *
 * Library includes here.  For documentation of standard C library           *
 * functions, see the list at:                                               *
 *   http://pubs.opengroup.org/onlinepubs/009695399/functions/contents.html  *
 * ************************************************************************* */
 
#include <stdio.h>              /* standard I/O */
#include <stdlib.h>
#include <stdbool.h>            /* bool types */
#include <stdint.h>             /* uint32_t, uint8_t, and similar types */
#include <inttypes.h>
#include <string.h>

#include "../cmdline/parse.h"   /* command line parser */
#include "../output/print.h"    /* printer */
#include "../campus/map.h"      /* map utility */


/* ************************************************************************* *
 * Local function declarations                                               *
 * ************************************************************************* */
 int get_file_size(FILE*);

/* ************************************************************************* *
 * Global variable declarations                                              *
 * ************************************************************************* */


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
    /* Your implementation here. */
    int  return_code, file_size;
    FILE *fp;

    uint8_t *array = NULL;

    return_code = parse_command_line (argc, argv);
    if (return_code == 1) return 1;

    /* Open the file and dynamically allocate the array here, using these
     * printf statements as needed for verbose mode

    printf ("Opening file \"%s\"\n", file_name);
    printf ("File contains %" PRIu32 " bytes of data\n", bytes_in_file);

     */


    if (verbose == 1) printf ("Opening file \"%s\"\n", file_name);
    fp = fopen(file_name, "r");

    file_size = get_file_size(fp);
    if (verbose == 1) printf ("File contains %d bytes of data\n", file_size);
    
    array = malloc (file_size * sizeof(uint8_t));
    if (array == NULL) return -1;

    fread(array, 1, file_size, fp);
    fclose(fp);

    if (map_mode == 1)
    {
        int map_return_code;

        building_t *buildings = NULL;
        campus_t *areas = NULL;
        if (verbose == 1) printf("Building campus map\n");
        map_return_code = build_map (file_name, &areas, &buildings);
        if (map_return_code == 1) return 1; //ERRORS!?

        if (building == 1)
        {
            if (verbose == 1) printf("Searching for building code \"%s\"\n",building_arg);
            bldg_t id;
            id = get_building_by_id(building_arg);
            if (id == INVALID_BUILDING_ID) return -1;

            campus_t *cur = areas;
            if (cur -> next == NULL)
            {
                uint8_t iter;
                for (iter = 0; iter  < cur -> number_of_buildings; iter++)
                {
                    if (cur -> list[iter].id == id)
                    {
                        print_building(cur -> list[iter]);
                        break;
                    }
                }
            }
            else
            {
                while (cur -> next != NULL)
                {
                    uint8_t iter;
                    for (iter = 0; iter  < cur -> number_of_buildings; iter++)
                    {
                        if (cur -> list[iter].id == id)
                        {
                            print_building(cur -> list[iter]);
                            break;
                        }
                }
            cur = cur -> next;
            }
            }
        }
        if (area == 1)
        {
            area_t id = get_area_by_id(area_arg);

            campus_t *cur = areas;
            while (cur != NULL)
            {
                if (cur -> id == id)
                {
                    print_area(*cur);
                }
            }
        }
        if (distance == 1)
        {
            const char *from_s = strtok(distance_arg, ":"), 
                       *to_s = strtok(NULL, ":");
            bldg_t from_id = get_building_by_id(from_s),
                   to_id   = get_building_by_id(to_s);
            print_distance(abs(from_id - to_id));
        }
    }
    else //interpret as number
    {
        
        if (decimal == 1)
        {
            print_decimal(array, file_size);
        }
        else if (octal == 1)
        {
            print_octal(array, file_size);
        }
        else
        {
            print_hex(array, file_size);
        }
    }

    free (array);
    array = NULL;

    verbose = 0;

    return 0;
}

int
get_file_size(FILE *fp)
{
    uint32_t size;
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    return size;
}
