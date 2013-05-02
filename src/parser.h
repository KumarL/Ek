#ifndef _PARSER_HEADER_
#define _PARSER_HEADER_
#include <string>
#include "input.h"

namespace Parser {
  const Input HandleIdentifier(const std::string& identifier_name);
  const Input HandleParam(
      const std::string& name,
      const std::string& value,
      const bool is_name_optional,
      const bool is_value_optiona);
  const Input HandleFlag(const std::string& name);
}
#endif
