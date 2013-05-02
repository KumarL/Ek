#include <cstring>
#include <string>
typedef enum {
  _E_ZERO_INPUT = -1,
  _E_NO_PARAM_VALUE = -2
} ErrorT;
class Inputs {
  private:
    static const char switch_char = '-';

    static const std::string usage_str;

    static bool IsSwitch(const char * p) {
      return nullptr == p ? false:
        switch_char == p[0];
    }

  public:

    static bool m;
    static bool k;
    static std::string comp;
    static std::string timer;

    static ErrorT Process(int argc, char ** argv) {
      if (argc <= 0)
        return _E_ZERO_INPUT;

      for (int i = 1; i < argc; ++i) {
        char * arg = argv[i];

        if (0==strcmp(arg, "-m"))
          m = true;
        else if (0==strcmp(arg, "-k"))
          k = true;
        else if (0==strcmp(arg, "-comp")) {
          if (++i == argc) {
            fprintf(stdout, "There is no value specified to comp param.\n");
            return _E_NO_PARAM_VALUE;
          }
          comp = argv[i];
          continue;
        }
        else if (0==strcmp(arg, "-timer")) {
          if (++i == argc) {
            fprintf(stdout, "There is no value specified to timer param.\n");
            return _E_NO_PARAM_VALUE;
          }
          timer = argv[i];
          continue;
        }
        else if (0==strcmp(arg, "-comp")) {
          if (++i == argc) {
            fprintf(stdout, "There is no value specified to comp param.\n");
            return _E_NO_PARAM_VALUE;
          }
          comp = argv[i];
          continue;
        }
        else if (0==strcmp(arg, "-timer")) {
          if (++i == argc) {
            fprintf(stdout, "There is no value specified to timer param.\n");
            return _E_NO_PARAM_VALUE;
          }
          timer = argv[i];
          continue;
        }
      }
      //arg checking
      if(comp.empty()) {
        fprintf(stderr, "Error: comp is a required input and should be specified.");
        return _E_NO_PARAM_VALUE;
      }

      if(timer.empty()) {
        fprintf(stderr, "Error: timer is a required input and should be specified.");
        return _E_NO_PARAM_VALUE;
      }


      return static_cast<ErrorT>(0);
    }
};

int main() {
  return 0;
}
