#include "tree_sitter_md/parser.h"
#include "tree_sitter/parser.h"
#include "tree_sitter_md/chars.h"
#include "tree_sitter_md/scanner.h"
#include "tree_sitter_md/tokens.h"

bool parse_inner_list_element(MDScanner* scanner, int consumed_chars, enum TokenType token_type)
{
  const bool* valid_symbols = scanner->valid_symbols;
  TSLexer* lexer = scanner->lexer;

  if (!valid_symbols[token_type]) {
    return false;
  }

  if (is_space(scanner->lookahead)) { // token<space>
    lexer->mark_end(lexer);
    lexer->result_symbol = token_type;

    // Set indent level to the first non-whitespace char
    int indent = scanner->back(scanner) + consumed_chars + get_indent_level(scanner);

    scanner->push(scanner, indent);
    return true;
  }

  return false;
}

bool parse_inner_numeric_bullet(MDScanner* scanner, bool parenthesized) {
  const bool* valid_symbols = scanner->valid_symbols;
  TSLexer* lexer = scanner->lexer;

  if (!is_numeric_bullet(scanner->lookahead) || !valid_symbols[T_NUMERIC_BULLET]) {
    
    


    
  }
}

bool parse_text(MDScanner* scanner)
{
  const bool* valid_symbols = scanner->valid_symbols;
  TSLexer* lexer = scanner->lexer;
  
  // if T_TEXT is not a symbol then return false
  if (!valid_symbols[T_TEXT]) {
    return false;
  }
  

  // if the char is one of the start_chars:  
  // '-', ':', '/', '\'', '"', '<', '(', '[', '{',
  // then ...?
  if (is_start_char(scanner->lookahead)) {
    scanner->advance(scanner);
    lexer->mark_end(lexer);
    lexer->result_symbol = T_TEXT;
    return true;
  }
  
  // Text tokens stop at a whitespace or start char
  while (!is_space(scanner->lookahead) && !is_start_char(scanner->lookahead)) {
   scanner->advance(scanner); 
  }
  
  lexer->mark_end(lexer);
  lexer->result_symbol = T_TEXT;
  return true;
}

bool parse_indent(MDScanner* scanner)
{
  const bool* valid_symbols = scanner->valid_symbols;
  TSLexer* lexer = scanner->lexer;

  int indent = 0;
  int newlines = 0;

  while (true) {
    /* switch(scanner->lookahead) { */
    /*   case CHAR_SPACE: */ 
    /*   case CHAR_VERTICAL_TAB: */
    /*   case CHAR_FORM_FEED: */
    /*     indent +=1; */
    /*   case CHAR_TAB: */
    /*     indent += TAB_STOP; */
    /*   case CHAR_EOF: */
    /*     indent = 0; */
    /*     newlines++; */
    /*     break; */
    /*   case CHAR_CARRIAGE_RETURN: */
    /*     indent = 0; */
    /*   case CHAR_NEWLINE: */
    /*     newlines++; */
    /*     indent = 0; */
    /* } */

    if (scanner->lookahead == CHAR_SPACE
        || scanner->lookahead == CHAR_VERTICAL_TAB
        || scanner->lookahead == CHAR_FORM_FEED) {
      indent += 1;
    } else if (scanner->lookahead == CHAR_TAB) {
      indent += TAB_STOP; 
    } else if (scanner->lookahead == CHAR_EOF) {
      indent = 0;
      newlines++;
      break;
    } else if (scanner->lookahead == CHAR_CARRIAGE_RETURN) {
      indent = 0;
    } else if (scanner->lookahead == CHAR_NEWLINE) {
      newlines++;
      indent = 0;
    } else {
      break;
    }
    scanner->skip(scanner);
  }
  
  int current_indent = scanner->back(scanner);

  if (indent > current_indent && valid_symbols[T_INDENT]) {
    scanner->push(scanner, indent);
    lexer->result_symbol = T_INDENT;
    return true;
  }

  if (newlines) {
    if (indent < current_indent && valid_symbols[T_DEDENT]) {
      scanner->pop(scanner);
      lexer->result_symbol = T_DEDENT;
      return true;
    }

    if (newlines > 1 && valid_symbols[T_BLANKLINE]) {
      lexer->result_symbol = T_BLANKLINE;
      return true;
    }
    
    if (newlines == 1 && valid_symbols[T_NEWLINE_INDENT] && indent > current_indent) {
      scanner->push(scanner, indent);
      lexer->result_symbol = T_NEWLINE_INDENT;
      return true;
    }

    if (valid_symbols[T_NEWLINE]) {
      lexer->result_symbol = T_NEWLINE;
      return true;
    }
  }
  
  return false;
}

bool parse_char_bullet(MDScanner* scanner) 
{
  const bool* valid_symbols = scanner->valid_symbols;
  TSLexer* lexer = scanner->lexer;

  if (!is_char_bullet(scanner->lookahead) || !valid_symbols[T_CHAR_BULLET]) {
    return false;
  }
  scanner->advance(scanner);
  bool ok = parse_inner_list_element(scanner, 1, T_CHAR_BULLET);
  if (ok) {
    return true;
  }
  return parse_text(scanner);
}

bool parse_numeric_bullet(MDScanner* scanner)
{
  const bool* valid_symbols = scanner->valid_symbols;

  if (!valid_symbols[T_NUMERIC_BULLET]) {
    return false;
  }

  bool parenthesized = false;
  if (scanner->lookahead == '(') {
    scanner->advance(scanner);
    parenthesized = true;
  }

  if (is_numeric_bullet(scanner->lookahead)) {
    return parse_inner_numeric_bullet(scanner, parenthesized);
  }

  return false;
  
}

bool parse_inline_markup(MDScanner* scanner);
bool parse_explict_markup_start(MDScanner* scanner);
bool parse_inner_inline_markup(MDScanner* scanner, unsigned type);
