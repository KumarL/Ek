#include "codegen.h"
#include <stdio.h>
#include <cstdarg>

Codegen::Codegen() {
  processMethodText =
"\n\
static ErrorT Process(int argc, char ** argv) {\n\
  if (argc <= 0)\n\
    return _E_ZERO_INPUT;\n\
\n\
  for (int i = 1; i < argc; ++i) {\n\
    char * arg = argv[i];\n\
\n\
";
  processMethodTextTailTestsForErrors =
"     }\
\n\
      //arg checking\n";
}

std::string Codegen::get_mem_test() {
  return membersText;
}

void
Codegen::process(Input i) {
  static bool is_first_input = true;
  bool is_flag = i.is_flag();

  std::string i_m = str_fmt(
"    static %s %s;\n",
      is_flag ? "bool" : "std::string",
      i.get_name().c_str());

  membersText += i_m;

  std::string param_check = str_fmt(
"    %sif (0==strcmp(arg, \"%c%s\"))%s\n",
     is_first_input ? "" : "else ",
     switch_char,
     i.get_name().c_str(),
     is_flag ? "" : " {");
  if (is_flag) {
    std::string fs = str_fmt(
"       %s = true;\n",
        i.get_name().c_str());
    param_check += fs.c_str();
  } else {
    std::string fs = str_fmt(
"       if (++i == argc) {\n\
            fprintf(stdout, \"There is no value specified to %s param.\\n\");\n\
            return _E_NO_PARAM_VALUE;\n\
        }\n\
        %s = argv[i];\n\
        continue;\n\
      }\n",
      i.get_name().c_str(),
      i.get_name().c_str());
    param_check += fs.c_str();
    std::string ps = str_fmt(
        "else if (%s.empty()) {\n\
           %s = arg;\n\
         }\n",
         i.get_name().c_str(),
         i.get_name().c_str());
    processMethodTextTailTests += param_check.c_str();

    if (!i.is_value_optional()) {
      processMethodTextTailTestsForErrors += str_fmt(
"     if(%s.empty()) {\n\
        fprintf(stderr, \"Error: %s is a required input and should be specified.\");\n\
        return _E_NO_PARAM_VALUE;\n\
      }\n\n",
      i.get_name().c_str(),
      i.get_name().c_str()).c_str();
    }
  }
  processMethodText += param_check.c_str();

  if (is_first_input)
    is_first_input = false;
}

bool
Codegen::write(const std::string& filename) const {
  FILE * code_file;
  code_file = fopen(filename.c_str(), "w");
  fprintf(code_file, "%s", headerText.c_str());
  fprintf(code_file, "%s", typeText.c_str());
  fprintf(code_file, "%s", classPreambleText.c_str());
  fprintf(code_file, "%s", membersText.c_str());
  fprintf(code_file, "%s", processMethodText.c_str());
  fprintf(code_file, "%s", processMethodTextTailTests.c_str());
  fprintf(code_file, "%s", processMethodTextTailTestsForErrors.c_str());
  fprintf(code_file, "%s", processMethodTrail.c_str());
  return true;
}

std::string
Codegen::str_fmt(const char * fmt, ...) {
  int str_size = 512;
  std::string s;
  va_list param;

  va_start(param, fmt);
  while (true) {
    s.resize(str_size);
    int copied_size = vsnprintf(
        const_cast<char *> (s.c_str()),
        str_size,
        fmt,
        param);
    if (copied_size >= 0 && copied_size < str_size) {
      s.resize(copied_size);
      break;
    } else if (copied_size >= 0) {
      str_size = copied_size + 1;
    } else {
      str_size *= 2;
    }
  }
  va_end(param);
  return s;
}

const std::string Codegen::headerText =
"\
#include <cstring>\n\
#include <string>\n\
";

const std::string Codegen::typeText = 
"typedef enum {\n\
  _E_ZERO_INPUT = -1,\n\
  _E_NO_PARAM_VALUE = -2\n\
} ErrorT;";
  
const std::string Codegen::classPreambleText =
"\n\
class Inputs {\n\
  private:\n\
    static const char switch_char = '-';\n\
\n\
    static const std::string usage_str;\n\
\n\
    static bool IsSwitch(const char * p) {\n\
      return nullptr == p ? false:\n\
        switch_char == p[0];\n\
    }\n\
\n\
  public:\n\
\n\
";

const std::string Codegen::printUsageText =
"\n\
    static void PrintUsage() {\n\
      fprintf(stdout, \"Usage: %s\n\", usage_str.c_str());\n\
    }\n\
";

const char Codegen::switch_char = '-';

const std::string Codegen::processMethodTrail =
"\n\
     return static_cast<ErrorT>(0);\n\
   }\n\
};";

