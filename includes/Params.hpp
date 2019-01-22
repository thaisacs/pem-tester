#pragma once

#include "llvm/Support/YAMLTraits.h"

namespace pem {
  struct RestTimeStruct {
    unsigned Min, Max;
  };

  struct NightWorkingStruct {
    unsigned Start, End;
  };
  
  struct PEMParams {
    unsigned TotalPaidTime;
    unsigned StretchTime;
    unsigned Overtime;
    unsigned SprendoverTime;

    RestTimeStruct RestTime;
    NightWorkingStruct NightWorking;
  };
}

template <> struct llvm::yaml::MappingTraits<pem::RestTimeStruct> {
  static void mapping(llvm::yaml::IO &io, pem::RestTimeStruct &params);
};

template <> struct llvm::yaml::MappingTraits<pem::NightWorkingStruct> {
  static void mapping(llvm::yaml::IO &io, pem::NightWorkingStruct &params);
};

template <> struct llvm::yaml::MappingTraits<pem::PEMParams> {
  static void mapping(llvm::yaml::IO &io, pem::PEMParams &params);
};
