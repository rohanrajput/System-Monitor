#include "processor.h"
#include <sstream>
#include "linux_parser.h"
#include <unistd.h>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    float cputilize;
    int idle, nonidle, total, nextidle, nextnonidle, nexttotal;
    std::string line, key;
    std::ifstream cputilization("/proc/stat");
    if(cputilization.is_open()) {
        std::getline(cputilization, line);
        std::istringstream strstream(line);
        strstream >> key >> kuser_ >> knice_ >> ksystem_ >> kidle_ >> kiowait_ >> kirq_ >> ksoftirq_ >> ksteal_ >> kguest_ >> kguestnice_;
        idle = kidle_ + kiowait_;
        nonidle = kuser_ + knice_ + ksystem_ + kirq_ + ksoftirq_ + ksteal_;
        total = idle + nonidle;
        //cputilize = (total - idle) / (float)total;
    }
    //calculating CPU utilization at period of 1 sec
    sleep(1);
    std::ifstream cputilization2("/proc/stat");
    if(cputilization2.is_open()) {
        std::getline(cputilization2, line);
        std::istringstream strstream(line);
        strstream >> key >> kuser_ >> knice_ >> ksystem_ >> kidle_ >> kiowait_ >> kirq_ >> ksoftirq_ >> ksteal_ >> kguest_ >> kguestnice_;
        nextidle = kidle_ + kiowait_;
        nextnonidle = kuser_ + knice_ + ksystem_ + kirq_ + ksoftirq_ + ksteal_;
        nexttotal = nextidle + nextnonidle;
    }
    cputilize = (nextnonidle - nonidle) / (float)(nexttotal - total);
    return cputilize;
}