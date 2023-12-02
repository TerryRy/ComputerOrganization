/*****************************************************************
 * BUAA Fall 2022 Fundamentals of Computer Hardware
 * Project4 Assembler and Linker
 *****************************************************************
 * my_assembler_utils.h
 * Assembler Functions Description
 *****************************************************************/
#ifndef MY_ASSEMBLER_UTILS_H
#define MY_ASSEMBLER_UTILS_H

#include "linker-src/linker_utils.h"

/*
 * This function reads .data symbol from INPUT and add them to the SYMTBL
 * Note that in order to distinguish in the symbol table whether a symbol
 * comes from the .data segment or the .text segment, we append a % to the
 * symbol name when adding the .data segment symbol. Since only underscores and
 * letters will appear in legal symbols, distinguishing them by adding % will
 * not cause a conflict between the new symbol and the symbol in the assembly file.
 *
 * Return value:
 * Return the number of bytes in the .data segment.
 */
int read_data_segment(FILE *input, SymbolTable *symtbl);

/* Reads STR and determines whether it is a label (ends in ':'), and if so,
 * whether it is a valid label, and then tries to add it to the symbol table.
 *
 * INPUT_LINE is which line of the input file we are currently processing. Note
 * that the first line is line 1 and that empty lines are included in this count.
 *
 * BYTE_OFFSET is the offset of the NEXT instruction (should it exist).
 *
 * Four scenarios can happen:
 *  1. STR is not a label (does not end in ':'). Returns 0.
 *  2. STR ends in ':', but is not a valid label. Returns -1.
 *  3a. STR ends in ':' and is a valid label. Addition to symbol table fails.
 *      Returns -1.
 *  3b. STR ends in ':' and is a valid label. Addition to symbol table succeeds.
 *      Returns 1.
 */
int add_if_label(uint32_t input_line, char *str, uint32_t byte_offset, SymbolTable *symtbl);

/*
 * Convert memory instructions(including lw, lb, sw, sb, lbu) to machine code.
 * Output the instruction to the **OUTPUT**.(Consider using write_inst_hex()).
 * 
 * Arguments:
 *  opcode:     op segment in MIPS machine code
 *  args:       args[0] is the $rt register, and args[2] is the $rs register.
 *             The other cases are illegal and need not be considered
 *  num_args:   length of args array
 *  addr:       Address offset of the current instruction in the file
 * 
 * Hint:
 *  Use translate_reg, translate_num and write_inst_hex.
 */
int write_mem(uint8_t opcode, FILE *output, char **args, size_t num_args);

#endif
