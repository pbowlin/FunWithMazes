#include "Timer.h"


std::ostream& operator<<(std::ostream& os, Timer& timer){
    return os << timer.getTotalDuration() << " secs, (" << timer.getStepDuration() << " secs)";
}

Timer::Timer() :
    start_time(std::chrono::system_clock::now()),
    step_time(start_time),
    block_name("code block")
{
}

Timer::Timer(std::string c_block_name, bool print_on_death) :
    start_time(std::chrono::system_clock::now()),
    step_time(start_time),
    block_name(c_block_name),
    death_rattle(print_on_death)
{
}

float Timer::getTotalDuration() const{
    std::chrono::duration<float> duration = std::chrono::system_clock::now() - start_time;
    return duration.count();
}

float Timer::getStepDuration() {
    std::chrono::duration<float> duration = std::chrono::system_clock::now() - step_time;
    step_time = std::chrono::system_clock::now();
    return duration.count();
}

Timer::~Timer(){
    if(death_rattle)
        std::cout << block_name << " execution time: " << *this << std::endl;
}