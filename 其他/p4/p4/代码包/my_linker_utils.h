/*****************************************************************
 * BUAA Fall 2022 Fundamentals of Computer Hardware
 * Project4 Assembler and Linker
 *****************************************************************
 * my_linker_utils.h
 * Linker Functions Description
 *****************************************************************/
#ifndef MY_LINKER_UTILS_H
#define MY_LINKER_UTILS_H

/*
 * Detect whether the given instruction needs relocation.
 *
 * Return value:
 * 1 if the instruction needs relocation, 0 otherwise.
 *
 * Arguments:
 * inst: 32-bit MIPS instruction.
 */
int inst_needs_relocation(SymbolTable *reltbl, uint32_t offset);

/*
 * Builds the symbol table and relocation data for a single file.
 * Read the .data, .text, .symbol, .relocation segments in that order.
 * The size of the .data and .text segments are read and saved in the
 * relocation table of the current file. For the .symbol and .relocation
 * segments, save the symbols in them in the corresponding locations.
 *
 * Return value:
 * 0 if no errors, -1 if error.
 *
 * Arguments:
 * input:            file pointer.
 * symtbl:           symbol table.
 * reldt:            pointer to a Relocdata struct.
 * base_text_offset: base text offset.
 * base_data_offset: base data offset.
 */
int
fill_data(FILE *input, SymbolTable *symtbl, RelocData *reldt, uint32_t base_text_offset, uint32_t base_data_offset);

#endif