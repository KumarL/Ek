#include "params.h"
#include <cstring>

std::string Params::str;
std::string Params::outnamespace;
std::string Params::out;


ErrorT
Params::Process(int argc, char ** argv) {
  if (argc <= 0)
    return _E_ZERO_INPUT;

  for (int i = 1; i < argc; ++i) {
    char * arg = argv[i];

    if (0 == strcmp(arg, "-str")) {
      if (++i == argc) {
        fprintf(stdout, "There is no value specified to str param.\n");
        return _E_NO_PARAM_VALUE;
      }
      str = argv[i];
      continue;
    }
    else if (0 == strcmp(arg, "-outnamespace")) {
      if (++i == argc) {
        fprintf(stdout, "There is no value specified to outnamespace param.\n");
        return _E_NO_PARAM_VALUE;
      }
      outnamespace = argv[i];
      continue;
    }
    else if (0 == strcmp(arg, "-out")) {
      if (++i == argc) {
        fprintf(stdout, "There is no value specified to out param.\n");
        return _E_NO_PARAM_VALUE;
      }
      out = argv[i];
      continue;
    }
    else if (str.empty()) {
       str = argv[i];
       continue;
     }

  }

  // arg checking
  if(str.empty()) {
    fprintf(stderr, "Error: str is a required input and should be specified.\n");
    return _E_NO_PARAM_VALUE;
  }

  if(out.empty()) {
    fprintf(stderr, "Error: out is a required input and should be specified.\n");
    return _E_NO_PARAM_VALUE;
  }


  return _E_NO_ERROR;
}
