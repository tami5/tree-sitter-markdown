#include "tree_sitter_md/chars.h"
#include <bits/stdint-intn.h> // added automatically ??
#include <string.h>

bool is_newline(int32_t c) 
{
  const int32_t newline_chars[] = {
    CHAR_EOF, CHAR_NEWLINE, CHAR_CARRIAGE_RETURN,
  };

  const int length = 3;

  for (int i = 0; i < length; i++) {
    if (c == newline_chars[i]) {
      return true;
    }
  }
  return false;
}

bool is_space(int32_t c) 
{
  const int32_t space_chars[] = {
    CHAR_SPACE, CHAR_FORM_FEED, CHAR_TAB, CHAR_VERTICAL_TAB,
  };
  
  const int length = 4;
  bool is_space_char = false;

  for (int i = 0; i < length; i++) {
    if (c == space_chars[i]) {
      is_space_char = true;
      break;
    }
  }
  return is_space_char || is_newline(c);
}

bool is_number(int32_t c) 
{
  const int32_t numbers[] = {
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9',
  };
  const int length = 10;
  for (int i = 0; i < length; i++) {
    if (c == numbers[i]) {
      return true;
    }
  }
  return false;
}

bool is_abc_lower(int32_t c) 
{
  const int32_t abc[] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z',
  };
  const int length = 26;
  for (int i = 0; i < length; i++) {
    if (c == abc[i]) {
      return true;
    }
  }
  return false;
}

bool is_abc_upper(int32_t c) 
{
  const int32_t abc[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z',
  };
  const int length = 26;
  for (int i = 0; i < length; i++) {
    if (c == abc[i]) {
      return true;
    }
  }
  return false;
}

bool is_abc(int32_t c) 
{
  return is_abc_lower(c) || is_abc_upper(c);
}

bool is_alphanumeric(int32_t c) 
{
  return is_abc(c) || is_number(c);
}

bool is_escapable(int32_t c) 
{
  const int32_t escapable_chars[] = {
    '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',',
    '-', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', '\\',
    ']', '^', '_', '`', '{', '|', '}', '~',
  };
  const int length = 32;
  for (int i = 0; i < length; i++) {
    if (c == escapable_chars[i]) {
      return true;
    }
  }
  return false;
}

bool is_start_char(int32_t c) 
{
  const int32_t valid_chars[] = {
    '-', ':', '/', '\'', '"',
    '<', '(', '[', '{',
  };
  const int length = 9;
  for (int i = 0; i < length; i++) {
    if (c == valid_chars[i]) {
      return true;
    }
  }
  return false;
}

bool is_end_char(int32_t c)
{
  const int32_t valid_chars[] = {
    '-', '.', ',', ':', ';', '!',
    '?', '\\', '/', '\'', '"', ')',
    ']', '}', '>',
  };
  const int length = 15;
  for (int i = 0; i < length; i++) {
    if (c == valid_chars[i]) {
      return true;
    }
  }
  return false;
}

bool is_inline_markup_start_char(int32_t c)
{
  const int32_t inline_markup_chars[] = {
    '*', // *emphasis*, and **strong**.
    '_', // _emphasis_, and __strong__..
    '~', // ~~strikethrough~~
    '`', // `span`
    '[', // [link].
  };
  const int length = 5;
  for (int i = 0; i < length; i++) {
    if (c == inline_markup_chars[i]) {
      return true;
    }
  }
  return false;
}

bool is_inline_markup_end_char(int32_t c)
{
  const int32_t inline_markup_chars[] = {
    '*', // *emphasis*, and **strong**.
    '_', // _emphasis_, and __strong__..
    '~', // ~~strikethrough~~
    '`', // `span`,
    ']', // [link].
  };
  const int length = 4;
  for (int i = 0; i < length; i++) {
    if (c == inline_markup_chars[i]) {
      return true;
    }
  }
  return false;
}

bool is_char_bullet(int32_t c)
{
  const int32_t bullets[] = {
    '*',
    '+',
    '-',
    8226, // '•'
    8227, // '‣'
    8259, // '⁃'
  };
  const int length = 6;
  for (int i = 0; i < length; i++) {
    if (c == bullets[i]) {
      return true;
    }
  }
  return false;
}

bool is_numeric_bullet(int32_t c)
{
  return is_number(c); // 1. / 1)
}

int get_indent_level(MDScanner* scanner)
{
  int32_t current = scanner->lookahead;
  int indent = 0;

  while (true) {
    current = scanner->lookahead;
    if (current == CHAR_SPACE || current == CHAR_VERTICAL_TAB || current == CHAR_FORM_FEED) {
      indent += 1;
    } else if (current == CHAR_TAB) {
      indent += TAB_STOP;
    } else {
      break;
    }
    scanner->advance(scanner);
  }

  return indent;
}

bool is_known_schema(char* string, unsigned string_len)
{
  char* valid_schemas[] = {
    "http",
    "https",
    "ftp",
    "mailto",
    "telnet",
    "ssh",
  };
  const int length = 6;
  for (int i = 0; i < length; i++) {
    if (string_len != strlen(valid_schemas[i])) {
      continue;
    }
    int result = memcmp(string, valid_schemas[i], string_len);
    if (result == 0) {
      return true;
    }
  }
  return false;
}

bool is_invalid_uri_char(int32_t c)
{
  const int32_t invalid_chars[] = {
    '^',
    '}',
    '{',
    '\\',
  };
  const int length = 4;
  for (int i = 0; i < length; i++) {
    if (c == invalid_chars[i]) {
      return true;
    }
  }
  return false;
}
