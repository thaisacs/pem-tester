#include "Util.hpp"

extern std::string InFile, OutFile, ParamFile;

void usage() {
  std::cout << "pemtester" << std::endl;
}

void VerifyArgs(int argc, char **argv) {
  char c;
  
  while((c = getopt(argc, argv, "ho:i:p:")) != -1) {
    switch(c) {
      case 'h':
        usage();
        exit(0);
      case 'o':
        OutFile = optarg;
        break;
      case 'i':
        InFile = optarg;
        break;
      case 'p':
        ParamFile = optarg;
        break;
    } 
  }
}

