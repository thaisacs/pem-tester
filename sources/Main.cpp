#include <iostream>

#include "Util.hpp"
#include "Params.hpp"
#include "Tester.hpp"

#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/YAMLTraits.h"

std::string InFile, OutFile;

int main(int argc, char **argv) {
  VerifyArgs(argc, argv);

  pem::Tester T(InFile, OutFile);

  auto InputBuffer = llvm::MemoryBuffer::getFile("../tests/params.yaml");
  llvm::yaml::Input yin(InputBuffer->get()->getBuffer());
  
  pem::PEMParams Params;
  yin >> Params;
  
  //T.run();

  return 0;
}
