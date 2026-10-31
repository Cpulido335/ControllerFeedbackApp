#include "util/clock.h"
#include <windows.h>
#include <stdint.h>
#include "globals.h"

struct CLOCK_STATE g_ClockState = {

};

void clock_init()
{
    QueryPerformanceFrequency(&g_ClockState.cpu_frequency);
    QueryPerformanceCounter(&g_ClockState.last_counter);

}


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


float clock_frame_start() //clock frame start function also returns delta
{
    QueryPerformanceCounter(&g_ClockState.frame_start);

    // --- COMPUTE DELTA FOR FRAME LOGIC (rotation, animation, etc.) ---
    // g_ClockState.last_frame_start = {0};
    if (g_ClockState.last_frame_start.QuadPart == 0)
        g_ClockState.last_frame_start = g_ClockState.frame_start; // initialize on first frame

    int64_t counter_elapsed = g_ClockState.frame_start.QuadPart - g_ClockState.last_frame_start.QuadPart;
    float delta = (float)counter_elapsed / (float)g_ClockState.cpu_frequency.QuadPart; // in seconds

    g_ClockState.last_frame_start = g_ClockState.frame_start; // update for next frame logic

    return delta;
}


void clock_frame_end()
{
    // --- FRAME END ---5
    // LARGE_INTEGER frame_end;
    QueryPerformanceCounter(&g_ClockState.frame_end);

    int64_t frame_ticks = g_ClockState.frame_end.QuadPart - g_ClockState.frame_start.QuadPart;
    float frame_time = (float)frame_ticks / (float)g_ClockState.cpu_frequency.QuadPart;

    
    if (frame_time < TARGET_FRAME_TIME) {  //sleepy time to cap FPS
        DWORD sleep_ms = (DWORD)((TARGET_FRAME_TIME - frame_time) * 1000.0);
        if (sleep_ms > 0)
            Sleep(sleep_ms);

        // measure again after sleep for accurate FPS display
        QueryPerformanceCounter(&g_ClockState.frame_end);
        frame_ticks = g_ClockState.frame_end.QuadPart - g_ClockState.frame_start.QuadPart;
        frame_time = (float)frame_ticks / (float)g_ClockState.cpu_frequency.QuadPart;
    }
}
