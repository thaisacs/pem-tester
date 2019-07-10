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


// RESTRIÇÃO 6
// A possibilidade de sequênciamento entre duas tarefas ti e tj é definida por duas restrições:
//    tempo de término de ti <= tempo de inicio de tj;
//    ponto de troca de término de ti = ponto de troca de início de tj;
