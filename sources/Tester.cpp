#include "Tester.hpp"

using namespace pem;

Tester::Tester(const std::string &InFile, const std::string &OutFile,
    PEMParams &Params) : Params(std::move(Params)) {
  
  IN = std::make_unique<Input>(InFile);
  OUT = std::unique_ptr<Output>(new Output(OutFile, IN->getInstanceSize()));
  
  IN->print();
  std::cout << std::endl;
  OUT->print();
}
