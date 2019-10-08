#pragma once

#include "Instance.hpp"
#include "Params.hpp"
#include "Output.hpp"

#include <iostream>
#include <string>
#include <memory>
#include <vector>

namespace pem {
  class Tester {
    std::unique_ptr<Input> IN;
    PEMOutput Output;
    PEMParams Params;
    unsigned status;
  public:
    Tester(const std::string&, PEMOutput&, PEMParams&);
    void run();
  private:
    void checkForSequencing();
    void checkWorkDay();
    void checkTasksAmount();
    std::vector<unsigned> getRestTime(unsigned);
    std::vector<unsigned> getRestTimeIndex(unsigned);
    unsigned getStretchTime(unsigned, unsigned);
    int calculateInterval(Time, Time);
    unsigned getSprendoverTime(unsigned);
    void dumpError(unsigned);
  };
}
