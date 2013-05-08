#ifndef _CODEGEN_HEADER_
#define _CODEGEN_HEADER_
#include <string>
#include "input.h"

class Codegen {
  private:
    static const char switch_char;

    // static header file content
    static const std::string headerFileText;

    // dynamic parts of source file
    std::string sourceFileMembers;
    std::string sourceFlagCheckProcess;
    std::string sourceDefaultAssignProcess;
    std::string sourceArgCheckProcess;

    // static source file content
    static const std::string sourceFileText;

    // the only dynamic part of header file
    std::string headerFileMembers;

    static std::string str_fmt(const char * fmt, ...);

	  void process_header(const Input& i);
	  void process_source(const Input& i);
	
	  std::string get_header() const;
	  std::string get_source() const;

	  std::string outFileName;

  public:
    Codegen();
	  Codegen(std::string /*fname*/);

    void process(const Input& i);
    bool write() const;
};
#endif
