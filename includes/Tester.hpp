#pragma once

#include "Instance.hpp"
#include "Params.hpp"

#include <iostream>
#include <string>
#include <memory>
#include <vector>

namespace pem {
  class Tester {
    std::unique_ptr<Input> IN;
    std::unique_ptr<Output> OUT;
    PEMParams Params;
    unsigned status;
    public:
    Tester(const std::string&, const std::string&, PEMParams&);
    void run(); 
  private:
    void checkForSequencing();
    void checkWorkDay();
    std::vector<unsigned> getRestTime(unsigned); 
    std::vector<unsigned> getRestTimeIndex(unsigned); 
    unsigned getStretchTime(unsigned, unsigned); 
    int calculateInterval(Time, Time);
    unsigned getSprendoverTime(unsigned);
    void objectiveFunction();
    void dumpError(unsigned);
  };
}
