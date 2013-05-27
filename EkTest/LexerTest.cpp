// This file contains all the functions defined to test Ek's Lexer

#include "lex.h"
#include "input.h"
#include "parser.h"
#include <string>
#include <algorithm>
#include <list>

typedef std::list<Input> InputsT;

int lex_inputs(Lexer& lexer, InputsT& inputs) {
  Token curr_tok;
  while (tok_eos != (curr_tok = lexer.get_next_token())) {
    switch (curr_tok) {
      case tok_identifier:
        {
          // We primarily care only about a parameter or
          // a flag. An identifier is likely the name of
          // the program. We can reserve its use for future
          // purpose, but we don't need it now.
          continue;
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
        break;
      default:
        return curr_tok; // Totally unexpected
    }
  }

  return 0;
}

int test_lexer(const char * usage, const InputsT& inputs) {
  Lexer lexer(usage);

  InputsT found_inputs;

  int ret_code;
  if (0 > (ret_code = lex_inputs(lexer, found_inputs))) {
    fprintf(stderr, "FAILED: test_lexer while lexing. Expected: 0. Found: %d\n", ret_code);
    return ret_code;
  }

  if (inputs.size() != found_inputs.size()) {
    fprintf(
      stderr, 
      "FAILED: test_lexer while lexing. Expected inputs: %d. Found inputs: %d\n",
      inputs.size(),
      found_inputs.size());
    return -1;
  }

  auto inputs_eq_comp     = [] (const Input& inp1, const Input& inp2) {    
    if (!(
      inp1.get_name() == inp2.get_name() &&
      inp1.has_value() == inp2.has_value() &&
      inp1.is_flag() == inp2.is_flag() &&
      inp1.is_name_optional() == inp2.is_name_optional() &&
      inp1.is_value_optional() == inp2.is_value_optional()))
      return false;

    if (inp1.has_value() && (inp1.get_value() != inp2.get_value()))
      return false;

    return true;
  };
  
  auto inputs_iter        = inputs.begin();
  auto found_inputs_iter  = found_inputs.begin();

  if (!std::equal(inputs_iter, inputs.end(), found_inputs_iter, inputs_eq_comp)) {
    // inputs_iter and found_inputs_iter points to the first item that did not match
    fprintf(
      stderr, 
      "FAILED: test_lexer while validatings inputs. Expected: %s. Found: %s\n",
      inputs_iter->get_name().c_str(),
      found_inputs_iter->get_name().c_str());
    return -1;
  }

  return 0;
}

int RunTests() {
  // Test 1
  const char * usage_str1 = "foo.exe -param1 <param 1>";

  InputsT expected_inputs1;
  expected_inputs1.push_back(
    Parser::HandleParam(
    "param1",
    "param 1",
    false,
    false
    )
  );

  fprintf(stdout, "Starting Test 1...\n");

  int ret_code;
  if (0 > (ret_code = test_lexer(usage_str1, expected_inputs1))) {
    return ret_code;
  }

  // Test 2
  const char * usage_str2 = "foo.exe [-first_param] <first param value> [[-second_param]\
    <second param value>] [-first_flag] [-second_flag]";

  InputsT expected_inputs2;
  
  expected_inputs2.push_back(
    Parser::HandleParam(
    "first_param",
    "first param value",
    true,
    false
    )
  );

  expected_inputs2.push_back(
    Parser::HandleParam(
    "second_param",
    "second param value",
    true,
    true)
    );

  expected_inputs2.push_back(
    Parser::HandleFlag(
    "first_flag"));

  expected_inputs2.push_back(
    Parser::HandleFlag(
    "second_flag"));

  fprintf(stdout, "Starting Test 2...\n");

  if (0 > (ret_code = test_lexer(usage_str2, expected_inputs2))) {
    return ret_code;
  }

  return 0;
}

int main() {
  return RunTests();
}