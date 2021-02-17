#ifndef TREE_SITTER_MD_TOKENS_H_
#define TREE_SITTER_MD_TOKENS_H_
enum TokenType {
  T_NEWLINE,
  T_BLANKLINE,
  T_INDENT,
  T_NEWLINE_INDENT,
  T_DEDENT,
  
  // Lists
  T_CHAR_BULLET,
  T_NUMERIC_BULLET,
  
  // Inline markup
  T_TEXT,
  T_EMPHASIS,
  T_STRONG,
  T_STRIKE,
  T_SPAN,
  T_LINK,

  // Sections
  
  // Blocks
  
  // Markup blocks
  T_EXPLICIT_MARKUP_START,
  
};

#endif /* TREE_SITTER_MD_TOKENS_H_ */

