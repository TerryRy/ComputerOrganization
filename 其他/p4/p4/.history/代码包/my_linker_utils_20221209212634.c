/*****************************************************************
 * BUAA Fall 2022 Fundamentals of Computer Hardware
 * Project4 Assembler and Linker
 *****************************************************************
 * my_linker_utils.c
 * Linker Submission
 *****************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "lib/tables.h"
#include "linker-src/linker_utils.h"

/*
 * Detect whether the given instruction needs relocation.
 *
 * Return value:
 *  1 if the instruction needs relocation, 0 otherwise.
 *
 * Arguments:
 *  reltbl: the relocation table.
 *  offset: the address of an instruction in the file.
 * 
 * Hint:
 *  Use get_symbol_for_addr().
 */
int inst_needs_relocation(SymbolTable *reltbl, uint32_t offset) {
    if(get_symbol_for_addr(reltbl, offset) != NULL) 
        return 1;
    return 0;
}

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
 * 
 * Hint:
 *  Use calc_text_size(), calc_data_size(), add_to_symbol_table();
 */
int fill_data(FILE *input, SymbolTable *symtbl, RelocData *reldt, uint32_t base_text_offset, uint32_t base_data_offset) {
    int ret = 0;
    char buf[LINKER_BUF_SIZE];

    while(fgets(buf, LINKER_BUF_SIZE, input)){
        char* token = strtok(buf, LINKER_IGNORE_CHARS);
        if(strcmp(token, ".data") == 0){
            reldt->data_size = calc_data_size(input);;
        }
        else if(strcmp(token, ".text") == 0){
            reldt->text_size = calc_text_size(input);
        }
        else if(strcmp(token, ".symbol") == 0){
            if(add_to_symbol_table(input, symtbl, base_text_offset, base_data_offset) == -1) ret = -1;
        }
        else if(strcmp(token, ".relocation") == 0){
            if(add_to_symbol_table(input,reldt->table,0,0) == -1) ret = -1;
        }
    }
    return ret;
}

int32_t relocate_inst(uint32_t inst, uint32_t offset, SymbolTable *symtbl, SymbolTable *reltbl) {
    char *buf; // 具体参数名
    int64_t loc; // 绝对地址
    int32_t rec = 0;
    buf = get_symbol_for_addr(reltbl, offset);
    if (buf == NULL) {
        return -1;
    }
    loc = get_addr_for_symbol(symtbl, buf);
    if (loc == -1) {
        return -1;
    }
    // 正常情况进行重定位
    
    // 根据buf是否含有‘@’以及后接“Hi”还是“Lo”判断取址方式
    int32_t hold;
    if (strstr(buf, "@") != NULL) {
        hold = inst & 0xffff0000; // 高16位保留，低16位置零
        if (strstr(buf, "Hi") != NULL) { // lui
            rec = hold | ((0xffff0000 & loc) >> 16);
        }
        else {
            rec = hold | (0x0000ffff & loc);
        }
    }
    else {
        hold = inst & 0xfc000000; // 高6位保留，低26位置零
        rec = hold | (((0xfffffff & loc) >> 2) | (inst & 0xf0000000));
    }



    // //取inst高6位（2进制下）判断指令
    // unsigned int check = inst >> 26;
    // switch (check) {
    //     case 2: { // j
    //         rec = 0x3ffffff & loc; // 仅保留loc低26位
    //         rec |= check << 26;
    //     }
    //       case 3: { // jar
    //         rec = 0x3ffffff & loc; // 仅保留loc低26位
    //         rec |= check << 26;
    //     }
    //     case 15: { // lui
    //         rec = 0xffff0000 & loc; // 高16位
    //         rec = rec >> 16;
    //         int32_t hold = inst & 0xffff0000; // 高16位保留，低16位置零
    //         rec |= hold;
    //     }
    //     case 13: { // ori
    //         rec = 0xffff & loc; // 低16位
    //         int32_t hold = inst & 0xffff0000; // 高16位保留，低16位置零
    //         rec |= hold;
    //     }
    // }
    return rec;
}

// int calc_text_size(FILE *input) {
//     int size = 0; // 文本大小
//     char buf[LINKER_BUF_SIZE];
//     if (input == NULL) {
//         return -1;
//     }
//     while (fgets(buf, LINKER_BUF_SIZE, input)) {
//         if(buf[0] == '\n' || buf[0] == '\r') {
//             break;
//         }
//         size += 4;

//     }
//     return size;
// }