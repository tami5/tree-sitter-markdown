#ifndef TREE_SITTER_MD_PARSER_H_
#define TREE_SITTER_MD_PARSER_H_

#include "tree_sitter_md/scanner.h"
#include "tree_sitter_md/tokens.h"

#define IM_EMPHASIS 1u << 0u
#define IM_STRONG 1u << 1u
#define IM_STRIKE 1u << 2u
#define IM_SPAN 1u << 3u

bool parse_inner_list_element(MDScanner* scanner, int consumed_chars, enum TokenType token_type);
bool parse_inner_numeric_bullet(MDScanner* scanner, bool parenthesized);

bool parse_text(MDScanner* scanner);
bool parse_indent(MDScanner* scanner);
bool parse_char_bullet(MDScanner* scanner);
bool parse_numeric_bullet(MDScanner* scanner);

bool parse_inline_markup(MDScanner* scanner);
bool parse_explict_markup_start(MDScanner* scanner);
bool parse_inner_inline_markup(MDScanner* scanner, unsigned type);

#endif /* TREE_SITTER_MD_PARSER_H_ */
