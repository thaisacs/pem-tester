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

  class Duration {
    Time T;
    unsigned Day;
  public:
    Duration(Time T, unsigned Day) : T(T), Day(Day) {}
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
    Duration EndTime;
  public:
    SimpleTask(Duration EndTime, unsigned TaskID) : EndTime(EndTime), 
    TaskID(TaskID) {}
  };

  class Journey {
    std::vector<SimpleTask> Tasks; 
  public:
    Journey() {}
    void addTask(SimpleTask Task) { 
      Tasks.push_back(Task);
    }
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
    unsigned getInstanceSize() { return InstanceSize; }
  };

  class Output : public Instance {
    Journey *Journeys;
  public:
    Output(const std::string&, unsigned); 
  };
}
