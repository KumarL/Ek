
#ifndef _PARAMS_HEADER_
#define _PARAMS_HEADER_
#include <string>

typedef enum {
  _E_NO_ERROR = 0,
  _E_ZERO_INPUT = -1,
  _E_NO_PARAM_VALUE = -2
} ErrorT;

class Params {
  public:
    static std::string str;
    static std::string outnamespace;
    static std::string out;
    static ErrorT Process(int argc, char ** argv);
};
#endif
