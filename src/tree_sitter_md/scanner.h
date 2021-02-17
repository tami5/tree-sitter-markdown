#ifndef TREE_SITTER_MD_SCANNER_H
#define TREE_SITTER_MD_SCANNER_H

#define MD_SCANNER_STACK_MAX_CAPACITY 99

#include <tree_sitter/parser.h>

typedef struct MDScanner MDScanner;

// TODO: track consumed_chars?
struct MDScanner {
  // Wrappers around the lexer.
  TSLexer* lexer;
  const bool* valid_symbols;

  int32_t lookahead;
  int32_t previous;

  void (*advance)(MDScanner* scanner);
  void (*skip)(MDScanner* scanner);

  // Functions for the indentation levels.
  int* indent_stack;
  unsigned length;

  void (*push)(MDScanner* scanner, int value);
  int (*pop)(MDScanner* scanner);
  int (*back)(const MDScanner* scanner);

  // Functions for the scanner.
  unsigned (*serialize)(MDScanner* scanner, char* buffer);
  void (*deserialize)(MDScanner* scanner, const char* buffer, unsigned length);
  bool (*scan)(MDScanner* scanner);
};

MDScanner* new_md_scanner();

void destroy_md_scanner(MDScanner* scanner);

void md_scanner_advance(MDScanner* scanner);
void md_scanner_skip(MDScanner* scanner);
void md_scanner_push(MDScanner* scanner, int value);

int md_scanner_pop(MDScanner* scanner);
int md_scanner_back(const MDScanner* scanner);

unsigned md_scanner_serialize(MDScanner* scanner, char* buffer);
void md_scanner_deserialize(MDScanner* scanner, const char* buffer, unsigned length);
bool md_scanner_scan(MDScanner* scanner);

#endif /* ifndef TREE_SITTER_MD_SCANNER_H */
