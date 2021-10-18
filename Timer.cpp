#include "Timer.h"


std::ostream& operator<<(std::ostream& os, const Timer& timer){
    return os << timer.getDuration() << "s";
}

Timer::Timer() :
    block_name("code block")
{
    start_time =  std::chrono::system_clock::now();
}

Timer::Timer(std::string c_block_name) :
    block_name(c_block_name)
{
    start_time =  std::chrono::system_clock::now();
}

float Timer::getDuration() const{
    std::chrono::duration<float> duration = std::chrono::system_clock::now() - start_time;
    return duration.count();
}

Timer::~Timer(){
    std::cout << block_name << " execution time: " << getDuration() << std::endl;
}