#include "Tester.hpp"

using namespace pem;

Tester::Tester(const std::string &InFile, const std::string &OutFile,
    PEMParams &Params) : Params(std::move(Params)) {
  
  IN = std::make_unique<Input>(InFile);
  OUT = std::unique_ptr<Output>(new Output(OutFile, IN->InstanceSize));

  status = 0;
}

bool checkTimes(Duration EndA, Time StartB, unsigned Opt) {
  if(EndA.Days == 0) {
    switch(Opt) {
      case 0:
        if(EndA.T.Hour > StartB.Hour)
          return false;
        if(EndA.T.Hour < StartB.Hour)
          return true;
        if(EndA.T.Minutes <= StartB.Minutes)
            return true;
        return false;
      case 1:
        if(EndA.T.Hour != StartB.Hour)
          return false;
        if(EndA.T.Minutes != StartB.Minutes)
          return false;
        return true;
    }
  }
  return false;
}

int Tester::calculateInterval(Time EndA, Time StartB) {
  int Minutes = StartB.Hour;

  if(StartB.Hour < EndA.Hour) {
    Minutes += 24;
  }

  Minutes -= EndA.Hour;
  Minutes *= 60;
  
  if(EndA.Hour == StartB.Hour) {
    Minutes += StartB.Minutes - EndA.Minutes;
  }else {
    Minutes -= EndA.Minutes;
    Minutes += StartB.Minutes;
  }
  
  if(Minutes < 0) {
    Minutes = 24*60 + Minutes;
  }

  return Minutes;
}

std::vector<unsigned> Tester::getRestTime(unsigned ID) {
  std::vector<unsigned> Intervals;
  int Interval = 0;
  
  for(unsigned j = 1; j < OUT->Journeys[ID]->Tasks.size(); j++) {
    unsigned ID_B = OUT->Journeys[ID]->Tasks[j]->getTaskID();
      
    auto EA = OUT->Journeys[ID]->Tasks[j-1]->getEndTime();      
    auto SB = IN->Tasks[ID_B]->getStartTime();      
     
    if(!checkTimes(EA, SB, 1)) {
      unsigned ID_B = OUT->Journeys[ID]->Tasks[j]->getTaskID();
      
      auto EA = OUT->Journeys[ID]->Tasks[j-1]->getEndTime();      
      auto SB = IN->Tasks[ID_B]->getStartTime();      
 
      Interval = calculateInterval(EA.T, SB);
      Intervals.push_back(Interval);  
    }
  }
  
  return Intervals;
}

std::vector<unsigned> Tester::getRestTimeIndex(unsigned ID) {
  std::vector<unsigned> Indexs;

  for(unsigned j = 1; j < OUT->Journeys[ID]->Tasks.size(); j++) {
    unsigned ID_B = OUT->Journeys[ID]->Tasks[j]->getTaskID();
      
    auto EA = OUT->Journeys[ID]->Tasks[j-1]->getEndTime();      
    auto SB = IN->Tasks[ID_B]->getStartTime();      
      
    if(!checkTimes(EA, SB, 1)) {
      Indexs.push_back(j);
      //unsigned ID_B = OUT->Journeys[ID]->Tasks[j]->getTaskID();
      //
      //auto EA = OUT->Journeys[ID]->Tasks[j-1]->getEndTime();      
      //auto SB = IN->Tasks[ID_B]->getStartTime();      
 
      //int Buffer = calculateInterval(EA.T, SB);
      
      //if(Buffer > Interval) {
      //Interval = Buffer;
      //}
    }
  }
 
  return Indexs;
}

unsigned Tester::getStretchTime(unsigned ID, unsigned Index) {
  if(Index < OUT->Journeys[ID]->Tasks.size() && Index > 0) {
    unsigned ID_A = OUT->Journeys[ID]->Tasks[0]->getTaskID();
  
    auto EA = OUT->Journeys[ID]->Tasks[Index-1]->getEndTime();      
    auto SB = IN->Tasks[ID_A]->getStartTime();      
    
    return calculateInterval(SB, EA.T);
  }

  return 0;
}

unsigned Tester::getSprendoverTime(unsigned ID) {
  unsigned Last = OUT->Journeys[ID]->Tasks.size() - 1;
  
  unsigned ID_A = OUT->Journeys[ID]->Tasks[0]->getTaskID();
  
  auto EA = OUT->Journeys[ID]->Tasks[Last]->getEndTime();      
  auto SB = IN->Tasks[ID_A]->getStartTime();      
  
  return calculateInterval(SB, EA.T);
}

void Tester::dumpError(unsigned i) {
  std::cout << "error jorney: ";
  std::cout << i << std::endl; 
  //switch(status) {
  //  case 1:
  //    std::string Msg = "Jornada[" + std::to_string(i);
  //    Msg += "]: não respeita a restrição de RestTime";
  //    std::cerr << Msg << std::endl;
  //    break;
  //  case 2:
  //    std::string Msg = "Jornada[" + std::to_string(i);
  //    Msg += "]: não respeita a restrição de StretchTime; ";
  //    Msg += "Jornada não tem descanso e o trabalho contínuo é excessivo ("; 
  //    Msg += std::to_string(SOT) + " > " + std::to_string(Params.StretchTime) + ");";
  //    std::cerr << Msg << std::endl;
  //    break;
  //  case 3:
  //    std::string Msg = "Jornada[" + std::to_string(i); 
  //    Msg += "]: não respeita a restrição de StretchTime; ";
  //    Msg += "Trabalho contínuo é excessivo ("; 
  //    Msg += std::to_string(ST) + " > " + std::to_string(Params.StretchTime) + ");";
  //    std::cerr << Msg << std::endl;
  //    break;
  //  case 4:
  //    std::string Msg = "Jornada[" + std::to_string(i);
  //    Msg += "]: não respeita a restrição de SprendoverTime";
  //    Msg += "Quantidade de trabalho excessiva ("; 
  //    Msg += std::to_string(SOT) + " > " + std::to_string(Params.StretchTime) + ");";
  //    std::cerr << Msg << std::endl;
  //    break;
  //}
}

void Tester::checkWorkDay() {
  for(int i = 0; i < OUT->Journeys.size(); i++) {
    bool isOK = false;
    
    auto RTIPossible = getRestTimeIndex(i);
    auto RTPossible = getRestTime(i);
    unsigned SOT = getSprendoverTime(i);
    unsigned ST = 0, RT = 0;

    for(unsigned j = 0; j < RTIPossible.size(); j++) {
      ST = getStretchTime(i, RTIPossible[j]);
      
      if(RTPossible[j] > Params.RestTime.Max)
          continue;
      
      if(RTPossible[j] < Params.RestTime.Min) {
        RTPossible[j] = 0;
        ST = 0;
      }
      
      if(RTPossible[j] == 0 && ST == 0) { 
        if(SOT > Params.StretchTime) 
          continue;
      }else {
        if(ST > Params.StretchTime)
          continue;
        
        if(SOT > Params.SprendoverTime)
          continue;
      }
    
      if(SOT - RTPossible[j] > Params.TotalPaidTime) {
        if(SOT - Params.TotalPaidTime - RTPossible[j] > Params.Overtime) {
          std::cout << SOT - Params.TotalPaidTime - RTPossible[j] << std::endl;
          continue;
        }
      }
      
      isOK = true;
      RT = RTPossible[j]; 
      break;
    }
   
    if(!isOK && !RTPossible.size()) {
      if(SOT <= Params.StretchTime) {
        isOK = true;
      }
    }
 

    if(!isOK)
      dumpError(i);
  } 
}

void Tester::checkForSequencing() {
  for(int i = 0; i < OUT->Journeys.size(); i++) {
    for(int j = 1; j < OUT->Journeys[i]->Tasks.size(); j++) {
      unsigned ID_A = OUT->Journeys[i]->Tasks[j-1]->getTaskID();
      unsigned ID_B = OUT->Journeys[i]->Tasks[j]->getTaskID();
    
      char DA = IN->Tasks[ID_A]->getDestination();
      char OB = IN->Tasks[ID_B]->getOrigin();

      if(DA != OB) {
        status = 1;
        std::string Msg = "Jornada[" + std::to_string(i);
        Msg += "]: Tarefa[" + std::to_string(j-1);
        Msg += "] e Tarefa[" + std::to_string(j);
        Msg += "] não são possíveis de serem sequenciadas;";
        std::cerr << Msg << std::endl;
      }

      //auto EA = OUT->Journeys[i]->Tasks[j-1]->getEndTime();      
      //auto SB = IN->Tasks[ID_B]->getStartTime();      
      
      //if(!checkTimes(EA, SB, 0)) {
      //  status = 1;
      //  std::cerr << "Jornada[" + std::to_string(i) +"]: Tarefa[" + std::to_string(j-1) + "] e Tarefa[" + std::to_string(j) + "] não são possíveis de serem sequenciadas." << std::endl;
      //}
    }
  }
}

void Tester::objectiveFunction() {}

void Tester::run() {
  checkForSequencing();
  checkWorkDay();
  
  if(!status) {
    objectiveFunction();
  }
}
