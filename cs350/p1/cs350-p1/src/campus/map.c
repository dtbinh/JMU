/*************************************************************************** *
 * Include statements
 *************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h> //stringy
#include "map.h"

/*************************************************************************** *
 * Builds the map of the campus in memory
 *************************************************************************** */
int
build_map (const char *mapfile, campus_t **areas, building_t *buildings[])
{
    int fsize;
    FILE *fp;

    uint8_t *farr; //array of file contents

    fp = fopen(mapfile, "r");
    fseek(fp, 0L, SEEK_END);
    fsize = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    farr = malloc (fsize * sizeof(uint8_t));
    if (farr == NULL) return 1;
    fread (farr, 1, fsize, fp);
    fclose(fp);

    campus_t *head;
    head = malloc( sizeof(campus_t) );
    if (head == NULL) return 1;
    head -> next = NULL;
    *areas = head;
    campus_t *cur = *areas; //for linked list traversal

    uint8_t iter;
    int8_t area = -1, num_bldg = 0, total_bldg = 0;
    for (iter = 0; iter < fsize; iter++)
    {
        cur = *areas;       
        /* if area < 0, then this byte is the area byte. Use it to create
         * the new node at the end of the linked list.
         */
        if (area < 0)
        {
            area = farr[iter];
            if (area < 0 || area >= NUMBER_OF_AREAS) return 1;
            
            //traverse the linked list
            if (cur -> next != NULL)
            {
                while (cur -> next != NULL)
                {
                    cur = cur -> next;
                }
            }
            //create new node. do magic to it
            cur -> next = malloc (sizeof(campus_t));
            if (cur -> next == NULL) return 1;
            cur -> id = area;
            cur = cur -> next;
            cur -> next = 0;
        }
        /* if area >= 0 and num_bldg == 0, then this is the byte signifying the
         * number of buildings. Set it to num_bldg, then iterate over the
         * building bytes and build the building list.
         */
        else if (area >= 0 && num_bldg == 0)
        {
            //get number of buildings from file
            num_bldg = farr[iter];
            total_bldg += num_bldg;

            //declare and initialize bldgs to have the buildings listed in file
            building_t bldgs[num_bldg];

            bldg_t temp_iter;
            uint8_t bldg_iter = 0;
            for (temp_iter = iter+1; temp_iter <= iter + num_bldg; temp_iter++)
            {
                if (farr[temp_iter] < 0 || farr[temp_iter] >= NUMBER_OF_BUILDINGS)
                    return 1;
                cur = *areas;
                if (cur -> next != NULL)
                    while (cur -> next != NULL) cur = cur -> next;
                //create new building_t
                building_t new_building;
                new_building.id = (bldg_t)farr[temp_iter];
                new_building.area = cur;
                bldgs[bldg_iter] = new_building;
                bldg_iter++;
            }
            iter = temp_iter;

            //now traverse linked list to find correct node to place bldgs in
            cur = *areas;
            if (cur -> next != NULL)
            {
                while (cur -> next != NULL)
                {
                    cur = cur -> next;
                }
            }
            //place bldgs and num_bldg in node;
            cur -> number_of_buildings = num_bldg;
            cur -> list = bldgs;
            //done. set num_bldg to 0 and area = -1 for next iteration
            num_bldg = 0;
            area = -1;
        }
    } //end for loop

    /* New while loop to construct buildings */
    if (total_bldg == 0) return 1; //shouldn't happen
    *buildings = malloc(total_bldg * sizeof(building_t));
    int current_loc = 0; //for keeping track of where you are in the array
    cur = *areas;
    if (cur -> next == NULL)
    {   
        uint8_t temp;
        for (temp = 0; temp < cur -> number_of_buildings; temp++)
        {   
            *buildings[current_loc] = cur -> list[temp];
            current_loc++;
        }
        cur = cur -> next;
    }
    else
    {
        while (cur -> next != NULL)
        {
            uint8_t temp;
            for (temp = 0; temp < cur -> number_of_buildings; temp++)
            {
                *buildings[current_loc] = cur -> list[temp];
                current_loc++;
            }
            cur = cur -> next;
        }
    }
    cur = *areas;
    //printf("%d\n",cur->list[0].id);
    return 0;
}

void
free_areas (campus_t *root)
{
    campus_t *cur = root;
    while (cur != NULL)
    {
        campus_t *temp = cur;
        cur = cur -> next;
        free(temp -> list);
    }

}

bldg_t
get_building_by_id (const char *code)
{
    uint8_t iter;

    for (iter = 0; iter < NUMBER_OF_BUILDINGS; iter++)
    {
        if (strcmp(code, BUILDING_CODES[iter]) == 0) return (bldg_t) iter;
    }
    return INVALID_BUILDING_ID;
}

area_t
get_area_by_id (const char *code)
{
    uint8_t iter;
    for (iter = 0; iter < NUMBER_OF_AREAS; iter++)
    {
        if(strcmp(code, AREA_CODES[iter]) == 0) return (area_t) iter;
    }
    return INVALID_AREA_ID;
}

uint32_t
building_distance (campus_t *root, bldg_t from, bldg_t to)
{
    int32_t from_area = -1, to_area = -1;
    campus_t *cur = root;
    if (cur != NULL)
    {
        while (cur -> next != NULL)
        {
            uint8_t iter;
            for (iter = 0; iter < cur -> number_of_buildings; iter++)
            {
                if (cur -> list[iter].id == from)
                {
                    from_area = cur -> id;
                }
                if (cur -> list[iter].id == to)
                {
                    to_area = cur -> id;
                }
            }
        }

    }
    return abs(to_area - from_area);
}
