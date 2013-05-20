
#ifndef _INPUTS_HEADER_
#define _INPUTS_HEADER_
#include <string>

typedef enum {
  _E_NO_ERROR = 0,
  _E_ZERO_INPUT = -1,
  _E_NO_PARAM_VALUE = -2
} ErrorT;

class Inputs {
  public:
    static std::string str;
    static std::string outnamespace;
    static std::string out;
    static ErrorT Process(int argc, char ** argv);
};
#endif
