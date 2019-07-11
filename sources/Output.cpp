#include "Output.hpp"

using namespace llvm::yaml;
using namespace pem;

using llvm::yaml::MappingTraits;
using llvm::yaml::SequenceTraits;
using llvm::yaml::IO;

void MappingTraits<JourneyOUT>::mapping(IO &io, JourneyOUT &Params) {
  io.mapRequired("Tasks", Params.Tasks);
}
  
//void MappingTraits<pem::TaskOUT>::mapping(IO &io, 
//    TaskOUT &Params) {
//  io.mapRequired("ID", Params.ID);
//  io.mapRequired("EndHour", Params.EndHour);
//  io.mapRequired("EndMinutes", Params.EndMinutes);
//}

size_t SequenceTraits<std::vector<pem::TaskOUT>>::size(IO &io, 
        std::vector<pem::TaskOUT> &T) {
    return T.size();
}

void MappingTraits<PEMOutput>::mapping(IO &io, PEMOutput &Params) {
  io.mapRequired("Journeys", Params.Journeys);
}

pem::TaskOUT& SequenceTraits<std::vector<pem::TaskOUT>>::element(IO &io, 
        std::vector<pem::TaskOUT> &List, size_t Index) {
    return List[Index];
}

size_t SequenceTraits<std::vector<pem::JourneyOUT>>::size(IO &io, 
        std::vector<pem::JourneyOUT> &J) {
    return J.size();
}

pem::JourneyOUT& SequenceTraits<std::vector<pem::JourneyOUT>>::element(IO &io, 
        std::vector<pem::JourneyOUT> &List, size_t Index) {
    return List[Index];
}
