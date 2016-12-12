#include <stdio.h>
#include <stdlib.h>

#ifndef __CAMPUS_MAP__
#define __CAMPUS_MAP__

/* Enumerated types are helpful in many, many scenarios when the exact number
 * of elements are known. This is similar to creating constants like:
 *
 * #define BLUESTONE 0
 * #define MEMORIAL 1
 * ...
 *
 * The major difference is that these are now real types that the compiler can
 * check. Thus, in code, we can write:
 *
 *   area_t area = BLUESTONE;
 *   printf ("%s Area\n", AREAS[area]);
 *
 * The output would be "Bluestone Area" based on the constants in map-const.c.
 *
 * The following would produce a compiler error with enumerated types, but would
 * not if we just used #define constants:
 *
 *   bldg_t building = MEMORIAL;
 */
typedef enum area_t {
    BLUESTONE, MEMORIAL, HILLSIDE, LAKE, VILLAGE, RIDGE, SKYLINE
} area_t;

/* Helpful constants indicating the number of areas and a special ID for
 * invalid areas.
 */
#define NUMBER_OF_AREAS (SKYLINE + 1)
#define INVALID_AREA_ID -1

typedef enum bldg_t {
    ALUM, AS, ASHB, BELL, BIO, BLUE, BOOK, STDM, BURR, CARD, CaPD, LIBR, MCPD,
    CHAN, CHAP, CHES, CLEV, CONV, CONC, DING, DUKE, EAGL, ECDH, FCSC, FORB,
    FPEC, FRED, FRYE, GARB, GIBB, GIFF, GODW, GSH, GSM, GrPD, GST, GR, HANS,
    HARR, HHS, HCTR, HILL, HLSD, HOFF, HUFF, IKEN, ISAT, JACK, JMAC, JOHN, KEEZ,
    LAC, LOGN, MS, MCP, MASS, MAUR, MCLG, MEMH, MHAC, MILL, MONT, MOOD, CS, MUS,
    PHIL, PCB, PAPC, PMAC, PWRP, QUAD, ROOP, ECL, SHEL, SHEN, SHOR, SONH, SPOT,
    SC, TAYL, USB, VARN, MSS, WAMP, WARR, WaPD, WEAV, WHIT, WILS, WP, ZSH
} bldg_t;

#define NUMBER_OF_BUILDINGS (ZSH + 1)
#define INVALID_BUILDING_ID -1

/* Special hack for a circular definition. Specifically, building_t needs a
 * campus_t member, while campus_t structures also need to reference a
 * building_t list. To appease the compiler, we have to handle this in a special
 * fashion.
 */
struct campus_t;

typedef struct building_t {
    bldg_t id;
    struct campus_t *area;
} building_t;

typedef struct campus_t {
    area_t id;
    building_t *list;
    uint8_t number_of_buildings;
    struct campus_t *next;
} campus_t;

/* Global string constants defined in map-const.c */
extern const char *BUILDINGS[];
extern const char *AREAS[];
extern const char *BUILDING_CODES[];
extern const char *AREA_CODES[];

/* Required interface into map.c */
int build_map (const char *mapfile, campus_t **areas, building_t *buildings[]);
void free_areas (campus_t *root);
bldg_t get_building_by_id (const char *code);
area_t get_area_by_id (const char *code);
uint32_t building_distance (campus_t *root, bldg_t from, bldg_t to);

#endif
