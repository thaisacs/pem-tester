#pragma once

#include "llvm/Support/YAMLTraits.h"

namespace pem {
  struct TaskOUT {
    unsigned ID;
  };

  struct JourneyOUT {
    std::vector<unsigned> Tasks;
  };

  struct PEMOutput {
    std::vector<JourneyOUT> Journeys;
  };
}

LLVM_YAML_IS_SEQUENCE_VECTOR(pem::JourneyOUT)

template <> struct llvm::yaml::MappingTraits<pem::JourneyOUT> {
  static void mapping(llvm::yaml::IO &io, pem::JourneyOUT &Params);
};

template <> struct llvm::yaml::MappingTraits<pem::TaskOUT> {
  static void mapping(llvm::yaml::IO &io, pem::TaskOUT &Params);
};

template <> struct llvm::yaml::MappingTraits<pem::PEMOutput> {
  static void mapping(llvm::yaml::IO &io, pem::PEMOutput &Params);
};

template <> struct llvm::yaml::SequenceTraits<std::vector<pem::TaskOUT>> {
    static size_t size(llvm::yaml::IO&, std::vector<pem::TaskOUT>&);
    static pem::TaskOUT &element(llvm::yaml::IO&, std::vector<pem::TaskOUT>&, size_t);
};

template <> struct llvm::yaml::SequenceTraits<std::vector<pem::JourneyOUT>> {
    static size_t size(llvm::yaml::IO&, std::vector<pem::JourneyOUT>&);
    static pem::JourneyOUT &element(llvm::yaml::IO&, std::vector<pem::JourneyOUT>&, size_t);
};
