#pragma once

#include "Instance.hpp"
#include "Params.hpp"

#include <iostream>
#include <string>
#include <memory>

namespace pem {
  class Tester {
    std::unique_ptr<Input> IN;
    std::unique_ptr<Output> OUT;
    PEMParams Params;
  public:
    Tester(const std::string&, const std::string&, PEMParams&);
    void run() {}
  };
}
