#ifndef _TIMER_H_INCLUDED_
#define _TIMER_H_INCLUDED_
//#define USE_CHRONO

#if defined _WIN32 && !defined USE_CHRONO
#include <Windows.h>
#else
// When on non-Windows operating system
#ifndef USE_CHRONO
#define USE_CHRONO
#endif // USE_CHRONO
#include <chrono>
#endif // _WIN32 && !defined USE_CHRONO

#include "asserts.h"
#include <cmath>
#include <tuple>
#include <functional>

enum Resolution
{
    NANOSECONDS = 1,
    MICROSECONDS = NANOSECONDS * 1000,
    MILLISECONDS = MICROSECONDS * 1000,
    SECONDS = MILLISECONDS * 1000
};

class Timer
{
public:
    Timer();

    void start();
    double stop(Resolution resolution = SECONDS);
    double getTime(Resolution resolution = SECONDS);

    static double convertResolution(Resolution from, Resolution to, double time);
    
    template<typename ReturnType, typename... ArgsTypes>
    static std::pair<ReturnType, Timer> measureTime(ReturnType(*fn)(ArgsTypes...), ArgsTypes&&... args);

    template<typename ReturnType, typename... ArgsTypes>
    static std::pair<ReturnType, Timer> measureTime(std::function<ReturnType(ArgsTypes...)> fn, ArgsTypes&&... args);
private:
#ifdef USE_CHRONO
    std::chrono::time_point<std::chrono::high_resolution_clock> chStart;
    std::chrono::time_point<std::chrono::high_resolution_clock> chStop;
#else
    LARGE_INTEGER pcStart;
    LARGE_INTEGER pcStop;
    static LARGE_INTEGER frequency;
    static BOOL isFrequencyInitialized;
#endif
};

#endif // _TIMER_H_INCLUDED_

template<typename ReturnType, typename ... ArgsTypes>
inline std::pair<ReturnType, Timer> Timer::measureTime(ReturnType(*fn)(ArgsTypes...), ArgsTypes&&... args)
{
    std::function<ReturnType(ArgsTypes...)> function(fn);

    return measureTime(function, args);
}

template<typename ReturnType, typename ...ArgsTypes>
inline std::pair<ReturnType, Timer> Timer::measureTime(std::function<ReturnType(ArgsTypes...)> fn, ArgsTypes && ...args)
{
    Timer timer;
    timer.start();
    ReturnType retVal = fn(args...);
    timer.stop();

    return std::make_pair(retVal, timer);
}
