#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : pid_{pid} {
    command_ = LinuxParser::Command(pid_);
    user_ = LinuxParser::User(pid_);
    Ram();
    UpTime();
    CpuUtilization();
}

// TODO: Return this process's ID
int Process::Pid() { 
    return pid_;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    long totalTimeInJiffies = LinuxParser::UpTime(pid_);
    long activeTimeInJiffies = LinuxParser::ActiveJiffies(pid_);
    cpuUtilization_ = (float)activeTimeInJiffies / (float)totalTimeInJiffies;
    return cpuUtilization_; 
}

// TODO: Return the command that generated this process
string Process::Command() { 
    return command_; 
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
    string ramInKB = LinuxParser::Ram(pid_);
    ramInMB_ = std::stoi(ramInKB) / 1000;
    return std::to_string(ramInMB_);
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
    return user_;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    return LinuxParser::UpTime(pid_) / sysconf(_SC_CLK_TCK); 
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
    return this->cpuUtilization_ < a.cpuUtilization_;
}