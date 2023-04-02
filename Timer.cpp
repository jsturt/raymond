#include "Timer.h"

Timer::Timer() {
    _start = std::chrono::high_resolution_clock::now();
}

Timer::~Timer() {
    _end = std::chrono::high_resolution_clock::now();
    _duration = _end - _start;
    std::cout<<"Operation complete in "<<_duration.count()<<"s. "<<std::endl;
}
