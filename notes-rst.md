# Rst Custom scanner

- It's made of four main files with their header files except for `token.h`.
- The scanner files are grouped into a single directory under source `tree_sitter_rst`.

## chars.h/c
chars.h consist of functions and variables declarations. Namely:

- `CHAR_EOF` 0
- `CHAR_NEWLINE` 10
- `CHAR_CARRIAGE_RETURN` 13
- `CHAR_SPACE` ' '
- `CHAR_FORM_FEED` '\f'
- `CHAR_TAB` '\t'
- `CHAR_VERTICAL_TAB` '\v'
- `TAB_STOP` 4
- `CHAR_EMDASH` 8212
- `is_newline`, `is_space`, `is_number`, `is_abc`
- `is_alphanumeric`;
- `is_adornment_char`; with checks
- `is_start_char`; with addition
- `is_end_char`;
- `is_inline_markup_start_char`; with addition
- `is_inline_markup_end_char`; with addition
- `is_internal_reference_char`;
- `is_char_bullet`, is_numeric_bullet;
- `is_numeric_bullet_simple`;
- `is_known_schema`;
- `is_invalid_uri_char`;
- `is_attribution_mark`;
- `get_indent_level(RSTScanner* scanner)`;

## scanner.h/c

The main struct
```js
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
```

Functions:

- `new_md_scanner()` return `MDScanner`
  - allocate memory to scanner of the type `MDScanner`
  - sets scanner.advance to `md_scanner_advance`:
  - sets scanner.skip to `md_scanner_skip`
  - sets scanner.indent_stack to new located memory
  - sets scanner.length to `0`
  - sets scanner.push to `md_scanner_push`
  - sets scanner.pop to `md_scanner_pop`
  - sets scanner.back to `md_scanner_back`
  - sets scanner.serialize to `md_scanner_serialize`
  - sets scanner.deserialize to `md_scanner_deserialize`
  - sets scanner.scan to `md_scanner_scan`

- `destory_md_scanner()` destroys the scanner.
  - frees indent_stack
  - frees scanner

- `md_scanner_advance()`

## parser.h/c

