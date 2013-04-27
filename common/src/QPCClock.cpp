#include "QPCClock.h"
#include <windows.h>

using namespace core;

// static
QPCClock::time_point QPCClock::now()
{
    static LARGE_INTEGER frequency = { 0 };
    if (frequency.QuadPart == 0)
    {
        ::QueryPerformanceFrequency(&frequency);
    }

    LARGE_INTEGER counter;
    ::QueryPerformanceCounter(&counter);

    return time_point(duration(static_cast<rep>((double)counter.QuadPart / frequency.QuadPart * period::den / period::num)));
}
