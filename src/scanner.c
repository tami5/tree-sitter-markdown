#include <tree_sitter/parser.h>

#include "tree_sitter_md/scanner.c"
#include "tree_sitter_md/tokens.h"

void* tree_sitter_md_external_scanner_create()
{
  return new_md_scanner();
}

void tree_sitter_md_external_scanner_destroy(void* payload)
{
  destroy_md_scanner(payload);
}

unsigned tree_sitter_md_external_scanner_serialize(
    void* payload,
    char* buffer)
{
  MDScanner* scanner = payload;
  return scanner->serialize(scanner, buffer);
}

void tree_sitter_md_external_scanner_deserialize(
    void* payload,
    const char* buffer,
    unsigned length)
{
  MDScanner* scanner = payload;
  scanner->deserialize(scanner, buffer, length);
}

bool tree_sitter_md_external_scanner_scan(
    void* payload,
    TSLexer* lexer,
    const bool* valid_symbols)
{
  MDScanner* scanner = (MDScanner*)payload;
  scanner->lexer = lexer;
  scanner->valid_symbols = valid_symbols;
  scanner->lookahead = lexer->lookahead;
  scanner->previous = lexer->lookahead;
  return scanner->scan(scanner);
}
