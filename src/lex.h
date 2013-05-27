#ifndef _LEX_HEADER_
#define _LEX_HEADER_
#include <string>

enum Token {
  tok_eos        = -1, // End of input string
  
  tok_param      = -2,

  tok_flag       = -3,

  tok_identifier = -8
};

class Lexer {
  private:
    bool         param_name_optional;
    bool         param_value_optional;
    char         last_char;
    size_t       curr_usage_pos;
    Token        curr_tok;
    std::string  param_name;
    std::string  param_value;
    std::string  identifier_str;
    std::string  usage_str;

    Token        get_token();
    int          get_char(char& val);

    const static char switch_char = '-';

  public:
    Lexer(const std::string&);
    Token get_next_token();
    const std::string& get_identifier()  const;
    const std::string& get_param_name()  const;
    const std::string& get_param_value() const;

    const bool get_param_name_optional()  const;
    const bool get_param_value_optional() const;
};
#endif
