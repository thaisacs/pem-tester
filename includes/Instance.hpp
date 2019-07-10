#pragma once

#include <memory>
#include <vector>
#include <iostream>
#include <fstream>

namespace pem {
  class Time {
  public:
    unsigned Hour, Minutes;
    Time(unsigned Hour, unsigned Minutes) : Hour(Hour), 
      Minutes(Minutes) {}
    void print();
  };

  class Duration {
  public:
    Time T;
    unsigned Days;
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
    Time getStartTime() { return StartTime; }
    void print();
  };

  class SimpleTask {
    unsigned TaskID; //input line
    Duration EndTime;
  public:
    SimpleTask(Duration EndTime, unsigned TaskID) : EndTime(EndTime), TaskID(TaskID) {}
    unsigned getTaskID() { return TaskID; }
    Duration getEndTime() { return EndTime; }
    void print();
  };

  class Journey {
  public:
    std::vector<std::unique_ptr<SimpleTask>> Tasks; 
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
  public:
    unsigned InstanceSize; 
    std::vector<std::unique_ptr<Task>> Tasks;
    Input(const std::string&); 
    void print();
  };

  class Output : public Instance {
  public:
    std::vector<std::unique_ptr<Journey>> Journeys;
    Output(const std::string&, unsigned); 
    void print();
  };
}
