#include "Params.hpp"

using namespace llvm::yaml;
using namespace pem;

void MappingTraits<PEMParams>::mapping(IO &io, PEMParams &params) {
  io.mapRequired("TotalPaidTime", params.TotalPaidTime);
  io.mapRequired("StretchTime", params.StretchTime);
  io.mapRequired("Overtime", params.Overtime);
  io.mapRequired("SprendoverTime", params.SprendoverTime);
}
