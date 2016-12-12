#include <string.h>
#include <stdio.h>
#include <mxml.h>
#include "logisim.h"

typedef enum { PROJECT, CIRCUIT, COMPONENT } circuit_hierarchy;

/* This CALLBACK function is used by the MXML library to insert whitespace in
 * the correct places when printing out the file */
const char *
whitespace_cb(mxml_node_t *node, int where)
{
    static circuit_hierarchy depth;

    /* mxmlGetElement(node) returns the XML tag name */
    const char * name = mxmlGetElement(node);

    /* highest level XML tag */
    if (!strcmp(name, "project"))
    {
        depth = PROJECT;
        switch (where)
        {
            case MXML_WS_BEFORE_OPEN:   return ("\n");
                                        break;
            case MXML_WS_BEFORE_CLOSE:  return ("\n");
                                        break;
        }

    /* second level incidental tags, includes lib, main, toolbar, circuit */
    } else if (!strcmp (name, "lib") || !strcmp (name, "toolbar") ||
               !strcmp (name, "main") || !strcmp (name, "circuit")) {
        depth = CIRCUIT;
        if (where == MXML_WS_BEFORE_OPEN || where == MXML_WS_BEFORE_CLOSE)
            return ("\n  ");

    /* third level tags, including tool, comp and wire */
    } else if (!strcmp (name, "tool") || !strcmp (name, "comp") ||
               !strcmp (name, "wire")) {
        depth = COMPONENT;
        if (where == MXML_WS_BEFORE_OPEN || where == MXML_WS_BEFORE_CLOSE)
            return ("\n    ");

    /* multi-level tags, specifically a */
    } else if (!strcmp (name, "a")) {
        if (where == MXML_WS_BEFORE_OPEN)
        {
            if (depth == COMPONENT) return ("\n      ");
            else return ("\n    ");
        }
    }

    /*
     * Return NULL for no added whitespace...
     */
    return (NULL);
}

/* This function takes x and y coordinates and returns a string with the values
 * formatted as an ordered pair */
char *
format_coords (int x, int y)
{
    size_t i;
    static char coords[] = "(   ,   )";

    for (i = 3; i > 0; i--)
    {
        coords[i] = (x % 10) + 0x30;
        coords[i+4] = (y % 10) + 0x30;
        x /= 10;
        y /= 10;
    }
    return coords;
}


/*  This helper function generates the necessary header information for a basic
 *  Logisim file.  Specifically, it generates the following XML code:

<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<project source="2.7.1" version="1.0">
This file is intended to be loaded by Logisim (http://www.cburch.com/logisim/).
  <lib desc="#Wiring" name="0"/>
  <lib desc="#Gates" name="1"/>
  <lib desc="#Base" name="2" />
  <main name="main"/>
  <toolbar>
    <tool lib="2" name="Poke Tool"/>
  </toolbar>
  <circuit name="main">
    <a name="circuit" val="main"/>
    <a name="clabel" val=""/>
    <a name="clabelup" val="east"/>
    <a name="clabelfont" val="SansSerif plain 12"/>
  </circuit>
</project>
*/
mxml_node_t *
generate_xml_header (mxml_node_t ** main_circuit, mxml_node_t ** main_project)
{
    /* generate the XML version tag */
    mxml_node_t *xml = mxmlNewXML("1.0");

    /* generate the <project> root node:
       <project source="2.7.1" version="1.0"
     */
    mxml_node_t *project = mxmlNewElement(xml, "project");
    mxmlElementSetAttr (project, "source", "2.7.1");
    mxmlElementSetAttr (project, "version", "1.0");

    /* The Wiring, Gates, and Base Logisim libraries are required in order to
     * display the generated circuit.  The next several lines generate:
       <lib desc="#Wiring" name="0"/>
       <lib desc="#Gates" name="1"/>
       <lib desc="#Base" name="2"/>
     */
    mxml_node_t *lib = mxmlNewElement(project, "lib");
    mxmlElementSetAttr (lib, "desc", "#Wiring");
    mxmlElementSetAttr (lib, "name", "0");

    lib = mxmlNewElement(project, "lib");
    mxmlElementSetAttr (lib, "desc", "#Gates");
    mxmlElementSetAttr (lib, "name", "1");

    lib = mxmlNewElement(project, "lib");
    mxmlElementSetAttr (lib, "desc", "#Base");
    mxmlElementSetAttr (lib, "name", "2");

    /* The main and toolbar tags tell Logisim what tools are needed.  To
     * evaluate a circuit, we only need the poke tool.
     <main name="main"/>
     <toolbar>
       <tool lib="2" name="Poke Tool"/>
     </toolbar>
   */
    mxml_node_t *main_circ = mxmlNewElement (project, "main");
    mxmlElementSetAttr (main_circ, "name", "main");

    mxml_node_t *toolbar = mxmlNewElement (project, "toolbar");
    mxml_node_t *tool = mxmlNewElement (toolbar, "tool");
    mxmlElementSetAttr (tool, "lib", "2");
    mxmlElementSetAttr (tool, "name", "Poke Tool");

    /* Add the main circuit */
    *main_circuit = circuit_module (project, "main");
    *main_project = project;

    /* Return the root XML node */
    return xml;
}

/* Now, start building the main circuit.  We need a circuit tag and some
 * tags for providing some initial values:
   <circuit name="main">
     <a name="circuit" val="main"/>
     <a name="clabel" val=""/>
     <a name="clabelup" val="east"/>
     <a name="clabelfont" val="SansSerif plain 12"/>
   </circuit>
 */
mxml_node_t *
circuit_module (mxml_node_t * project, const char * name)
{
    mxml_node_t * main_circuit;

    mxml_node_t *circuit = mxmlNewElement (project, "circuit");
    mxmlElementSetAttr (circuit, "name", name);
    main_circuit = circuit;

    mxml_node_t *a_box = mxmlNewElement (circuit, "a");
    mxmlElementSetAttr (a_box, "name", "circuit");
    mxmlElementSetAttr (a_box, "val", "main");

    a_box = mxmlNewElement (circuit, "a");
    mxmlElementSetAttr (a_box, "name", "clabel");
    mxmlElementSetAttr (a_box, "val", name);

    a_box = mxmlNewElement (circuit, "a");
    mxmlElementSetAttr (a_box, "name", "clabelup");
    mxmlElementSetAttr (a_box, "val", "east");

    a_box = mxmlNewElement (circuit, "a");
    mxmlElementSetAttr (a_box, "name", "clabelfont");
    mxmlElementSetAttr (a_box, "val", "SansSerif plain 12");

    return main_circuit;
}

/* Generate an input pin at the coordinates provided.  Produces:
   <comp lib="0" loc="(XXX,YYY)" name="Pin">
     <a name="tristate" val="false"/>
   </comp>
 */
void
input_pin (mxml_node_t * main_circuit, int x, int y, const char * name)
{
    mxml_node_t * pin = NULL;
    mxml_node_t * tristate = NULL;
    mxml_node_t * anode = NULL;

    pin = mxmlNewElement (main_circuit, "comp");
    mxmlElementSetAttr (pin, "lib", "0");
    mxmlElementSetAttr (pin, "loc", format_coords (x, y));
    mxmlElementSetAttr (pin, "name", "Pin");

    tristate = mxmlNewElement (pin, "a");
    mxmlElementSetAttr (tristate, "name", "tristate");
    mxmlElementSetAttr (tristate, "val", "false");

    anode = mxmlNewElement (pin, "a");
    mxmlElementSetAttr (anode, "name", "label");
    mxmlElementSetAttr (anode, "val", name);

    anode = mxmlNewElement (pin, "a");
    mxmlElementSetAttr (anode, "name", "labelfont");
    mxmlElementSetAttr (anode, "val", "SansSerif plain 12");
}

/* Generate an output pin at the coordinates provided.  Produces:
   <comp lib="0" loc="(XXX,YYY)" name="Pin">
     <a name="output" val="true"/>
     <a name="facing" val="west"/>
     <a name="labelloc" val="east"/>
   </comp>
 */
void
output_pin (mxml_node_t * main_circuit, int x, int y, const char * name)
{
    mxml_node_t * pin = NULL;;
    mxml_node_t * anode = NULL;

    pin = mxmlNewElement (main_circuit, "comp");
    mxmlElementSetAttr (pin, "lib", "0");
    mxmlElementSetAttr (pin, "loc", format_coords (x, y));
    mxmlElementSetAttr (pin, "name", "Pin");

    anode = mxmlNewElement (pin, "a");
    mxmlElementSetAttr (anode, "name", "output");
    mxmlElementSetAttr (anode, "val", "true");

    anode = mxmlNewElement (pin, "a");
    mxmlElementSetAttr (anode, "name", "facing");
    mxmlElementSetAttr (anode, "val", "west");

    anode = mxmlNewElement (pin, "a");
    mxmlElementSetAttr (anode, "name", "labelloc");
    mxmlElementSetAttr (anode, "val", "east");

    anode = mxmlNewElement (pin, "a");
    mxmlElementSetAttr (anode, "name", "label");
    mxmlElementSetAttr (anode, "val", name);

    anode = mxmlNewElement (pin, "a");
    mxmlElementSetAttr (anode, "name", "labelfont");
    mxmlElementSetAttr (anode, "val", "SansSerif plain 12");
}

/* <comp lib="1" loc="(XXX,YYY)" name="NOT Gate"/> */
void
inverter (mxml_node_t * main_circuit, int x, int y)
{
    mxml_node_t * inverter = mxmlNewElement (main_circuit, "comp");
    mxmlElementSetAttr (inverter, "lib", "1");
    mxmlElementSetAttr (inverter, "loc", format_coords (x, y));
    mxmlElementSetAttr (inverter, "name", "NOT Gate");
}


/* Generate a wire connecting two points, specified as coordinates:
   <wire from="(FFX,FFY)" to="(TTX,TTY)"/>
 */
void
wire (mxml_node_t * main_circuit, int fromx, int fromy, int tox, int toy)
{
    mxml_node_t * wire = mxmlNewElement (main_circuit, "wire");
    mxmlElementSetAttr (wire, "from", format_coords (fromx, fromy));
    mxmlElementSetAttr (wire, "to", format_coords (tox, toy));
}

/* Generates an AND-gate at the provided coordinates for the minterm
 * specified:
   <comp lib="1" loc="(XXX,YYY)" name="AND Gate">
     <a name="size" val="30"/>
     <a name="inputs" val="2"/>
   </comp>
 * Note that the nega and negb booleans are used to specify whether or not the
 * input bits need to be negated. For instance, if nega was true, the following
 * line would be added to the component:
     <a name="negate0" val="true"/>
 */
void
andgate (mxml_node_t * main_circuit, int x, int y, bool nega, bool negb)
{
    mxml_node_t * anode = NULL;
    mxml_node_t * andgate;

    andgate = mxmlNewElement (main_circuit, "comp");
    mxmlElementSetAttr (andgate, "lib", "1");
    mxmlElementSetAttr (andgate, "loc", format_coords (x, y));
    mxmlElementSetAttr (andgate, "name", "AND Gate");

    anode = mxmlNewElement (andgate, "a");
    mxmlElementSetAttr (anode, "name", "size");
    mxmlElementSetAttr (anode, "val", "30");

    anode = mxmlNewElement (andgate, "a");
    mxmlElementSetAttr (anode, "name", "inputs");
    mxmlElementSetAttr (anode, "val", "2");

    if (nega)
    {
        anode = mxmlNewElement (andgate, "a");
        mxmlElementSetAttr (anode, "name", "negate0");
        mxmlElementSetAttr (anode, "val", "true");
    }
    if (negb)
    {
        anode = mxmlNewElement (andgate, "a");
        mxmlElementSetAttr (anode, "name", "negate1");
        mxmlElementSetAttr (anode, "val", "true");
    }
}
