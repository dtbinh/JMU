/* ************************************************************************* *
 * disassemble.c                                                             *
 * ------                                                                    *
 *  Author:   Conner Turnbull                                                *
 *  Purpose:  Disassembles instructions to assembly                          *
 * ************************************************************************* */

/* ************************************************************************* *
 * Library includes here.  For documentation of standard C library           *
 * functions, see the list at:                                               *
 *   http://pubs.opengroup.org/onlinepubs/009695399/functions/contents.html  *
 * ************************************************************************* */

#include "disassemble.h"
#include "../output/print.h"
 
/* ************************************************************************* *
 * Local function declarations                                               *
 * ************************************************************************* */
int build_list(uint8_t **, instruction_t **, uint32_t);
int is_unary (uint8_t);
int get_mnemonic(uint8_t, char**);
int get_addressing_mode(uint8_t, char**);

/* ************************************************************************* *
 * Global variable declarations                                              *
 * ************************************************************************* */
 char *output;

/* ************************************************************************* *
 * disassemble - the entry point for this file.                              *
 *                                                                           *
 * Parameters                                                                *
 *   code_array -- array of uint8_t that contains instructions and opspecs   *
 *   bytes_in_array -- the size of the array                                 *
 *                                                                           *
 * Returns                                                                   *
 *   Program exit status. The standard is to return 0 for normal exit (no    *
 *   errors occurred). If something unusual happens, return some number      *
 *   other than 0, which can then indicate to the user what happened.        *
 * ************************************************************************* */
 int
 disassemble(instruction_t **list, uint8_t **code_array, uint32_t bytes_in_array)
 {
    instruction_t * root;
    int return_code;

    root = *list;

    //build the list
    return_code = build_list (code_array, &root, bytes_in_array);
    if (return_code == 1)
    {
        printv("machine/disassemble.c/disassemble():\tError in build_list(). "
               "Exiting.\n");
        return 1;
    }

    *list = root;
    return 0;
 }

/* ************************************************************************* *
 * build_list - builds the linked list, where each node is a instruction_t   *
 *              struct.                                                      *
 *                                                                           *
 * Parameters                                                                *
 *   code_array -- array of uint8_t that contains instructions and opspecs   *
 *   list -- the initial root of the list. Not initialized                   *
 *   bytes_in_array -- the size of the array                                 *
 *                                                                           *
 * Returns                                                                   *
 *   Program exit status. The standard is to return 0 for normal exit (no    *
 *   errors occurred). If something unusual happens, return some number      *
 *   other than 0, which can then indicate to the user what happened.        *
 * ************************************************************************* */
 int
 build_list(uint8_t **code_array, instruction_t **list, uint32_t bytes_in_array)
 {
    int return_code = 0;
    uint8_t *code = *code_array;
    instruction_t *root = *list;
  
    //initialize root
    root = malloc (sizeof (instruction_t) );
    if (root == NULL) return 1;
    
    instruction_t *cur = NULL;
    cur = root;

    uint32_t pc;
    for (pc = 0; pc < bytes_in_array; pc++)
    {

        cur -> address = pc;
        cur -> inst_spec = code[pc];
        cur -> unary = is_unary(cur -> inst_spec);
        //Determin if unary, then get op. Operand is 0 if unary.
        if (cur -> unary)
        {
            cur -> op_spec = 0xFFFF;
        }
        else
        {
            cur -> op_spec = code[pc + 1] << 8;
            cur -> op_spec += code[pc + 2];
            pc += 2;
        }
        // mnemonic by reference
        return_code = get_mnemonic(cur -> inst_spec, &cur -> mnemonic);
        if (return_code)
        {
            printv("machine/disassemble.c/build_list:\tCould not get "
                   "mnemonic. Returning 1.\n");
            return return_code;
        }

        //addressing_mod by reference
        if (cur -> op_spec != 0xFFFF)
        {
            return_code = get_addressing_mode(cur -> inst_spec, &cur -> addressing_mode);
        }
        else
        {
            cur -> addressing_mode = "";
        }
        if (return_code)
        {
            printv("machine/disassemble.c/build_list:\tCould not get "
                   "addressing mode. Returning 1.\n");
            return return_code;
        }

        //create reference to next instruction
        cur -> next = malloc (sizeof (instruction_t) );
        if (cur -> next == NULL) return 1;
        cur = cur -> next;
    }
    *list = root;
    return 0;
 }

/* ************************************************************************* *
 * is_unary - determines whether the instruction specifier is unary or not   *
 *                                                                           *
 * Parameters                                                                *
 *   instruction_specifier - The instruction specifier to be tested          *
 *                                                                           *
 * Returns                                                                   *
 *   Status of the specifier. 1 for unary, 0 nonunary                        *
 * ************************************************************************* */
 int
 is_unary (uint8_t inst_spec)
 {
    int exit_status = 0;

    if (0x00 <= inst_spec && inst_spec <= 0x03)
        exit_status = 1;
    else if (0x18 <= inst_spec && inst_spec <= 0x23)
        exit_status = 1;
    else if (0x24 <= inst_spec && inst_spec <= 0x27)
        exit_status = 1;
    else if (0x58 <= inst_spec && inst_spec <= 0x5F)
        exit_status = 1;

    return exit_status;
 }


/* ************************************************************************* *
 * get_mnemonic - gets the mnemonic string value of the instruction          *
 *                specifier                                                  *
 *                                                                           *
 * Parameters                                                                *
 *   instruction_specifier -- the uint8_t containing the inst_spec           *
 *   mnemonic -- empty string. Pass by reference magic will change this      *
 *                                                                           *
 * Returns                                                                   *
 *   Program exit status. The standard is to return 0 for normal exit (no    *
 *   errors occurred). If something unusual happens, return some number      *
 *   other than 0, which can then indicate to the user what happened.        *
 * ************************************************************************* */
int get_mnemonic(uint8_t inst_spec, char **mnemonic)
{
    char *mne = *mnemonic;

    if (0x00 <= inst_spec && inst_spec <=0x03)
    {
        switch (inst_spec)
        {
            case 0x00:
                mne = "STOP";
                *mnemonic = mne;
                return 0;
            case 0x01:
                mne = "RETTR";
                *mnemonic = mne;
                return 0;
            case 0x02:
                mne = "MOVSPA";
                *mnemonic = mne;
                return 0;
            case 0x03:
                mne = "MOVFLGA";
                *mnemonic = mne;
                return 0;
            default:
                printv("machine/disassemble.c/get_mnemonic:\tReached default \
                        case in switch 0-3. Returning.\n");
                return 1;
        }
    }
    else if (0x04 <= inst_spec && inst_spec <= 0x17)
    {
        switch (inst_spec >> 1)
        {
            case 0x02:
                mne = "BR";
                *mnemonic = mne;
                return 0;
            case 0x03:
                mne = "BRLE";
                *mnemonic = mne;
                return 0;
            case 0x04:
                mne = "BRLT";
                *mnemonic = mne;
                return 0;
            case 0x05:
                mne = "BREQ";
                *mnemonic = mne;
                return 0;
            case 0x06:
                mne = "BRNE";
                *mnemonic = mne;
                return 0;
            case 0x07:
                mne = "BRGE";
                *mnemonic = mne;
                return 0;
            case 0x08:
                mne = "BRGT";
                *mnemonic = mne;
                return 0;
            case 0x09:
                mne = "BRV";
                *mnemonic = mne;
                return 0;
            case 0x0A:
                mne = "BRC";
                *mnemonic = mne;
                return 0;
            case 0x0B:
                mne = "CALL";
                *mnemonic = mne;
                return 0;
            default:
                printv("machine/disassemble.c/get_mnemonic:\tReached default "
                       "case in switch 0x04-0x17. Returning.\n");
                return 1;
        }
    }
    else if (0x18 <= inst_spec && inst_spec <= 0x23)
    {
        switch (inst_spec)
        {
            case 0x18:
                mne = "NOTA";
                *mnemonic = mne;
                return 0;
            case 0x19:
                mne = "NOTX";
                *mnemonic = mne;
                return 0;
            case 0x1A:
                mne = "NEGA";
                *mnemonic = mne;
                return 0;
            case 0x1B:
                mne = "NEGX";
                *mnemonic = mne;
                return 0;
            case 0x1C:
                mne = "ASLA";
                *mnemonic = mne;
                return 0;
            case 0x1D:
                mne = "ASLX";
                *mnemonic = mne;
                return 0;
            case 0x1E:
                mne = "ASRA";
                *mnemonic = mne;
                return 0;
            case 0x1F:
                mne = "ASRX";
                *mnemonic = mne;
                return 0;
            case 0x20:
                mne = "ROLA";
                *mnemonic = mne;
                return 0;
            case 0x21:
                mne = "ROLX";
                *mnemonic = mne;
                return 0;
            case 0x22:
                mne = "RORA";
                *mnemonic = mne;
                return 0;
            case 0x23:
                mne = "RORX";
                *mnemonic = mne;
                return 0;
            default:
                printv("machine/disassemble.c/get_mnemonic:\tReached default "
                       "case in switch 0x18-0x23. Returning.\n");
                return 1;
        }
    }
    else if (0x24 <= inst_spec && inst_spec <= 0x27)
    {
        switch (inst_spec)
        {
            case 0x24:
                mne = "NOP0";
                *mnemonic = mne;
                return 0;
            case 0x25:
                mne = "NOP1";
                *mnemonic = mne;
                return 0;
            case 0x26:
                mne = "NOP2";
                *mnemonic = mne;
                return 0;
            case 0x27:
                mne = "NOP3";
                *mnemonic = mne;
                return 0;
            default:
                printv("machine/disassemble.c/get_mnemonic:\tReached default "
                       "case in switch 0x24-0x27. Returning.\n");
                return 1;
        }
    }
    else if (0x28 <= inst_spec && inst_spec <= 0x2F)
    {
        mne = "NOP";
        *mnemonic = mne;
        return 0;
    }
    else if (0x30 <= inst_spec && inst_spec <= 0x57)
    {
        switch (inst_spec >> 3)
        {
            case 0x06:
                mne = "DECI";
                *mnemonic = mne;
                return 0;
            case 0x07:
                mne = "DECO";
                *mnemonic = mne;
                return 0;
            case 0x08:
                mne = "STRO";
                *mnemonic = mne;
                return 0;
            case 0x09:
                mne = "CHARI";
                *mnemonic = mne;
                return 0;
            case 0x0A:
                mne = "CHARO";
                *mnemonic = mne;
                return 0;
            default:
                printv("machine/disassemble.c/get_mnemonic:\tReached default "
                       "case in switch 0x30-0x57. Returning.\n");
                return 1;
        }
    }
    else if (0x58 <= inst_spec && inst_spec <= 0x5F)
    {
        switch (inst_spec)
        {
            case 0x58:
                mne = "RET0";
                *mnemonic = mne;
                return 0;
            case 0x59:
                mne = "RET1";
                *mnemonic = mne;
                return 0;
            case 0x5A:
                mne = "RET2";
                *mnemonic = mne;
                return 0;
            case 0x5B:
                mne = "RET3";
                *mnemonic = mne;
                return 0;
            case 0x5C:
                mne = "RET4";
                *mnemonic = mne;
                return 0;
            case 0x5D:
                mne = "RET5";
                *mnemonic = mne;
                return 0;
            case 0x5E:
                mne = "RET6";
                *mnemonic = mne;
                return 0;
            case 0x5F:
                mne = "RET7";
                *mnemonic = mne;
                return 0;
            default:
                printv("machine/disassemble.c/get_mnemonic:\tReached default "
                       "case in switch 0x58-0x5F. Returning.\n");
                return 1;
        }
    }
    else if (0x60 <= inst_spec && inst_spec <= 0x6F)
    {
        switch (inst_spec >> 3)
        {
            case 0x0C:
                mne = "ADDSP";
                *mnemonic = mne;
                return 0;
            case 0x0D:
                mne = "SUBSP";
                *mnemonic = mne;
                return 0;
            default:
                printv("machine/disassemble.c/get_mnemonic:\tReached default "
                       "case in switch 0x60-0x6F. Returning.\n");
                return 1;
        }
    }
    else if (0x70 <= inst_spec && inst_spec <= 0xBF)
    {
        switch (inst_spec & 0xF8)
        {
            case 0x70:
                mne = "ADDA";
                *mnemonic = mne;
                return 0;
            case 0x78:
                mne = "ADDX";
                *mnemonic = mne;
                return 0;
            case 0x80:
                mne = "SUBA";
                *mnemonic = mne;
                return 0;
            case 0x88:
                mne = "SUBX";
                *mnemonic = mne;
                return 0;
            case 0x90:
                mne = "ANDA";
                *mnemonic = mne;
                return 0;
            case 0x98:
                mne = "ANDX";
                *mnemonic = mne;
                return 0;
            case 0xA0:
                mne = "ORA";
                *mnemonic = mne;
                return 0;
            case 0xA8:
                mne = "ORX";
                *mnemonic = mne;
                return 0;
            case 0xB0:
                mne = "CPA";
                *mnemonic = mne;
                return 0;
            case 0xB8:
                mne = "CPX";
                *mnemonic = mne;
                return 0;
            default:
                printv("machine/disassemble.c/get_mnemonic:\tReached default "
                       "case in switch 0x70-0xBF. Returning.\n");
                return 1;
        }
    }
    else if (0xC0 <= inst_spec && inst_spec <= 0xFF)
    {
        switch (inst_spec & 0xF8)
        {
            case 0xC0:
                mne = "LDA";
                *mnemonic = mne;
                return 0;
            case 0xC8:
                mne = "LDX";
                *mnemonic = mne;
                return 0;
            case 0xD0:
                mne = "LDBYTEA";
                *mnemonic = mne;
                return 0;
            case 0xD8:
                mne = "LDBYTEX";
                *mnemonic = mne;
                return 0;
            case 0xE0:
                mne = "STA";
                *mnemonic = mne;
                return 0;
            case 0xE8:
                mne = "STX";
                *mnemonic = mne;
                return 0;
            case 0xF0:
                mne = "STBYTEA";
                *mnemonic = mne;
                return 0;
            case 0xF8:
                mne = "STBYTEX";
                *mnemonic = mne;
                return 0;
            default:
                printv("machine/disassemble.c/get_mnemonic:\tReached default "
                       "case in switch 0xC0-0xFF. Returning.\n");
                return 1;
        }
    }
    mne = "unused";
    //To satisfy the compiler, I'm throwing mne in here
    printv("machine/disassemble.c/get_mnemonic:\tReached the end of the "
           "function %s, which shouldn't happen. Returning 1.\n", mne);
    return 1;
}

/* ************************************************************************* *
 * get_addressing_mode - gets the addressing mode  string value of the       *
 *                       instruction                                         *
 *                                                                           *
 * Parameters                                                                *
 *   instruction_specifier -- the uint8_t containing the inst_spec           *
 *   addr_mode -- empty string. Pass by reference magic will change this     *
 *                                                                           *
 * Returns                                                                   *
 *   Program exit status. The standard is to return 0 for normal exit (no    *
 *   errors occurred). If something unusual happens, return some number      *
 *   other than 0, which can then indicate to the user what happened.        *
 * ************************************************************************* */
int
get_addressing_mode(uint8_t inst_spec, char **addr_mode)
{
    char *mode = *addr_mode;

    if (0x04 <= inst_spec && inst_spec <= 0x17)
    {
        switch (inst_spec & 0x01)
        {
            case 0x00:
                mode = "i";
                *addr_mode = mode;
                return 0;
            case 0x01:
                mode = "x";
                *addr_mode = mode;
                return 0;
            default:
                printv("machine/disassemble.c/get_addressing_mode():"
                       "\tSomething went wrong in 0x04 - 0x17. Returning 1.\n");
                return 1;
        }
    }
    else if (0x30 <= inst_spec && inst_spec <= 0x57)
    {
        switch (inst_spec & 0x07)
        {
            case 0x00:
                mode = "i";
                *addr_mode = mode;
                return 0;
            case 0x01:
                mode = "d";
                *addr_mode = mode;
                return 0;
            case 0x02:
                mode = "n";
                *addr_mode = mode;
                return 0;
            case 0x03:
                mode = "s";
                *addr_mode = mode;
                return 0;
            case 0x04:
                mode = "sf";
                *addr_mode = mode;
                return 0;
            case 0x05:
                mode = "x";
                *addr_mode = mode;
                return 0;
            case 0x06:
                mode = "sx";
                *addr_mode = mode;
                return 0;
            case 0x07:
                mode = "sxf";
                *addr_mode = mode;
                return 0;
            default:
                printv("machine/disassemble.c/get_addressing_mode():"
                       "\tSomething went wrong in 0x30 - 0x57. Returning 1.\n");
                return 1;
        }
    }
    else if (0x60 <= inst_spec && inst_spec <= 0x6F)
    {
        switch (inst_spec & 0x07)
        {
            case 0x00:
                mode = "i";
                *addr_mode = mode;
                return 0;
            case 0x01:
                mode = "d";
                *addr_mode = mode;
                return 0;
            case 0x02:
                mode = "n";
                *addr_mode = mode;
                return 0;
            case 0x03:
                mode = "s";
                *addr_mode = mode;
                return 0;
            case 0x04:
                mode = "sf";
                *addr_mode = mode;
                return 0;
            case 0x05:
                mode = "x";
                *addr_mode = mode;
                return 0;
            case 0x06:
                mode = "sx";
                *addr_mode = mode;
                return 0;
            case 0x07:
                mode = "sxf";
                *addr_mode = mode;
                return 0;
            default:
                printv("machine/disassemble.c/get_addressing_mode():"
                       "\tSomething went wrong in 0x60 - 0x6F. Returning 1.\n");
                return 1;
        }
    }
    else if (0x70 <= inst_spec && inst_spec <= 0xBF)
    {
        switch (inst_spec & 0x07)
        {
            case 0x00:
                mode = "i";
                *addr_mode = mode;
                return 0;
            case 0x01:
                mode = "d";
                *addr_mode = mode;
                return 0;
            case 0x02:
                mode = "n";
                *addr_mode = mode;
                return 0;
            case 0x03:
                mode = "s";
                *addr_mode = mode;
                return 0;
            case 0x04:
                mode = "sf";
                *addr_mode = mode;
                return 0;
            case 0x05:
                mode = "x";
                *addr_mode = mode;
                return 0;
            case 0x06:
                mode = "sx";
                *addr_mode = mode;
                return 0;
            case 0x07:
                mode = "sxf";
                *addr_mode = mode;
                return 0;
            default:
                printv("machine/disassemble.c/get_addressing_mode():"
                       "\tSomething went wrong in 0x70 - 0xBF. Returning 1.\n");
                return 1;
        }
    }
    else if (0xC0 <= inst_spec && inst_spec <= 0xFF)
    {
        switch (inst_spec & 0x07)
        {
            case 0x00:
                mode = "i";
                *addr_mode = mode;
                return 0;
            case 0x01:
                mode = "d";
                *addr_mode = mode;
                return 0;
            case 0x02:
                mode = "n";
                *addr_mode = mode;
                return 0;
            case 0x03:
                mode = "s";
                *addr_mode = mode;
                return 0;
            case 0x04:
                mode = "sf";
                *addr_mode = mode;
                return 0;
            case 0x05:
                mode = "x";
                *addr_mode = mode;
                return 0;
            case 0x06:
                mode = "sx";
                *addr_mode = mode;
                return 0;
            case 0x07:
                mode = "sxf";
                *addr_mode = mode;
                return 0;
            default:
                printv("machine/disassemble.c/get_addressing_mode():"
                       "\tSomething went wrong in 0xC0 - 0xFF. Returning 1.\n");
                return 1;
        }
    }

    mode = "unused";
    //To satisfy the compiler, I'm throwing mode in here
    printv("machine/disassemble.c/get_addressing_mode:\tReached the end of "
           "the function %s, which shouldn't happen. Returning 1.\n", mode);
    return 1;
}

/* ************************************************************************* *
 * free_list - frees the linked list of instructions                         *
 *                                                                           *
 * Parameters                                                                *
 *   head -- Double pointer. Ends at first node in list                      *
 *                                                                           *
 * Returns                                                                   *
 *   void                                                                    *
 * ************************************************************************* */
void
free_list (instruction_t ** list)
{
    instruction_t * head = * list;

    instruction_t * cur_node = head;
    if (cur_node != NULL)
    {
        while (cur_node != NULL)
        {
            instruction_t * temp = cur_node;
            cur_node = cur_node -> next;
            free (temp);
            temp = NULL;
        }
    }

    * list = head;
}
