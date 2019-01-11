#include <iostream>

#include "Util.hpp"
#include "Tester.hpp"

std::string InFile, OutFile;

int main(int argc, char **argv) {
  VerifyArgs(argc, argv);

  pem::Tester T(InFile, OutFile);

  T.run();

  return 0;
}
