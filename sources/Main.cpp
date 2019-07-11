#include <iostream>

#include "Util.hpp"
#include "Params.hpp"
#include "Output.hpp"
#include "Tester.hpp"

#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/YAMLTraits.h"

std::string InFile, OutFile, ParamFile;
unsigned Size;

int main(int argc, char **argv) {
  VerifyArgs(argc, argv);

  pem::PEMParams Params;
  auto InputPBuffer = llvm::MemoryBuffer::getFile(ParamFile);
  llvm::yaml::Input yinp(InputPBuffer->get()->getBuffer());
  yinp >> Params;
  
  pem::PEMOutput Output;
  auto InputBuffer = llvm::MemoryBuffer::getFile(OutFile);
  llvm::yaml::Input yino(InputBuffer->get()->getBuffer());
  
  for(unsigned i = 0; i < Size; i++) {
    pem::JourneyOUT J;
    Output.Journeys.push_back(J);
  }
  
  yino >> Output;
  
  pem::Tester T(InFile, Output, Params);
  
  T.run();

  return 0;
}

// RESTRIÇÃO 6
// A possibilidade de sequênciamento entre duas tarefas ti e tj é definida por duas restrições:
//    tempo de término de ti <= tempo de inicio de tj;
//    ponto de troca de término de ti = ponto de troca de início de tj;
