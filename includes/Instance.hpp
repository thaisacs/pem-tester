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
    void print();
  };

  class Duration {
    Time T;
    unsigned Days;
  public:
    Duration(Time T, unsigned Days) : T(T), Days(Days) {}
    void print();
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
    void print();
  };

  class SimpleTask {
    unsigned TaskID; //input line
    Duration EndTime;
  public:
    SimpleTask(Duration EndTime, unsigned TaskID) : EndTime(EndTime), TaskID(TaskID) {}
    void print();
  };

  class Journey {
    std::vector<std::unique_ptr<SimpleTask>> Tasks; 
  public:
    Journey() {}
    void addTask(std::unique_ptr<SimpleTask> T) { 
      Tasks.push_back(std::move(T));
    }
    void print();
  };

  class Instance {
  public:
    Instance() {}
  };

  class Input : public Instance {
    unsigned InstanceSize; 
    std::vector<std::unique_ptr<Task>> Tasks;
  public:
    Input(const std::string&); 
    unsigned getInstanceSize() { return InstanceSize; }
    void print();
  };

  class Output : public Instance {
    std::vector<std::unique_ptr<Journey>> Journeys;
  public:
    Output(const std::string&, unsigned); 
    void print();
  };
}
