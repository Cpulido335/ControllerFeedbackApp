#ifndef CLOCK_H
#define CLOCK_H

#include <windows.h> //TODO does this include a bunch of uncessary bullshit into this translation unit?

struct CLOCK_STATE {
    
    LARGE_INTEGER cpu_frequency;
    LARGE_INTEGER last_counter;
    LARGE_INTEGER frame_start;
    LARGE_INTEGER last_frame_start;

    LARGE_INTEGER frame_end;
};


extern struct CLOCK_STATE g_ClockState;

void clock_init();
double get_time_seconds();
float clock_frame_start();
void clock_frame_end();

#endif 