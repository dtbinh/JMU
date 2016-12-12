#ifndef __LOGISIM_HEADER__
#define __LOGISIM_HEADER__
#include <mxml.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */
const char * whitespace_cb(mxml_node_t *node, int where);
char * format_coords (int x, int y);
mxml_node_t * generate_xml_header (mxml_node_t ** main, mxml_node_t ** project);

mxml_node_t * circuit_module (mxml_node_t * project, const char * name);
void input_pin (mxml_node_t * main_circuit, int x, int y, const char * name);
void output_pin (mxml_node_t * main_circuit, int x, int y, const char * name);
void inverter (mxml_node_t * main_circuit, int x, int y);
void wire (mxml_node_t * main_circuit, int fromx, int fromy, int tox, int toy);
void andgate (mxml_node_t * main_circuit, int x, int y, bool nega, bool negb);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
