#include "Tester.hpp"
#include "Output.hpp"

using namespace pem;

Tester::Tester(const std::string &InFile, PEMOutput &Output,
    PEMParams &Params) : Params(std::move(Params)), Output(std::move(Output)) {
  
  IN = std::make_unique<Input>(InFile);

  status = 0;
}

bool checkTimes(Time EndA, Time StartB, unsigned Opt) {
  switch(Opt) {
    case 0:
      if(EndA.Hour > StartB.Hour)
        return false;
      if(EndA.Hour < StartB.Hour)
        return true;
      if(EndA.Minutes <= StartB.Minutes)
          return true;
      return false;
    case 1:
      if(EndA.Hour != StartB.Hour)
        return false;
      if(EndA.Minutes != StartB.Minutes)
        return false;
      return true;
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
  
  for(unsigned j = 1; j < Output.Journeys[ID].Tasks.size(); j++) {
    unsigned ID_A = Output.Journeys[ID].Tasks[j-1];
    unsigned ID_B = Output.Journeys[ID].Tasks[j];
      
    auto EA = IN->Tasks[ID_A]->getEndTime();      
    auto SB = IN->Tasks[ID_B]->getStartTime();      
  
    if(!checkTimes(EA, SB, 1)) {
      Interval = calculateInterval(EA, SB);
      Intervals.push_back(Interval);  
    }
  }
  
  return Intervals;
}

std::vector<unsigned> Tester::getRestTimeIndex(unsigned ID) {
  std::vector<unsigned> Indexs;

  for(unsigned j = 1; j < Output.Journeys[ID].Tasks.size(); j++) {
    unsigned ID_A = Output.Journeys[ID].Tasks[j-1];
    unsigned ID_B = Output.Journeys[ID].Tasks[j];
  
    auto EA = IN->Tasks[ID_A]->getEndTime();      
    auto SB = IN->Tasks[ID_B]->getStartTime();      
    
    if(!checkTimes(EA, SB, 1)) {
      Indexs.push_back(j);
    }
  }

  return Indexs;
}

unsigned Tester::getStretchTime(unsigned ID, unsigned Index) {
  if(Index < Output.Journeys[ID].Tasks.size() && Index > 0) {
    unsigned ID_A = Output.Journeys[ID].Tasks[0];
    unsigned ID_B = Output.Journeys[ID].Tasks[Index-1];
  
    auto EA = IN->Tasks[ID_B]->getEndTime();      
    auto SB = IN->Tasks[ID_A]->getStartTime();      
    
    return calculateInterval(SB, EA);
  }

  return 0;
}

unsigned Tester::getSprendoverTime(unsigned ID) {
  unsigned Last = Output.Journeys[ID].Tasks.size() - 1;
  
  unsigned ID_A = Output.Journeys[ID].Tasks[0];
  unsigned ID_B = Output.Journeys[ID].Tasks[Last];
  
  auto EA = IN->Tasks[ID_B]->getEndTime();      
  auto SB = IN->Tasks[ID_A]->getStartTime();      
 
  return calculateInterval(SB, EA);
}

void Tester::dumpError(unsigned i) {
  std::cout << "error jorney: " << i << std::endl; 
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
  for(unsigned i = 0; i < Output.Journeys.size(); i++) {
    bool isOK = false;
    unsigned ST = 0, RT = 0;
    int OT = 0;
    
    auto RTIPossible = getRestTimeIndex(i);
    auto RTPossible = getRestTime(i);
    unsigned SOT = getSprendoverTime(i);
    
    if(SOT <= Params.StretchTime) {
      ST = SOT;
      isOK = true;
    } else {
      for(unsigned j = 0; j < RTIPossible.size(); j++) {
        ST = 0; RT = 0; OT = 0;
        
        if(RTPossible[j] > Params.RestTime.Max)
          continue;
        
        ST = getStretchTime(i, RTIPossible[j]);
        
        if(RTPossible[j] < Params.RestTime.Min)
          continue;
        
        if(ST > Params.StretchTime)
          continue;
        
        if(SOT > Params.SprendoverTime)
          continue;
        
        RT = RTPossible[j]; 
        OT = SOT - RT - Params.TotalPaidTime; 
        
        if(OT < 0)
          OT = 0;

        isOK = true;
        break;
      }
    }
    if(!isOK)
      //dumpError(i);
      std::cout << "-" << " & " << "-" << " & " << "-" << " & " << "-" << " & " << "-" << " \\\\" << std::endl;
    else
      std::cout << i << " & " << ST << " & " << RT << " & " << OT << " & " << SOT << " \\\\" << std::endl;
  } 
}

void Tester::checkForSequencing() {
  for(unsigned i = 0; i < Output.Journeys.size(); i++) {
    for(unsigned j = 1; j < Output.Journeys[i].Tasks.size(); j++) {
      unsigned ID_A = Output.Journeys[i].Tasks[j-1];
      unsigned ID_B = Output.Journeys[i].Tasks[j];
  
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
    
    }
  } 
}

void Tester::run() {
  checkForSequencing();
  std::cout << "Jorney & StretchTime & RestTime & Overtime & SprendoverTime \\\\ \n";
  checkWorkDay();
}
