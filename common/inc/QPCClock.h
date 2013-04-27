#pragma once
#include <boost/chrono.hpp>

namespace core
{
    // Self-made Windows QueryPerformanceCounter based C++11 API compatible clock
    //  (c) http://stackoverflow.com/users/1749706/mateusz-pusz, 2012
    struct QPCClock
    {
        typedef boost::chrono::nanoseconds duration; // nanoseconds resolution
        typedef duration::rep rep;
        typedef duration::period period;
        typedef boost::chrono::time_point<QPCClock, duration> time_point;
        static const bool is_steady = true;

        // Return current time
        static time_point now();
    };
}
