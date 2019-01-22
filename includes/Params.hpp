#pragma once

#include "llvm/Support/YAMLTraits.h"

namespace pem {
  struct PEMParams {
    unsigned TotalPaidTime;
    unsigned StretchTime;
    unsigned Overtime;
    unsigned SprendoverTime;

    //struct RestTime {
    //  enum 
    //};
  };
}

template <> struct llvm::yaml::MappingTraits<pem::PEMParams> {
  static void mapping(llvm::yaml::IO &io, pem::PEMParams &params);
};
