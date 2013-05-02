#ifndef _CODEGEN_HEADER_
#define _CODEGEN_HEADER_
#include <string>
#include "input.h"

class Codegen {
  private:
    std::string membersText;
    std::string processMethodText;
    std::string processMethodTextTailTests;
    std::string processMethodTextTailTestsForErrors;

    static const std::string headerText;
    static const std::string typeText;
    static const std::string classPreambleText;
    static const std::string printUsageText;
    static const std::string processMethodTrail;
    static const char switch_char;

    static std::string str_fmt(const char * fmt, ...);


  public:
    Codegen();
    void process(Input i);
    bool write(const std::string& filename) const;

    void test(Input i);
    std::string get_mem_test();
};
#endif
