#include "Tester.hpp"

using namespace pem;

Tester::Tester(const std::string &InFile, const std::string &OutFile,
    PEMParams &Params) : Params(std::move(Params)) {
  IN = std::unique_ptr<Input>(new Input(InFile));
  OUT = std::unique_ptr<Output>(new Output(OutFile, IN->getInstanceSize()));
}
