#include <stdint.h>
#include <inttypes.h>

#include "print.h"


void
print_area (campus_t area)
{
    printf("%s Area (%d buildings):", AREAS[area.id], area.number_of_buildings);
    uint8_t temp;
    for (temp = 0; temp < area.number_of_buildings; temp++)
    {
        printf("    %s", BUILDINGS[area.id]);
    }
}

void
print_building (building_t building)
{
    campus_t area_id;
    area_id = *building.area;
    printf("%s is in %s Area", BUILDINGS[building.id], AREAS[area_id.id]);
}

void
print_distance (uint32_t distance)
{
    if (distance == 0)
    {
        printf("You can make it betweren them in less than 5 minutes\n");
    }
    else if (distance == 1)
    {
        printf("You can make it between them in 5 minutes\n");
    }
    else if (distance == 2)
    {
        printf("You can make it in 10 minutes if you hurry\n");
    }
    else
    {
        printf("This would take more than 15 minutes and cannot be done\nPick a new class\n");
    }
}

void
print_decimal(uint8_t *array, int size)
{
    if (verbose == 1)
     {
         printf("Running in numeric mode\n");
         printf("Output will be in decimal format\n");
     }
    uint8_t iter;
    uint8_t limit_output = 0;
    for (iter = 0; iter < size; iter++)
    {
        if (limit_output >= 80)
        {
            printf("\n");
            limit_output = 0;
        }
        printf("%03" PRIu8 " ", array[iter]);
        limit_output += 4;
    }
    decimal = 0;
    printf("\n");
}

void
print_octal(uint8_t *array, int size)
{
    if (verbose)
     {
         printf("Running in numeric mode\n");
         printf("Output will be in octal format\n");
     }
    uint8_t iter;
    uint8_t limit_output = 0;
    for (iter = 0; iter < size; iter++)
    {
        if (limit_output >= 80)
        {
            printf("\n");
            limit_output = 0;
        }
        printf("%03" PRIo8 " ", array[iter]);
        limit_output += 4;
    }
    octal = 0;
    printf("\n");
}

void print_hex(uint8_t *array, int size)
{
    if (verbose)
     {
         printf("Running in numeric mode\n");
         printf("Output will be in hexadecimal format\n");
     }
    uint8_t iter;
    uint8_t limit_output = 0;
    for (iter = 0; iter < size; iter++)
    {
        if (limit_output >= 80)
        {
            printf("\n");
            limit_output = 0;
        }
        printf("%02" PRIX8 " ", array[iter]);
        limit_output += 3;
    }
    printf("\n");
}
