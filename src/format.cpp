#include <string>
#include <iomanip>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    std::string time; 
    int hr, min, sec, temp;
    hr = seconds / 3600;
    temp = seconds % 3600;
    min = temp / 60;
    sec = temp % 60;
    std::ostringstream outstream;
    outstream << std::setfill('0') << std::setw(2) << hr << ":" << std::setfill('0') << std::setw(2) << min << ":" << std::setfill('0') << std::setw(2) << sec;
    //time = std::to_string(hr) + ":" + std::to_string(min) + ":" + std::to_string(sec);
    return outstream.str();
}