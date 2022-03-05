///////////////////////////////////////////////////////////////////////////////
//
// Author:           Aodhan Shaw
// Email:            aodhanshaw@gmail.com
// Title:            Timer Class
// Semester:         Spring 2022
// Date:             16 Feb 2022
//
// Description:
//       This is a simple class that wraps the "chrono" data type and allows a user
//       to time code snippets at the granularity of seconds or milliseconds.
//
// Usage:
//      #include "timer.hpp"
//
//
//      Timer T;
//      T.Start();
//
//      // do stuff to be timed here
//
//      T.End();
//
//      double s = T.Seconds();
//      long m = T.MilliSeconds();
//
//      cout <<s << " seconds" <<endl;
//      cout <<m << " milli" <<endl;
//
/////////////////////////////////////////////////////////////////////////////////
#include <chrono>
#include <thread>
#include <time.h>

class Timer {
private:
    int seed;
    int micro;
    std::chrono::time_point<std::chrono::steady_clock> start;
    std::chrono::time_point<std::chrono::steady_clock> end;
    // Fsec seconds;
    // Msec milliseconds;

public:
    Timer() {
    }

    void Start() {
        //start = Time::now();
        start = chrono::steady_clock::now();
    }

    void End() {
        //end = Time::now();
        end = chrono::steady_clock::now();
    }

    auto NanoSeconds() {
        return chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    }

    auto Seconds() {
        return chrono::duration_cast<chrono::seconds>(end - start).count();
    }

    auto MilliSeconds() {
        return chrono::duration_cast<chrono::milliseconds>(end - start).count();
    }
};

