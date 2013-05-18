#include "out.h"
#include <cstring>

bool Inputs::m;
bool Inputs::k;
std::string Inputs::comp;
std::string Inputs::timer;

ErrorT 
Inputs::Process(int argc, char ** argv) {
  if (argc <= 0)
    return _E_ZERO_INPUT;

  for (int i = 1; i < argc; ++i) {
    char * arg = argv[i];

    if (0==strcmp(arg, "-m")) {
      m = true;
      continue;
    }
    else if (0==strcmp(arg, "-k")) {
      k = true;
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
    else if (comp.empty()) {
      comp = argv[i];
      continue;
    }
    else if (timer.empty()) {
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
  
  return _E_NO_ERROR;
}

int main() {
  return 0;
}
