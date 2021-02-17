#ifndef TREE_SITTER_MD_CHARS_H_
#define TREE_SITTER_MD_CHARS_H_

#include <stdbool.h>
#include <tree_sitter/parser.h>

#include "tree_sitter_md/scanner.h"

#define CHAR_EOF 0
#define CHAR_NEWLINE 10
#define CHAR_CARRIAGE_RETURN 13
#define CHAR_SPACE ' '
#define CHAR_FORM_FEED '\f'
#define CHAR_TAB '\t'
#define CHAR_VERTICAL_TAB '\v'
#define CHAR_EMDASH 8212
#define TAB_STOP 4

int get_indent_level(MDScanner* scanner);

bool is_newline(int32_t c);
bool is_space(int32_t c);
bool is_number(int32_t c);
bool is_abc(int32_t c);
bool is_alphanumeric(int32_t c);
bool is_escapable_char(int32_t c);

bool is_start_char(int32_t c);
bool is_end_char(int32_t c);

bool is_inline_markup_start_char(int32_t c);
bool is_inline_markup_end_char(int32_t c);

bool is_char_bullet(int32_t c);
bool is_numeric_bullet(int32_t c);

bool is_known_schema(char* string, unsigned string_len);
bool is_invalid_uri_char(int32_t c);

#endif /* ifndef TREE_SITTER_MD_CHARS_H_ */
