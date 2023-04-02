#ifndef RAYTRACER_TIMER_H
#define RAYTRACER_TIMER_H

#include <chrono>
#include <iostream>

class Timer {
public:
    Timer();
    ~Timer();
private:
    std::chrono::high_resolution_clock::time_point _start,_end;
    std::chrono::duration<float> _duration;
};


#endif //RAYTRACER_TIMER_H
