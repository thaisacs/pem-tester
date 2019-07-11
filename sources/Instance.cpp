#include "Instance.hpp"

using namespace pem;

Time Task::getEndTime() {
  unsigned Minutes = StartTime.Minutes;
  unsigned Hour = StartTime.Hour;
  unsigned Times = 0;

  Minutes += Duration;

  while(Minutes > 59) {
    Times++;
    Minutes -= 60;
  }

  Hour += Times;
 
  if(Hour > 23)
    Hour -= 24;

  Time T(Hour, Minutes);

  return T;
}


std::string FindBusLineID(const std::string &Line) {
  std::string Result = "";
  unsigned i = 1;
  char c = Line[i];

  while(c != 0x22) {
    Result += c;
    c = Line[++i];
  }

  return Result;
}

char FindOrigin(const std::string &Line) {
  unsigned i = 0;
  char c = Line[i];

  // find second field
  while(c != 0x2C) {
    i++;
    c = Line[i];
  }
  i++;
  c = Line[i];

  while(c == 0x20) {
    i++;
    c = Line[i];
  }

  return Line[++i];
}

char FindDestination(const std::string &Line) {
  unsigned i = 0;
  char c = Line[i];

  // find third field
  for(unsigned j = 0; j < 2; j++) {
    while(c != 0x2C) {
      i++;
      c = Line[i];
    }
    i++;
    c = Line[i];
  }

  while(c == 0x20) {
    i++;
    c = Line[i];
  }

  return Line[++i];
}

unsigned FindStartTimeHour(const std::string Line) {
  unsigned i = 0, Number = 0;
  char c = Line[i];
  
  // find third field
  for(unsigned j = 0; j < 3; j++) {
    while(c != 0x2C) {
      i++;
      c = Line[i];
    }
    i++;
    c = Line[i];
  }
  
  while(c == 0x20) {
    i++;
    c = Line[i];
  }
 
  while(c >= 48 && c <= 57) {
    Number = 10*Number + c - 48;
    i++;
    c = Line[i];
  }

  if(Number > 23)
    Number -= 24;

  return Number;
}

unsigned FindStartTimeMinutes(std::string Line) {
  unsigned i = 0, Number = 0;
  char c = Line[i];
  
  // find third field
  for(unsigned j = 0; j < 4; j++) {
    while(c != 0x2C) {
      i++;
      c = Line[i];
    }
    i++;
    c = Line[i];
  }
  
  while(c == 0x20) {
    i++;
    c = Line[i];
  }
 
  while(c >= 48 && c <= 57) {
    Number = 10*Number + c - 48;
    i++;
    c = Line[i];
  }
  
  return Number;
}

unsigned FindDuration(std::string Line) {
  unsigned i = 0, Number = 0;
  char c = Line[i];
  
  // find third field
  for(unsigned j = 0; j < 5; j++) {
    while(c != 0x2C) {
      i++;
      c = Line[i];
    }
    i++;
    c = Line[i];
  }
  
  while(c == 0x20) {
    c = Line[++i];
  }
 
  while(c >= 48 && c <= 57) {
    Number = 10*Number + c - 48;
    c = Line[++i];
  }

  return Number;
}

unsigned FindVehicleID(std::string Line) {
  unsigned i = 0, Number = 0;
  char c = Line[i];
  
  // find third field
  for(unsigned j = 0; j < 6; j++) {
    while(c != 0x2C) {
      i++;
      c = Line[i];
    }
    i++;
    c = Line[i];
  }
  
  while(c == 0x20) {
    i++;
    c = Line[i];
  }
 
  while(c >= 48 && c <= 57) {
    Number = 10*Number + c - 48;
    c = Line[++i];
  }

  return Number;
}

unsigned FindInputLine(std::string Line) {
  unsigned i = 0, Result = 0;
  char c = Line[i];

  while(c != 0x20) {
    Result = Result * 10 + c - 48;
    c = Line[++i];
  }

  return Result;
}

Duration FindEndTime(std::string Line) {
  unsigned i = 0, Number = 0;
  char c = Line[i];
 
  for(unsigned j = 0; j < 6; j++) {
    while(c != 0x20) {
      c = Line[++i];
    }
    while(c == 0x20) {
      c = Line[++i];
    }
  }
  
  unsigned Day = c - 48, Hour = 0, Minute = 0;
  c = Line[++i];
  c = Line[++i];
  Hour = c - 48;
  c = Line[++i];
  if(c != ':') {
    Hour = Hour * 10 + c - 48;
    c = Line[++i];
  }
  c = Line[++i];
  Minute = c - 48;
  c = Line[++i];
  if(c != ' ') {
    Minute = Minute * 10 + c - 48;
  }
 
  Time T(Hour, Minute);
  Duration D(T, Day);
  
  return D;
}

unsigned FindJourneyID(std::string Line) {
  unsigned i = 0, Number = 0;
  char c = Line[i];
 
  // find third field
  for(unsigned j = 0; j < 8; j++) {
    while(c != 0x20) {
      c = Line[++i];
    }
    while(c == 0x20) {
      c = Line[++i];
    }
  }
  
  while(c >= 48 && c <= 57) {
    Number = 10*Number + c - 48;
    c = Line[++i];
  }

  return Number;
}

Input::Input(const std::string &FileName) {
  std::string Line;
  std::ifstream File(FileName);

  if(!File.is_open()) {
    std::cout << "Could not open input file\n";
    exit(1);
  }

  // eat number of tasks
  getline(File, Line);
  
  InstanceSize = std::stoi(Line, nullptr, 10); 
  
  for(unsigned i = 0; i < InstanceSize; i++) {
    getline(File, Line);
    
    Time T(FindStartTimeHour(Line), FindStartTimeMinutes(Line));
    
    auto TA = std::make_unique<Task>(FindBusLineID(Line), FindOrigin(Line),
        FindDestination(Line), FindVehicleID(Line), T, FindDuration(Line));
    
    Tasks.push_back(std::move(TA));
  }
 
  File.close();
}

Output::Output(const std::string &FileName, unsigned InstanceSize) {
  std::string Line;
  std::ifstream File(FileName);

  if(!File.is_open()) {
    std::cout << "Could not open output file\n";
    exit(1);
  }

  for(unsigned i = 0; i < InstanceSize; i++) {
    getline(File, Line);
    unsigned L = FindInputLine(Line);
    Duration D = FindEndTime(Line);
    unsigned ID = FindJourneyID(Line);
    
    if(Journeys.size() <= ID) {
      auto JN = std::make_unique<Journey>();
      Journeys.push_back(std::move(JN));
    }
    
    auto ST = std::make_unique<SimpleTask>(D, L);
    Journeys[ID]->addTask(std::move(ST));
  }
  File.close();
}

//===----------------------------------------------------------------------===//
//// Print 
//===----------------------------------------------------------------------===//

void Time::print() {
  std::cout << Hour << ":" << Minutes << std::endl;;
}

void Duration::print() {
  T.print();
  std::cout << " " << Days << std::endl;
}

void Task::print() {
  std::cout << BusLineID << ", " << Origin << ", " << Destination << ", " <<
  Duration << ", "; 
  StartTime.print();
  std::cout << ", " << VehicleID << std::endl;
}

void SimpleTask::print() {
  std::cout << TaskID << " ";
  EndTime.print();
}

void Journey::print() {
  for(unsigned i = 0; i < Tasks.size(); i++) {
    Tasks[i]->print();
  }
}

void Input::print() {
  for(unsigned i = 0; i < Tasks.size(); i++) {
    Tasks[i]->print();
  }
}

void Output::print() {
  for(unsigned i = 0; i < Journeys.size(); i++) {
    Journeys[i]->print();
  }
}

