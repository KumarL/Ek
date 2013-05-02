#include "parser.h"

const Input
Parser::HandleIdentifier(const std::string& identifier_name) {
  Input inp_identifier(identifier_name, false);
  return inp_identifier;
}

const Input
Parser::HandleParam(
      const std::string& name,
      const std::string& value,
      const bool is_name_optional,
      const bool is_value_optional) {
  Input inp_param(
      name,
      value,
      is_name_optional,
      is_value_optional
      );
  return inp_param;
}

const Input
Parser::HandleFlag(const std::string& name) {
  Input inp_flag(name, true);
  return inp_flag;
}
