#include "codegen.h"
#include <stdio.h>
#include <cstdarg>

Codegen::Codegen() {
}

Codegen::Codegen(std::string fname)
	: outFileName(fname) {
  Codegen();
}

void
Codegen::process_header(const Input& i) {
  headerFileMembers += str_fmt(
"    static %s %s;\n",
    i.is_flag() ? "bool" : "std::string",
    i.get_name().c_str());
}

void
Codegen::process_source(const Input& i) {
  static bool is_first = true;

  // 1. First dynamic part of process method
  sourceFileMembers += str_fmt(
"%s Inputs::%s;\n",
    i.is_flag() ? "bool" : "std::string",
    i.get_name().c_str());

  // 2. Second dynamic part of process method
  std::string if_body;

  if (i.is_flag()){
    if_body = str_fmt(
"      %s = true;\n",
      i.get_name().c_str()
    );
  } else {
    if_body = str_fmt(
"      if (++i == argc) {\n\
         fprintf(stdout, \"There is no value specified to %s param.\\n\");\n\
         return _E_NO_PARAM_VALUE;\n\
       }\n\
       %s = argv[i];\n",
      i.get_name().c_str(),
      i.get_name().c_str()
    );
  }
  
  sourceFlagCheckProcess += str_fmt(
"    %sif (0 == strcmp(arg, \"%c%s\")) {\n\
       %s\n\
       continue;\n\
     }\n\
",
    is_first ? "" : "else ",
    switch_char,
    i.get_name().c_str(),
    if_body.c_str()
    );
    
  // 3. Third dynamic part of process method
  if (!i.is_flag() && i.is_name_optional()) {
    sourceDefaultAssignProcess += str_fmt(
  "    %sif (%s.empty()) {\n\
         %s = argv[1];\n\
         continue;\n\
       }\n",
       is_first ? "" : "else ",
       i.get_name(),
       i.get_name()
       );
  }

  // 4. Fourth dynamic part. We check our arg assignment
  if (!i.is_flag() && !i.is_value_optional()) {
    sourceArgCheckProcess += str_fmt(
"  if(%s.empty()) {\n\
     fprintf(stderr, \"Error: %s is a required input and should be specified.\");\n\
     return _E_NO_PARAM_VALUE;\n\
   }\n\n",
      i.get_name().c_str(),
      i.get_name().c_str()
      );
  }

  if (is_first)
    is_first = false;
 }

bool
Codegen::write() const {
  FILE * header_file = fopen(get_header().c_str(), "w");
  fprintf(
      header_file, 
      headerFileText.c_str(), 
      headerFileMembers.c_str());
      
  FILE * code_file = fopen(
    get_source().c_str(), 
    "w");
  fprintf(
    code_file,
    sourceFileText.c_str(),
    sourceFileMembers.c_str(),
    sourceFlagCheckProcess.c_str(),
    sourceDefaultAssignProcess.c_str(),
    sourceArgCheckProcess.c_str());

  return (0 == fclose(header_file)) && (0 == fclose(code_file));
}

void
Codegen::process(const Input& i) {
  process_header(i);
  process_source(i);
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

std::string
Codegen::get_header() const {
	return outFileName + ".h";
}

std::string
Codegen::get_source() const {
	return outFileName + ".cc";
}

// The file layout has four dynamic
// part that needs to be plugged.
// 1. definition of static class members
// 2. flag check part of process method
// 3. default assignment part of process method
// 4. the checking code of Process method
const std::string Codegen::sourceFileText =
"\
#include \"out.h\"\n\
#include <cstring>\n\
\n\
%s\n\
\n\
ErrorT\n\
Inputs::Process(int argc, char ** argv) {\n\
  if (argc <= 0)\n\
    return _E_ZERO_INPUT;\n\
\n\
  for (int i = 1; i < argc; ++i) {\n\
    char * arg = argv[i];\n\
\n\
    %s\n\
    %s\n\
  }\n\
\n\
  // arg checking\n\
  %s\n\
\n\
  return _E_NO_ERROR;\n\
}\n\
";

const std::string Codegen::headerFileText= 
"\n\
#ifndef _INPUTS_HEADER_\n\
#define _INPUTS_HEADER_\n\
#include <string>\n\
\n\
typedef enum {\n\
  _E_NO_ERROR = 0,\n\
  _E_ZERO_INPUT = -1,\n\
  _E_NO_PARAM_VALUE = -2\n\
} ErrorT;\n\
\n\
class Inputs {\n\
  public:\n\
%s\
    static ErrorT Process(int argc, char ** argv);\n\
};\n\
#endif\n\
";

const char Codegen::switch_char = '-';