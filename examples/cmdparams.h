#include <string>

typedef enum {
  _E_ZERO_INPUT = -1,
  _E_NO_PARAM_VALUE = -2
} ErrorT;

class Inputs {
  private:
    static bool IsSwitch(const char * p);

    static const char switch_char = '-';

  public:
    static bool m;
    static bool k;
    static std::string comp;
    static std::string timer;

    static ErrorT Process(int argc, char ** argv);
};
