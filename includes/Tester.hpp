#pragma once

#include "Instance.hpp"

#include <iostream>
#include <string>
#include <memory>

namespace pem {
  class Tester {
    std::unique_ptr<Instance> IN, OUT;
  public:
    Tester(const std::string&, const std::string&);
    void run() {}
  };
}
