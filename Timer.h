#pragma once
/*
Simple timer class that will automatically calculate how long a block of code
takes to execute
*/

#include <chrono>
#include <string>
#include <iostream>

class Timer {
    public:
        Timer();
        Timer(std::string c_block_name);
        
        float getDuration() const;

        ~Timer();
        
        friend std::ostream& operator<< (std::ostream& os, const Timer& timer);

    private:
        std::chrono::time_point<std::chrono::system_clock> start_time;
        std::string block_name;
        
};