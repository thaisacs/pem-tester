#pragma once

#include <memory>
#include <vector>
#include <iostream>
#include <fstream>

namespace pem {
  class Time {
    unsigned Hour, Minutes;
  public:
    Time(unsigned Hour, unsigned Minutes) : Hour(Hour), 
    Minutes(Minutes) {}
  };

  class Task {
    std::string BusLineID;
    char Origin, Destination;
    unsigned VehicleID, Duration;
    Time StartTime;
  public:
    Task(const std::string &BusLineID, char Origin, char Destination,
        unsigned VehicleID, Time StartTime, unsigned Duration) : BusLineID(BusLineID), 
    Origin(Origin), Destination(Destination), VehicleID(VehicleID), StartTime(StartTime), 
    Duration(Duration) {}
    std::string getBusLineID() { return BusLineID; }
    char getOrigin() { return Origin; }
    char getDestination() { return Destination; }
    unsigned getVehicleID() { return VehicleID; }
    void print() {
      std::cout << BusLineID << ", " << Origin << ", " << Destination << ", " <<
        Duration << ", " << VehicleID << std::endl;
    };
  };

  class SimpleTask {
    unsigned TaskID; //input line
    Time EndTime;
  public:
    SimpleTask() {}
  };

  class Journey {
    std::vector<SimpleTask> Tasks; 
    unsigned JourneyID;
  public:
    Journey() {}
  };

  class Instance {
  public:
    Instance() {}
  };

  class Input : public Instance {
    unsigned InstanceSize; 
    std::vector<Task> Tasks;
  public:
    Input(const std::string&); 
  };

  class Output : public Instance {
    std::vector<Journey> Journeys;
  public:
    Output(const std::string&); 
  };
}
