#include <iostream>
#include <string>
#include <stdio.h>
#include <list>
#include "input.h"
#include "lex.h"
#include "parser.h"
#include "codegen.h"

int main(int argc, char ** argv)
{
  const std::string usage_str = "shutdown [-m] [-k] [-comp] <computer name> -timer <number in seconds>";

  Lexer lexer(usage_str);

  std::list<Input> inputs;

  Token curr_tok;
  while (tok_eos != (curr_tok = lexer.get_next_token())) {
    switch (curr_tok) {
      case tok_identifier:
        {
          inputs.push_back(Parser::HandleIdentifier(
                lexer.get_identifier()));
        }
        break;
      case tok_param:
        {
          Input inp_param = Parser::HandleParam(
              lexer.get_param_name(),
              lexer.get_param_value(),
              lexer.get_param_name_optional(),
              lexer.get_param_value_optional()
              );
          inputs.push_back(inp_param);
        }
        break;
      case tok_flag:
        {
          Input inp_flag = Parser::HandleFlag(
            lexer.get_identifier());
          inputs.push_back(inp_flag);
        }
        break;
      case tok_eos:
      default:
        break;
    }
  }

  Codegen cg;
  for (auto& input : inputs) {
    cg.process(input);
  }
  
  cg.write("out.cc");

  return 0;
}
