/* ************************************************************************* *
 * interpret.c                                                               *
 * ------                                                                    *
 *  Author:   Conner Turnbull                                                *
 *  Purpose:  A PEP/8 interpreter.                                           *
 * ************************************************************************* */

/* ************************************************************************* *
 * Library includes here.  For documentation of standard C library           *
 * functions, see the list at:                                               *
 *   http://pubs.opengroup.org/onlinepubs/009695399/functions/contents.html  *
 * ************************************************************************* */
#include "interpret.h"
#include "../output/print.h"

/* ************************************************************************* *
 * Local function declarations                                               *
 * ************************************************************************* */
 inst_t decode (uint8_t * memory, uint16_t address);
 void execute (cpu_t **, uint8_t **, inst_t);
 int check_unary (uint8_t);
 int get_addr_mode (uint8_t, char **);
 uint8_t get_register (uint8_t);

/* ************************************************************************* *
 * Global variable declarations                                              *
 * ************************************************************************* */
 cpu_t *cpu;

/* ************************************************************************* *
 * interpret - Cycles through the von Neumann cycle until the stop           *
 *             is encountered. Fetch -> decode -> increment -> execute.      *
 *                                                                           *
 * Parameters                                                                *
 *   memory -- contains binary instructions and data.                        *
 *   size   -- size of memory being used                                     *
 *                                                                           *
 * Returns                                                                   *
 *   Program exit status. The standard is to return 0 for normal exit (no    *
 *   errors occurred). If something unusual happens, return some number      *
 *   other than 0, which can then indicate to the user what happened.        *
 * ************************************************************************* */

int
interpret (uint8_t ** memory, uint32_t size)
{
    uint8_t * mem = * memory;

    cpu = calloc (sizeof (cpu_t), 1); //I want everything to start at 0
    if (cpu == NULL) return 1;


    start();
    do
    {
        inst_t instruction;
        //Fetch the instruction specifier at address in PC
        cpu -> inst_spec = mem[cpu -> PC];

        //Decode the instruction specifier
        instruction = decode (mem, cpu -> PC);
        if (instruction.valid == 0)
        {
            printv("Encountered invalid instruction. Returning 1.\n");
            return 1;
        }

        if (instruction.is_unary == 0)
        {
            //Fetch the operand specifier at address in PC
            cpu -> op_spec = instruction.op_spec;
            cpu -> PC += 3;
        }
        else
        {
            cpu -> op_spec = 0x0000;
            cpu -> PC++;
        }
        printc(cpu);
        execute(&cpu, &mem, instruction);
    } while (cpu -> STOP == 0);
    
    //Free allocated memory
    free (cpu);
    cpu = NULL;

    * memory = mem;
    return 0;
}


/* ************************************************************************* *
 * decode - builds the instruction                                           *
 *                                                                           *
 * Parameters                                                                *
 *   memory -- contains binary instructions and data.                        *
 *   size   -- size of memory being used                                     *
 *                                                                           *
 * Returns                                                                   *
 *   Program exit status. The standard is to return 0 for normal exit (no    *
 *   errors occurred). If something unusual happens, return some number      *
 *   other than 0, which can then indicate to the user what happened.        *
 * ************************************************************************* */
inst_t decode (uint8_t * memory, uint16_t address)
{
    inst_t instruction;
    int return_code;
    
    instruction.address = address;
    instruction.inst_spec = memory[instruction.address];

    instruction.is_unary = check_unary(instruction.inst_spec);
    if (instruction.is_unary)
        instruction.op_spec = 0xFFFF;
    else
        instruction.op_spec = (memory[address + 1] << 8);
        instruction.op_spec += memory[address + 2];

    return_code = get_addr_mode (instruction.inst_spec, &instruction.addr_mode);
    if (return_code == -1)
        instruction.valid = 0;
    else
        instruction.valid = 1;

    instruction.reg = get_register(instruction.inst_spec);
    
    return instruction;
}


/* ************************************************************************* *
 * execute - execute the instruction                                         *
 *                                                                           *
 * Parameters                                                                *
 *   memory -- contains binary instructions and data.                        *
 *   inst   -- the instruction to be executed                                *
 *                                                                           *
 * Returns                                                                   *
 *   Program exit status. The standard is to return 0 for normal exit (no    *
 *   errors occurred). If something unusual happens, return some number      *
 *   other than 0, which can then indicate to the user what happened.        *
 * ************************************************************************* */

 void
 execute (cpu_t ** pep8, uint8_t ** memory, inst_t inst)
 {
    cpu_t * cpu = * pep8;
    uint8_t * mem = * memory;

    // STOP
    if (cpu -> inst_spec == 0x00)
    {
        cpu -> STOP = 1;
        * pep8 = cpu;
        return;
    }
    //BRANCHES
    else if (0x04 <= cpu -> inst_spec && cpu -> inst_spec <= 0x11)
    {
        switch (inst.inst_spec)
        {
            case 0x04: //BR op_spec,i
                cpu -> PC = cpu -> op_spec;
                * pep8 = cpu;
                return;

            case 0x05: //BR op_spec,x
                printv("Indexed addressing mode not currently supported. "
                       "Exiting\n");
                cpu -> STOP = 1;
                return;

            case 0x06: //BRLE op_spec,i
                if ((cpu -> NZVC & 0x08) == 0x08 || (cpu -> NZVC & 0x04) == 0x04)
                {
                    cpu -> PC = cpu -> op_spec;
                    * pep8 = cpu;
                }
                return;

            case 0x07: //BRLE op_spec,x
                printv("Indexed addressing mode not currently supported. "
                       "Exiting\n");
                cpu -> STOP = 1;
                return;

            case 0x08: //BRLT op_spec,i
                if ((cpu -> NZVC & 0x08) == 0x08)
                {
                    cpu -> PC = cpu -> op_spec;
                    * pep8 = cpu;
                }
                return;

            case 0x09: //BRLT op_spec,x
                printv("Indexed addressing mode not currently supported. "
                       "Exiting\n");
                cpu -> STOP = 1;
                return;
                
            case 0x0A: //BREQ op_spec,i
                if ((cpu -> NZVC & 0x04) == 0x04)
                {
                    cpu -> PC = cpu -> op_spec;
                    * pep8 = cpu;
                }
                return;

            case 0x0B: //BREQ op_spec,x
                printv("Indexed addressing mode not currently supported. "
                       "Exiting\n");
                cpu -> STOP = 1;
                return;

            case 0x0C: //BRNE op_spec,i
                if ((cpu -> NZVC & 0x04) == 0x00)
                {
                    cpu -> PC = cpu -> op_spec;
                    * pep8 = cpu;
                }
                return;

            case 0x0D: //BRNE, op_spec,x
                printv("Indexed addressing mode not currently supported. "
                       "Exiting\n");
                cpu -> STOP = 1;
                return;

            case 0x0E: //BRGE, op_spec,i
                if ((cpu -> NZVC & 0x04) == 0x00)
                {
                    cpu -> PC = cpu -> op_spec;
                    * pep8 = cpu;
                }
                return;

            case 0x0F: //BRGE, op_spec,x
                printv("Indexed addressing mode not currently supported. "
                       "Exiting\n");
                cpu -> STOP = 1;
                return;

            case 0x10: //BRGT, op_spec,i
                if ((cpu -> NZVC & 0x08) == 0x08 || (cpu -> NZVC & 0x04) == 0x04)
                {
                    cpu -> PC = cpu -> op_spec;
                    * pep8 = cpu;
                }
                return;

            case 0x11: //BRGT, op_spec,x
                printv("Indexed addressing mode not currently supported. "
                       "Exiting\n");
                cpu -> STOP = 1;
                return;

            default:
                printv("Reached default branch case. Exiting\n");
                cpu -> STOP = 1;
                return;
        }
    }
    //The Invert and Negate Instructions
    else if (0x18 <= cpu -> inst_spec && cpu -> inst_spec <= 0x1B)
    {
        switch (cpu -> inst_spec)
        {
            case 0x18: //NOTA
                cpu -> A = ~(cpu -> A);
                * pep8 = cpu;
                //check if negative
                if ((cpu -> A & 0x8000) == 0x8000)
                    cpu -> NZVC |= 0x08;
                else
                    cpu -> NZVC &= 0x07;
                    //check if zero
                if (cpu -> A == 0x0000)
                    cpu -> NZVC |= 0x04;
                else
                    cpu -> NZVC &= 0x0B;
                return;
            case 0x19: //NOTX
                cpu -> X = ~(cpu -> X);
                * pep8 = cpu;
                //check if negative
                if ((cpu -> X & 0x8000) == 0x8000)
                    cpu -> NZVC |= 0x08;
                else
                    cpu -> NZVC &= 0x07;
                    //check if zero
                if (cpu -> X == 0x0000)
                    cpu -> NZVC |= 0x04;
                else
                    cpu -> NZVC &= 0x0B;
                return;
            case 0x1A: //NEGA
                if ((cpu -> NZVC & 0x08) == 0x08)
                {
                    cpu -> A -= 1;
                    cpu -> A = ~(cpu -> A);
                    cpu -> NZVC = cpu -> NZVC & 0x07;
                }
                else
                {
                    cpu -> A = ~(cpu -> A);
                    cpu -> A += 1;
                    cpu -> NZVC = cpu -> NZVC | 0x08;
                }
                //check if zero
                if (cpu -> A == 0x0000)
                    cpu -> NZVC |= 0x04;
                else
                    cpu -> NZVC &= 0x0B;
                * pep8 = cpu;
                return;
            case 0x1B: //NEGX
                if ((cpu -> NZVC & 0x08) == 0x08)
                {
                    cpu -> X -= 1;
                    cpu -> X = ~(cpu -> X);
                    cpu -> NZVC = cpu -> NZVC & 0x07;
                }
                else
                {
                    cpu -> X = ~(cpu -> X);
                    cpu -> X += 1;
                    cpu -> NZVC = cpu -> NZVC | 0x08;
                }
                //check if zero
                if (cpu -> X == 0x0000)
                    cpu -> NZVC |= 0x04;
                else
                    cpu -> NZVC &= 0x0B;
                * pep8 = cpu;
                return;
        }
    }
    //DECO
    else if (0x38 <= cpu -> inst_spec && cpu -> inst_spec <= 0x3F)
    {
        switch (cpu -> inst_spec & 0x07)
        {
            case 0x00: //DECO op_spec, i
                DECO(cpu -> op_spec);
                return;
            case 0x01: //DECO op_spec, d
                DECO((uint16_t)(mem[cpu -> op_spec] << 8) + mem[cpu -> op_spec + 1]);
                return;
            default: //DECO op_spec, everything else
                printv("DECO addressing mode not implemented. Exiting\n");
        }
    }
    //CHARO
    else if (0x50 <= cpu -> inst_spec && cpu -> inst_spec <= 0x57)
    {
        switch (cpu -> inst_spec & 0x07)
        {
            case 0x00: //CHARO op_spec, i

                CHARO(cpu -> op_spec);
                return;
            case 0x01: //CHARO op_spec, d
                CHARO(mem[cpu -> op_spec + 1]);
                return;
            default: //CHARO op_spec, everything else
                printv("CHARO addressing mode not implemented. Exiting\n");
        }
    }
    //arithmetic and logic operators
    else if (0x70 <= cpu -> inst_spec && cpu -> inst_spec <= 0xBF)
    {
        switch (cpu -> inst_spec & 0x08)
        {
            case 0x00: //Accumulator
                switch (cpu -> inst_spec & 0xF7)
                {
                    case 0x70: //ADDA op_spec,i
                        cpu -> A += cpu -> op_spec;
                        //check if negative
                        if ((cpu -> A & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> A == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0x71: //ADDA op_spec,d
                        cpu -> A += (((uint16_t)mem[cpu -> op_spec] << 8) + mem[cpu -> op_spec + 1]);
                        //check if negative
                        if ((cpu -> A & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> A == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0x80: //SUBA op_spec,i
                        cpu -> A -= cpu -> op_spec;
                        //check if negative
                        if ((cpu -> A & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> A == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0x81: //SUBA op_spec,d
                        cpu -> A -= (((uint16_t)mem[cpu -> op_spec] << 8) + mem[cpu -> op_spec + 1]);
                        //check if negative
                        if ((cpu -> A & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> A == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0x90: //ANDA op_spec,i
                        cpu -> A &= cpu -> op_spec;
                        //check if negative
                        if ((cpu -> A & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> A == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0x91: //ANDA op_spec,d
                        cpu -> A &= (((uint16_t)mem[cpu -> op_spec] << 8) + mem[cpu -> op_spec + 1]);
                        if ((cpu -> A & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> A == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0xA0: //ORA op_spec,i
                        cpu -> A |= cpu -> op_spec;
                        if ((cpu -> A & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> A == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0xA1: //ORA op_spec,d
                        cpu -> A |= (((uint16_t)mem[cpu -> op_spec] << 8) + mem[cpu -> op_spec + 1]);
                        if ((cpu -> A & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> T == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0xB0: //CPA op_spec,i
                        cpu -> T = cpu -> A - cpu -> op_spec;
                        if ((cpu -> T & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> T == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0xB1: //CPA op_spec,d
                        cpu -> T = cpu -> A - (((uint16_t)mem[cpu -> op_spec] << 8) + mem[cpu -> op_spec + 1]);
                        if ((cpu -> T & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> T == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    default:
                        printv("Addressing mode not implemented. Exiting\n");
                        cpu -> STOP = 1;
                        return;
                }
            case 0x08: //Index
                switch (cpu -> inst_spec & 0xF7)
                {
                    case 0x70: //ADDX op_spec,i
                        cpu -> X += cpu -> op_spec;
                        if ((cpu -> X & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> X == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0x71: //ADDX op_spec,d
                        cpu -> X += (((uint16_t)mem[cpu -> op_spec] << 8) + mem[cpu -> op_spec + 1]);
                        if ((cpu -> X & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> X == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0x80: //SUBX op_spec,i
                        cpu -> X -= cpu -> op_spec;
                        if ((cpu -> X & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> X == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0x81: //SUBX op_spec,d
                        cpu -> X -= (((uint16_t)mem[cpu -> op_spec] << 8) + mem[cpu -> op_spec + 1]);
                        if ((cpu -> X & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> X == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0x90: //ANDX op_spec,i
                        cpu -> X &= cpu -> op_spec;
                        if ((cpu -> X & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> X == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0x91: //ANDX op_spec,d
                        cpu -> X &= (((uint16_t)mem[cpu -> op_spec] << 8) + mem[cpu -> op_spec + 1]);
                        if ((cpu -> X & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> X == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0xA0: //ORX op_spec,i
                        cpu -> X |= cpu -> op_spec;
                        if ((cpu -> X & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> X == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0xA1: //ORX op_spec,d
                        cpu -> X |= (((uint16_t)mem[cpu -> op_spec] << 8) + mem[cpu -> op_spec + 1]);
                        if ((cpu -> X & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> X == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0xB0: //CPX op_spec,i
                        cpu -> T = cpu -> X - cpu -> op_spec;
                        if ((cpu -> T & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> T == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0xB1: //CPX op_spec,d
                        cpu -> T = cpu -> X - (((uint16_t)mem[cpu -> op_spec] << 8) + mem[cpu -> op_spec + 1]);
                        //check if negative
                        if ((cpu -> T & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> T == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    default:
                        printv("Addressing mode not implemented. Exiting\n");
                        cpu -> STOP = 1;
                        return;
                }
            default:
                printv("Invalid register. Exiting\n");
                cpu -> STOP = 1;
                return;
        }
    }
    //Memory
    else if (0xC0 <= cpu -> inst_spec && cpu -> inst_spec <= 0xFF)
    {
        switch (cpu -> inst_spec & 0x08)
        {
            case 0x00: //Accumulator
                switch (cpu -> inst_spec & 0xF7)
                {
                    case 0xC0: //LDA op_spec,i
                        cpu -> A = cpu -> op_spec;
                        //check if negative
                        if ((cpu -> A & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> A == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0xC1: //LDA op_spec,d
                        cpu -> A = ((uint16_t)mem[cpu -> op_spec] << 8) + mem[cpu -> op_spec + 1];
                        //check if negative
                        if ((cpu -> A & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> A == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0xD0: //LDBYTEA op_spec,i
                        cpu -> A = cpu -> op_spec & 0x00FF;
                        //check if negative
                        if ((cpu -> A & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> A == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0xD1: //LDBYTEA op_spec,d
                        cpu -> A = mem[cpu -> op_spec + 1];
                        //check if negative
                        if ((cpu -> A & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> A == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0xE1: //STA op_spec,d
                        mem[cpu -> op_spec] = (cpu -> A & 0xFF00) >> 8;
                        mem[cpu -> op_spec + 1] = cpu -> A;
                        memory_change (cpu -> op_spec, cpu -> A);
                        //check if negative
                        if ((cpu -> A & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> A == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        * memory = mem;
                        return;
                    case 0xF1: //STBYTEA op_spec,d
                        mem[cpu -> op_spec + 1] = cpu -> A;
                        memory_change (cpu -> op_spec, cpu -> A & 0x00FF);
                        //check if negative
                        if ((cpu -> A & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> A == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        * memory = mem;
                        return;
                    default:
                        printv("Addressing mode not implemented. Exiting\n");
                        cpu -> STOP = 1;
                        return;
                }
            case 0x08: //Index
                switch (cpu -> inst_spec & 0xF7)
                {
                    case 0xC0: //LDX op_spec,i
                        cpu -> X = cpu -> op_spec;
                        //check if negative
                        if ((cpu -> X & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> X == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0xC1: //LDX op_spec,d
                        cpu -> X = ((uint16_t)mem[cpu -> op_spec] << 8) + mem[cpu -> op_spec + 1];
                        //check if negative
                        if ((cpu -> X & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> X == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0xD0: //LDBYTEX op_spec,i
                        cpu -> X = cpu -> op_spec & 0x00FF;
                        //check if negative
                        if ((cpu -> X & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> X == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0xD1: //LDBYTEX op_spec,d
                        cpu -> X = mem[cpu -> op_spec + 1];
                        //check if negative
                        if ((cpu -> X & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> X == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        return;
                    case 0xE1: //STX op_spec,d
                        mem[cpu -> op_spec] = (cpu -> X & 0xFF00) >> 8;
                        mem[cpu -> op_spec + 1] = cpu -> X;
                        memory_change (cpu -> op_spec, cpu -> X);
                        //check if negative
                        if ((cpu -> X & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> X == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        * memory = mem;
                        return;
                    case 0xF1: //STBYTEX op_spec,d
                        mem[cpu -> op_spec + 1] = cpu -> X;
                        memory_change (cpu -> op_spec, cpu -> X & 0x0F);
                        //check if negative
                        if ((cpu -> X & 0x8000) == 0x8000)
                            cpu -> NZVC |= 0x08;
                        else
                            cpu -> NZVC &= 0x07;
                        //check if zero
                        if (cpu -> X == 0x0000)
                            cpu -> NZVC |= 0x04;
                        else
                            cpu -> NZVC &= 0x0B;
                        * pep8 = cpu;
                        * memory = mem;
                        return;
                    default:
                        printv("Addressing mode not implemented. Exiting\n");
                        cpu -> STOP = 1;
                        return;
                }
            default:
                printv("Invalid register. Exiting\n");
                cpu -> STOP = 1;
                return;
        }
    } 
    * pep8 = cpu;
    * memory = mem;
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
 check_unary (uint8_t inst_spec)
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
 * get_addr_mode - Builds the addressing mode. If unary, returns 1           *
 *                                                                           *
 * Parameters                                                                *
 *   inst_spec -- the instruction specifier                                  *
 *   addressing_mode - pointer to string of addressing mode. Will be built   *
 *                                                                           *
 * Returns                                                                   *
 *   Status of the specifier. 1 for unary, 0 nonunary, -1 for invalid inst   *
 * ************************************************************************* */
 int
 get_addr_mode (uint8_t inst_spec, char ** addressing_mode)
 {
    char * addr_mode = * addressing_mode;

    if (0x04 <= inst_spec && inst_spec <= 0x11)
    {
        switch (inst_spec & 0x01)
        {
            case 0x00:
                addr_mode = "i";
                * addressing_mode = addr_mode;
                return 0;
            case 0x01:
                addr_mode = "x";
                * addressing_mode = addr_mode;
                return 0;
            default:
                addr_mode = "";
                * addressing_mode = addr_mode;
                return -1;
        }
    }
    else if (0x38 <= inst_spec && inst_spec <= 0x3F)
    {
        switch (inst_spec & 0x07)
        {
            case 0x00:
                addr_mode = "i";
                * addressing_mode = addr_mode;
                return 0;
            case 0x01:
                addr_mode = "d";
                * addressing_mode = addr_mode;
                return 0;
            case 0x02:
                addr_mode = "n";
                * addressing_mode = addr_mode;
                return 0;
            case 0x03:
                addr_mode = "s";
                * addressing_mode = addr_mode;
                return 0;
            case 0x04:
                addr_mode = "sf";
                * addressing_mode = addr_mode;
                return 0;
            case 0x05:
                addr_mode = "x";
                * addressing_mode = addr_mode;
                return 0;
            case 0x06:
                addr_mode = "sx";
                * addressing_mode = addr_mode;
                return 0;
            case 0x07:
                addr_mode = "sxf";
                * addressing_mode = addr_mode;
                return 0;
            default:
                addr_mode = "";
                * addressing_mode = addr_mode;
                return -1;
        }
    }
    else if (0x50 <= inst_spec && inst_spec <= 0x57)
    {
        switch (inst_spec & 0x07)
        {
            case 0x00:
                addr_mode = "i";
                * addressing_mode = addr_mode;
                return 0;
            case 0x01:
                addr_mode = "d";
                * addressing_mode = addr_mode;
                return 0;
            case 0x02:
                addr_mode = "n";
                * addressing_mode = addr_mode;
                return 0;
            case 0x03:
                addr_mode = "s";
                * addressing_mode = addr_mode;
                return 0;
            case 0x04:
                addr_mode = "sf";
                * addressing_mode = addr_mode;
                return 0;
            case 0x05:
                addr_mode = "x";
                * addressing_mode = addr_mode;
                return 0;
            case 0x06:
                addr_mode = "sx";
                * addressing_mode = addr_mode;
                return 0;
            case 0x07:
                addr_mode = "sxf";
                * addressing_mode = addr_mode;
                return 0;
            default:
                addr_mode = "";
                * addressing_mode = addr_mode;
                return -1;
        }
    }
    else if (0x70 <= inst_spec && inst_spec <= 0xDF)
    {
        switch (inst_spec & 0x07)
        {
            case 0x00:
                addr_mode = "i";
                * addressing_mode = addr_mode;
                return 0;
            case 0x01:
                addr_mode = "d";
                * addressing_mode = addr_mode;
                return 0;
            case 0x02:
                addr_mode = "n";
                * addressing_mode = addr_mode;
                return 0;
            case 0x03:
                addr_mode = "s";
                * addressing_mode = addr_mode;
                return 0;
            case 0x04:
                addr_mode = "sf";
                * addressing_mode = addr_mode;
                return 0;
            case 0x05:
                addr_mode = "x";
                * addressing_mode = addr_mode;
                return 0;
            case 0x06:
                addr_mode = "sx";
                * addressing_mode = addr_mode;
                return 0;
            case 0x07:
                addr_mode = "sxf";
                * addressing_mode = addr_mode;
                return 0;
            default:
                addr_mode = "";
                * addressing_mode = addr_mode;
                return -1;
        }
    }
    else if (0xE0 <= inst_spec && inst_spec <= 0xFF)
    {
        switch (inst_spec & 0x07)
        {
            case 0x01:
                addr_mode = "d";
                * addressing_mode = addr_mode;
                return 0;
            case 0x02:
                addr_mode = "n";
                * addressing_mode = addr_mode;
                return 0;
            case 0x03:
                addr_mode = "s";
                * addressing_mode = addr_mode;
                return 0;
            case 0x04:
                addr_mode = "sf";
                * addressing_mode = addr_mode;
                return 0;
            case 0x05:
                addr_mode = "x";
                * addressing_mode = addr_mode;
                return 0;
            case 0x06:
                addr_mode = "sx";
                * addressing_mode = addr_mode;
                return 0;
            case 0x07:
                addr_mode = "sxf";
                * addressing_mode = addr_mode;
                return 0;
            default:
                addr_mode = "";
                * addressing_mode = addr_mode;
                return -1;
        }
    }

    addr_mode = "";
    * addressing_mode = addr_mode;
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

 uint8_t
 get_register (uint8_t inst_spec)
 {
    uint8_t reg;

    if (0x18 <= inst_spec && inst_spec <= 0x19)
    {
        switch (inst_spec & 0x01)
        {
            case 0x00:
                reg = 0x00;
                return reg;
            case 0x01:
                reg = 0x01;
                return reg;
            default:
                reg = 0xFF;
                return reg;
        }
    }
    else if (0x70 <= inst_spec && inst_spec <= 0xFF)
    {
        switch (inst_spec & 0x08)
        {
            case 0x00:
                reg = 0x00;
                return reg;
            case 0x08:
                reg = 0x01;
                return reg;
            default:
                reg = 0xFF;
                return reg;
        }
    }

    reg = 0xFF;
    return reg;
 }
