#include "Params.hpp"

using namespace llvm::yaml;
using namespace pem;

void MappingTraits<RestTimeStruct>::mapping(IO &io, RestTimeStruct &params) {
  io.mapRequired("Min", params.Min);
  io.mapRequired("Max", params.Max);
}
  
void MappingTraits<NightWorkingStruct>::mapping(IO &io, 
    NightWorkingStruct &params) {
  io.mapRequired("Start", params.Start);
  io.mapRequired("End", params.End);
}

void MappingTraits<PEMParams>::mapping(IO &io, PEMParams &params) {
  io.mapRequired("TotalPaidTime", params.TotalPaidTime);
  io.mapRequired("StretchTime", params.StretchTime);
  io.mapRequired("Overtime", params.Overtime);
  io.mapRequired("SprendoverTime", params.SprendoverTime);
  
  io.mapRequired("RestTime", params.RestTime);
  io.mapRequired("NightWorking", params.NightWorking);
}
