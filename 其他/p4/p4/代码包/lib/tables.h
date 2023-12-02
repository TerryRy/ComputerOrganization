/*****************************************************************
 * BUAA Fall 2022 Fundamentals of Computer Hardware
 * Project4 Assembler and Linker
 *****************************************************************
 * tables.h
 *****************************************************************/

#ifndef TABLES_H
#define TABLES_H

#include <stdint.h>
#include <stdio.h>

extern const int SYMTBL_NON_UNIQUE;      // allows duplicate names in table
extern const int SYMTBL_UNIQUE_NAME;     // duplicate names not allowed

/* Defined SymbolTable. Use this to implement the following
   functions. PLEASE DO NO CHANGE THIS.
 */
typedef struct {
    char *name;
    uint32_t addr;
} Symbol;

typedef struct {
    Symbol *tbl;
    uint32_t len;
    uint32_t cap;
    int mode;
} SymbolTable;

/*******************************
 * Helper Functions
 *******************************/

/* raise an error */
void allocation_failed();

/* raise an error */
void addr_alignment_incorrect();

/* raise an error */
void name_already_exists(const char *name);

/* Output symbols and offsets to the specified file */
void write_symbol(FILE *output, uint32_t addr, const char *name);

/*******************************
 * Symbol Table Functions
 *******************************/

/* Creates a new SymbolTable containg 0 elements and returns a pointer to that
 * table. Multiple SymbolTables may exist at the same time.
 * If memory allocation fails, you should call allocation_failed().
 * Mode will be either SYMTBL_NON_UNIQUE or SYMTBL_UNIQUE_NAME. You will need
 * to store this value for use during add_to_table().
 */
SymbolTable *create_table(int mode);

void free_table(SymbolTable *table);

/* Adds a new symbol and its address to the SymbolTable pointed to by TABLE.
 * ADDR is given as the byte offset from the first instruction. The SymbolTable
 * must be able to resize itself as more elements are added.
 *
 * Note that NAME may point to a temporary array, so it is not safe to simply
 * store the NAME pointer. You must store a copy of the given string.
 *
 * If ADDR is not word-aligned, you should call addr_alignment_incorrect() and
 * return -1. If the table's mode is SYMTBL_UNIQUE_NAME and NAME already exists
 * in the table, you should call name_already_exists() and return -1. If memory
 * allocation fails, you should call allocation_failed().
 *
 * Otherwise, you should store the symbol name and address and return 0.
 */
int add_to_table(SymbolTable *table, const char *name, uint32_t addr);

/* Returns the address (byte offset) of the given symbol. If a symbol with name
 * NAME is not present in TABLE, return -1.
 */
int64_t get_addr_for_symbol(SymbolTable *table, const char *name);

/* Returns the address symbol name of the given address (byte offset). If a symbol
 * with address ADDR is not present in TABLE, return -1.
 */
const char *get_symbol_for_addr(SymbolTable *table, const int32_t addr);

/* Writes the SymbolTable TABLE to OUTPUT. You should use write_symbol() to
 * perform the write. Do not print any additional whitespace or characters.
 */
void write_table(SymbolTable *table, FILE *output);

#endif