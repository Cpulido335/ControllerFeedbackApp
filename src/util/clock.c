#include "util/clock.h"
#include <windows.h>

double get_time_seconds() //TODO this is cheeks, we could just have a global time variable that gets updated once per frame call and everything 
//that requires time could just reference that
{
    static LARGE_INTEGER freq = {0};
    LARGE_INTEGER counter;

    if (freq.QuadPart == 0)
        QueryPerformanceFrequency(&freq);

    QueryPerformanceCounter(&counter);
    return (double)counter.QuadPart / (double)freq.QuadPart;
}