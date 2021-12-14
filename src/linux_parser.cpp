#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  float memutilizaion, memtotal, memfree;
  std::string line, key;
  std::ifstream memstream(kProcDirectory + kMeminfoFilename);
  if(memstream.is_open())
  {
    while(std::getline(memstream, line))
    {
      std::istringstream strstream(line);
      strstream >> key;
      if(key == "MemTotal:") {
        strstream >> memtotal;
      }
      if(key == "MemFree:") {
        strstream >> memfree;
        memutilizaion = (memtotal - memfree) / memtotal;
        return memutilizaion;
      }
    }
  }
  return memutilizaion;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  long uptime;
  std::string line;
  std::ifstream upstream(kProcDirectory + kUptimeFilename);
  if(upstream.is_open()) {
    std::getline(upstream, line);
    std::istringstream strstream(line);
    strstream >> uptime;
    return uptime;
  }
  return uptime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  int totalprocesses;
  std::string line, key;
  std::ifstream totalprstream(kProcDirectory + kStatFilename);
  if(totalprstream.is_open()) {
    while(std::getline(totalprstream, line)) {
      std::istringstream strstream(line);
      strstream >> key;
      if(key == "processes") {
        strstream >> totalprocesses;
        return totalprocesses;
      }
    }
  }
  return totalprocesses;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  std::string line, key;
  int runprocesses;
  std::ifstream runprocesstream(kProcDirectory + kStatFilename);
  if(runprocesstream.is_open()) {
    while(std::getline(runprocesstream, line)) {
      std::istringstream strstream(line);
      strstream >> key;
      if(key == "procs_running") {
        strstream >> runprocesses;
        return runprocesses;
      }
    }
  }
  return runprocesses;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  std::string cmd, line, pidstr;
  pidstr = std::to_string(pid);
  std::ifstream cmdstream(kProcDirectory + pidstr + kCmdlineFilename);
  if(cmdstream.is_open()) {
    while(std::getline(cmdstream, line)) {
      if(line.size() > 40)
      {
        std::string substring;
        line = line.substr(0, 40) + "...";
        //return substring;
      }
    }
  }
  return line;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  std::string line, ram, key, pidstr;
  int ramkb;
  pidstr = std::to_string(pid);
  std::ifstream ramstream(kProcDirectory + pidstr + kStatusFilename);
  if(ramstream.is_open()) {
    while(std::getline(ramstream, line)) {
      std::istringstream strstream(line);
      strstream >> key;
      if(key == "VmSize:") {
        strstream >> ramkb;
        ramkb /= 1000;
        ram = std::to_string(ramkb);
        return ram;
      }
    }
  }
  return ram;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
  std::string uid, line, pidstr, key;
  pidstr = std::to_string(pid);
  std::ifstream uidstream(kProcDirectory + pidstr + kStatusFilename);
  if(uidstream.is_open()) {
    while(std::getline(uidstream, line)) {
      std::istringstream strstream(line);
      strstream >> key;
      if(key == "Uid:") {
        strstream >> uid;
        return uid;
      }
    }
  }
  return uid;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  std::string uname, key, line, pidstr, uid, x;
  pidstr = std::to_string(pid); 
  uid = LinuxParser::Uid(pid);
  std::ifstream userstream(kPasswordPath);
  if(userstream.is_open()) {
    while(std::getline(userstream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream strstream(line);
      strstream >> uname >> x >> key;
      if(key == uid) {
        return uname;
      }
    }
  }
  return uname;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  std::string line, pidstr, key;
  int i = 1; 
  long int uptime;
  pidstr = std::to_string(pid);
  std::ifstream uptimestream(kProcDirectory + pidstr + kStatFilename);
  if(uptimestream.is_open()) {
    std::getline(uptimestream, line);
    std::istringstream strstream(line);
    //strstream >> systime;
    while(i < 21) {
      strstream >> key;
      i++;
    }
    strstream >> uptime;
    //uptime /= sysconf(_SC_CLK_TCK);
    //uptime = systime - uptime;
    //uptime = uptime - systime;
  }
  return (LinuxParser::UpTime() - (uptime / sysconf(_SC_CLK_TCK)));
  //return uptime;
}
