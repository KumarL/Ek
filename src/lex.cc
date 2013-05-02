#include <ctype.h>
#include <stdio.h>
#include "lex.h"

Lexer::Lexer(const std::string& _usage) : 
  param_name_optional(false),
  param_value_optional(false),
  curr_usage_pos(9),
  usage_str(_usage) {
}

Token
Lexer::get_next_token() {
 return curr_tok = get_token();
}

const std::string& 
Lexer::get_identifier() const {
  return identifier_str;
}

const std::string& 
Lexer::get_param_name() const {
  return param_name;
}

const std::string& 
Lexer::get_param_value() const {
  return param_value;
}

const bool
Lexer::get_param_name_optional() const {
  return param_name_optional;
}

const bool 
Lexer::get_param_value_optional() const {
  return param_value_optional;
}

int 
Lexer::get_char(char& val) { 
  if (curr_usage_pos < usage_str.length())
  {
    val = usage_str[curr_usage_pos++];
    return 0;
  }

  return -1;
}

//gettok -- Return the next token from the input string
Token 
Lexer::get_token() {
  static char last_char = ' ';

  while (
      isspace(last_char) &&
      get_char(last_char) >= 0
      );

  if (curr_usage_pos == usage_str.length())
    return tok_eos;

  identifier_str = "";
  if (isalpha(last_char)) {
    identifier_str = last_char;
    while (
        get_char(last_char) >= 0 &&
        (isalnum(last_char) || '.' == last_char)
        )
    {
      identifier_str += last_char;
    }

    return tok_identifier;
  }

  // check for param, or switch
  bool param_name_or_value_optional = false;

  if ('[' == last_char) {
    get_char(last_char);

    if ('[' == last_char) {
      param_name_optional = param_value_optional = true;
      get_char(last_char);
    } else {
      param_name_or_value_optional = true;
    }
  }

  if (switch_char == last_char) {
    param_name = "";
    while (
        get_char(last_char) >= 0 &&
        isalpha(last_char)
        )
    {
      param_name += last_char;
    }

    if (param_name_optional && ']' != last_char) {
      fprintf(stderr, "Unterminated paranthesis");
    } else if (param_name_or_value_optional) {
      // Resolve the ambiguity now
      param_name_optional = ']' == last_char;
      param_value_optional = !param_name_optional;
    } else {
      param_name_optional = param_value_optional = false;
    }

    while (
        get_char(last_char) >= 0 &&
        isspace(last_char));

    if (curr_usage_pos == usage_str.length() ||
        '<' != last_char) {
      identifier_str = param_name;
      return tok_flag;
    }

    while (
        get_char(last_char) >= 0 &&
        '>' != last_char
        )
    {
      identifier_str += last_char;
    }

    if ('>' != last_char) {
      fprintf(stderr, "Unterminated value paranthesis: >");
    } else {
      get_char(last_char); // move the read position one char forward
    }

    if (param_value_optional &&
        get_char(last_char) &&
        ']' != last_char) {
      fprintf(stderr, "Unterminated paranthesis: >");
    }

    param_value = identifier_str;

    Token ret_tok = tok_param;

    param_name_optional = param_value_optional = false;

    return ret_tok;
  }

  return tok_eos;
}
