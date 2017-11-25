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

// Forward declaration
template <typename ReturnType>
struct MeasurementResult;

class Timer
{
public:
    Timer();

    void start();
    double stop(Resolution resolution = SECONDS);
    double getTime(Resolution resolution = SECONDS);

    static double convertResolution(Resolution from, Resolution to, double time);
    
    template<typename ReturnType, typename... ArgsTypes>
    static MeasurementResult<ReturnType> measureTime(ReturnType(*fn)(ArgsTypes...), ArgsTypes&&... args);

    template<typename ReturnType, typename... ArgsTypes>
    static MeasurementResult<ReturnType> measureTime(std::function<ReturnType(ArgsTypes...)> fn, ArgsTypes&&... args);

    template<typename... ArgsTypes>
    static Timer measureTime(void(*fn)(ArgsTypes...), ArgsTypes&&... args);

    template<typename... ArgsTypes>
    static Timer measureTime(std::function<void(ArgsTypes...)> fn, ArgsTypes && ...args);
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

template <typename ReturnType>
struct MeasurementResult : public Timer
{
    ReturnType functionResult;
};


template<typename ReturnType, typename ... ArgsTypes>
inline MeasurementResult<ReturnType> Timer::measureTime(ReturnType(*fn)(ArgsTypes...), ArgsTypes&&... args)
{
    MeasurementResult<ReturnType> retVal;
    retVal.start();
    retVal.functionResult = fn(args...);
    retVal.stop();

    return retVal;
}

template<typename ReturnType, typename ...ArgsTypes>
inline MeasurementResult<ReturnType> Timer::measureTime(std::function<ReturnType(ArgsTypes...)> fn, ArgsTypes && ...args)
{
    MeasurementResult<ReturnType> retVal;
    retVal.start();
    retVal.functionResult = fn(args...);
    retVal.stop();

    return retVal;
}

template<typename ...ArgsTypes>
inline Timer Timer::measureTime(void(*fn)(ArgsTypes...), ArgsTypes && ...args)
{
    Timer timer;
    timer.start();
    fn(args...);
    timer.stop();

    return timer;
}

template<typename ...ArgsTypes>
inline Timer Timer::measureTime(std::function<void(ArgsTypes...)> fn, ArgsTypes && ...args)
{
    Timer timer;
    timer.start();
    fn(args...);
    timer.stop();

    return timer;
}

#endif // _TIMER_H_INCLUDED_