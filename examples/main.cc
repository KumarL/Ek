#include "cmdparams.cc"

int main(int argc, char ** argv) {
  ErrorT ret = Inputs::Process(argc, argv);

  if (0 != ret)
    Inputs::PrintUsage();
  else {
    fprintf(stdout, "%d\n", Inputs::m);
    fprintf(stdout, "%d\n", Inputs::k);
    fprintf(stdout, "%s\n", Inputs::comp.c_str());
    fprintf(stdout, "%s\n", Inputs::timer.c_str());
  }

  return 0;
}
