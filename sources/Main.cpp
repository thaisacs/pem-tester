#include <iostream>

#include "Util.hpp"
#include "Params.hpp"
#include "Tester.hpp"

#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/YAMLTraits.h"

std::string InFile, OutFile, ParamFile;

int main(int argc, char **argv) {
  VerifyArgs(argc, argv);

  auto InputBuffer = llvm::MemoryBuffer::getFile(ParamFile);
  llvm::yaml::Input yin(InputBuffer->get()->getBuffer());
  
  pem::PEMParams Params;
  yin >> Params;
  
  pem::Tester T(InFile, OutFile, Params);
  
  T.run();

  return 0;
}
