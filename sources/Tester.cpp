#include "Tester.hpp"

using namespace pem;

Tester::Tester(const std::string &InFile, const std::string &OutFile) {
  IN = std::unique_ptr<Input>(new Input(InFile));
}
