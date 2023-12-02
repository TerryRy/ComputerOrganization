/*****************************************************************
 * BUAA Fall 2022 Fundamentals of Computer Hardware
 * Project4 Assembler and Linker
 *****************************************************************
 * my_assembler_utils.c
 * Assembler Submission
 *****************************************************************/
#include <string.h>
#include <stdlib.h>

#include "my_assembler_utils.h"
#include "assembler-src/assembler_utils.h"
#include "lib/translate_utils.h"

/*
 * This function reads .data symbol from INPUT and add them to the SYMTBL
 * Note that in order to distinguish in the symbol table whether a symbol
 * comes from the .data segment or the .text segment, we append a % to the
 * symbol name when adding the .data segment symbol. Since only underscores and
 * letters will appear in legal symbols, distinguishing them by adding % will
 * not cause a conflict between the new symbol and the symbol in the assembly file.
 *
 * Return value:
 *  Return the number of bytes in the .data segment.
 * 
 * Hint:
 *  Read pass_one() in assembler.c first.
 */
int read_data_segment(FILE *input, SymbolTable *symtbl) {
    // char str[ASSEMBLER_BUF_SIZE];
    // char *token;
    // int data_sz = 0;
    // fgets(str, ASSEMBLER_BUF_SIZE, input); // ".data"
    // while (fgets(str, ASSEMBLER_BUF_SIZE, input))
    // {
    //     if (str[0] == '\n' || str[0] == '\r')
    //         break;
    //     skip_comment(str); // 删除注释
    //     token = strtok(str, ASSEMBLER_IGNORE_CHARS); // "  Label:"
    //     if (token == NULL)
    //         continue;
    //     token[strlen(token) - 1] = '\0'; // "  Label"
        
    //     // 去除前导空格
    //     int i, j;
    //     for(i = 0; token[i] == ' '; i ++); /*循环结束后的i值为前导空格的个数*/
    //     if(i == 0) 
    //         return;
    //     for(j = i; token[j] != '/0'; j ++)
    //         token[j-i] = token[j];
    //     token[j-i]='/0';
        
    //     if (is_valid_label(token))
    //     {
    //         char sym_name[1086] = "%";
    //         strcat(sym_name, token); // "%Label"
    //         add_to_table(symtbl, sym_name, data_sz);
    //         token = strtok(NULL, ASSEMBLER_IGNORE_CHARS); // ".space"
    //         token = strtok(NULL, ASSEMBLER_IGNORE_CHARS); // "number_of_bytes"
    //         long int add_data_sz;
    //         translate_num(&add_data_sz, token, INT16_MIN, INT16_MAX);
    //         data_sz += add_data_sz;
    //     }
    // }
    // return data_sz;


    char buf[ASSEMBLER_BUF_SIZE];   // 存储每一行的读入数据
    uint32_t input_line = 0;
    int is_valid = 1;
    int byte_offset = 0;
    fgets(buf, ASSEMBLER_BUF_SIZE, input);
    if(strcmp(strtok(buf, ASSEMBLER_IGNORE_CHARS),".data") != 0){   // 如果一开始读入不是.data，直接返回invalid -1
        return -1;
    }
    while(fgets(buf, ASSEMBLER_BUF_SIZE, input)){   // 继续循环读入每一行
        skip_comment(buf);
        input_line++;
        if(buf[0] == '\n'|| buf[0] == '\r'){     // 读到空行退出循环
            break;
        }
        char name[2000] = {'%','\0'};    // 暂定最大的名字为1000行
        char *token = strtok(buf, ASSEMBLER_IGNORE_CHARS);
        if(token[strlen(token)-1] == ':'){
            token[strlen(token)-1] = '\0';
            if(!is_valid_label(token)){         // 如果Label名称违法则读取下一行,且设定返回invalid -1
                is_valid = 0;
                raise_label_error(input_line, token);
                continue;
            }
        }
        else{
            is_valid = 0;
            raise_label_error(input_line, token);
            continue;
        }
        strcat(name, token);

        token = strtok(NULL, ASSEMBLER_IGNORE_CHARS);
        if(strcmp(token,".space") != 0) {     // 如果读取非.space则字段违法，且设定返回invalid -1
            is_valid = 0;
            continue;
        }

        long num = 0;
        token = strtok(NULL, ASSEMBLER_IGNORE_CHARS);
        if(translate_num(&num, token, 0, 100000000) == -1){     // 如果读取到非法数字则设定返回invalid -1
            is_valid = 0;
            continue;
        }
        if(add_to_table(symtbl, name, byte_offset) == 0){
                byte_offset += num;
        }
        
    }
    return is_valid ? byte_offset : -1;


}

/* Reads STR and determines whether it is a label (ends in ':'), and if so,
 * whether it is a valid label, and then tries to add it to the symbol table,
 * remerber to replace ':' with '\0'.
 *
 * Four scenarios can happen:
 *  1. STR is not a label (does not end in ':'). Returns 0.
 *  2. STR ends in ':', but is not a valid label. Returns -1.
 *  3a. STR ends in ':' and is a valid label. Addition to symbol table fails.
 *      Returns -1.
 *  3b. STR ends in ':' and is a valid label. Addition to symbol table succeeds.
 *      Returns 1.
 * 
 * Hint:
 *  Use is_valid_label(), add_to_table() and raise_label_error().
 */
int add_if_label(uint32_t input_line, char *str, uint32_t addr, SymbolTable *symtbl) {
    size_t len = strlen(str);
    if(str[len - 1] == ':') {
        str[len - 1] = '\0';
        if(is_valid_label(str)) {
            if(add_to_table(symtbl, str, addr) == 0) {
                return 1;
            }
            else {
                return -1;
            }
        }
        else {
            raise_label_error(input_line, str);
            return -1;
        }
    }
    else {
        return 0;
    }
}

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
 *  Use translate_reg(), translate_num() and write_inst_hex().
 */
int write_mem(uint8_t opcode, FILE *output, char **args, size_t num_args) {
    if (num_args != 3) {
        return -1;
    }

    long imm;
    int rt = translate_reg(args[0]);
    int rs = translate_reg(args[2]);
    int err = translate_num(&imm, args[1], INT16_MIN, INT16_MAX);

    if (rs == -1 || rt == -1) {
        return -1;
    }

    if (err == -1) {
        return -1;
    }

    uint32_t  ins = 0;
    ins |= imm & 0x0000ffff;
    ins |= rt << 16;
    ins |= rs << 21;
    ins |= opcode << 26;

    write_inst_hex(output, ins);
    return 0;
}