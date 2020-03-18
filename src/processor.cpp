#include <string>
#include <vector>

#include "processor.h"
#include "linux_parser.h"

using std::string;
using std::vector;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  vector<string> cpuUtilization = LinuxParser::CpuUtilization();
    
  int user = std::stoi(cpuUtilization[LinuxParser::CPUStates::kUser_]);
  int nice = std::stoi(cpuUtilization[LinuxParser::CPUStates::kNice_]);
  int system = std::stoi(cpuUtilization[LinuxParser::CPUStates::kSystem_]);
  int idle = std::stoi(cpuUtilization[LinuxParser::CPUStates::kIdle_]);
  int iowait = std::stoi(cpuUtilization[LinuxParser::CPUStates::kIOwait_]);
  int irq = std::stoi(cpuUtilization[LinuxParser::CPUStates::kIRQ_]);
  int softirq = std::stoi(cpuUtilization[LinuxParser::CPUStates::kSoftIRQ_]);
  int steal = std::stoi(cpuUtilization[LinuxParser::CPUStates::kSteal_]);

  int currentNonIdleTime = user + nice + system + irq + softirq + steal;
  int currentTotalTime = currentNonIdleTime + idle + iowait;

  float utilization = (float)(currentNonIdleTime - previoudNonIdleTime_) / (float)(currentTotalTime - previousTotalTime_);

  previousTotalTime_ = currentTotalTime;
  previoudNonIdleTime_ = currentNonIdleTime;

  return utilization;
  
}