#include "Instance.hpp"

using namespace pem;

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
    i++;
    c = Line[i];
  }

  return Number;
}

Input::Input(const std::string &FileName) {
  std::string Line;
  std::ifstream File(FileName);

  if(!File.is_open())
    exit(1);

  /// eat number of tasks
  getline(File, Line);

  InstanceSize = std::stoi(Line, nullptr, 10); 
  
  for(unsigned i = 0; i < InstanceSize; i++) {
    getline(File, Line);
    
    Time T(FindStartTimeHour(Line), FindStartTimeMinutes(Line));

    Task TA(FindBusLineID(Line), FindOrigin(Line), 
        FindDestination(Line), FindVehicleID(Line), T, FindDuration(Line));
    
    Tasks.push_back(TA);
  }
 
  File.close();
}

Output::Output(const std::string &FileName) {
  std::string Line;
  std::ifstream File(FileName);

  if(!File.is_open())
    exit(1);

  for(unsigned i = 0; i < InstanceSize; i++) {
  }
 
  File.close();
}
