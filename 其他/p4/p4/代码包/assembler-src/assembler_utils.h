/*****************************************************************
 * BUAA Fall 2022 Fundamentals of Computer Hardware
 * Project4 Assembler and Linker
 *****************************************************************
 * assembler_utils.h
 *****************************************************************/

#ifndef ASSEMBLER_UTILS_H
#define ASSEMBLER_UTILS_H

#include <stdint.h>
#include "../lib/tables.h"

extern const char *ASSEMBLER_IGNORE_CHARS;

extern const int MAX_ARGS;

extern const int ASSEMBLER_BUF_SIZE;

void raise_label_error(uint32_t input_line, const char *label);

/* Call this function if more than MAX_ARGS arguments are found while parsing
 * arguments.
 *
 * INPUT_LINE is which line of the input file that the error occurred in. Note
 * that the first line is line 1 and that empty lines are included in the count.
 *
 * EXTRA_ARG should contain the first extra argument encountered.
 */
void raise_extra_arg_error(uint32_t input_line, const char *extra_arg);

/* You should call this function if write_pass_one() or translate_inst()
   returns -1.

   INPUT_LINE is which line of the input file that the error occurred in. Note
   that the first line is line 1 and that empty lines are included in the count.
 */
void raise_inst_error(uint32_t input_line, const char *name, char **args, int num_args);

/*  A helpful helper function that parses instruction arguments. It raises an error
 *  if too many arguments have been passed into the instruction.
 */
int parse_args(uint32_t input_line, char **args, int *num_args);

/* Truncates the string at the first occurrence of the '#' character. */
void skip_comment(char *str);

#endif