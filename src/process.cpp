#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const { 
    float cputilize = 0;
    std::string line, key;
    unsigned long long int uptime, utime, stime, cutime, cstime;
    int j = 1;
    std::ifstream cpustream("/proc/" + std::to_string(pid_) + "/stat");
    if(cpustream.is_open()) {
        std::getline(cpustream, line);
        std::istringstream strstream(line);
        strstream >> uptime;
        while(j < 13) {
            strstream >> key;
            j++;
        }
        strstream >> utime >> stime >> cutime >> cstime;
        unsigned long long int total_time = utime + stime + cutime + cstime;
        //long seconds = uptime - (LinuxParser::UpTime(pid_));
        cputilize = (1.0 * (total_time/sysconf(_SC_CLK_TCK)) / LinuxParser::UpTime(pid_));
    }
    return cputilize;
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(Process::Pid()); }

// TODO: Return this process's memory utilization
string Process::Ram() const { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Process::Pid()); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(Process::Pid()); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
    //return (this->CpuUtilization() > a.CpuUtilization()) ; //sorting based on CPU utilization of each process
    return (std::stol(this->Ram()) > std::stol(a.Ram())); //sorting based on memory utilization of each process
}
