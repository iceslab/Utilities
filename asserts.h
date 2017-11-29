#ifndef _ASSERTS_H_INCLUDED_
#define _ASSERTS_H_INCLUDED_

#include <cstdio>
#include <climits>
#include <cassert>

#ifdef _WIN32
#define NOMINMAX // Disable macros for min and max
#include <Windows.h>
#endif // _WIN32

#define QUOTE(x) #x

#define VERBOSITY_LEVEL_NONE 0
#define VERBOSITY_LEVEL_ERROR 1
#define VERBOSITY_LEVEL_WARNING 2
#define VERBOSITY_LEVEL_INFO 3
#define VERBOSITY_LEVEL_DEBUG 4

#ifndef VERBOSITY_LEVEL
#pragma message("Warning: VERBOSITY_LEVEL not defined. Defaulting to VERBOSITY_LEVEL_WARNING")
#pragma message("Warning: VERBOSITY_LEVELS={0, 1, 2, 3, 4} -> NONE, ERROR, WARNING, INFO, DEBUG")
#define VERBOSITY_LEVEL VERBOSITY_LEVEL_WARNING
#endif

inline void breakWhenDebuggerPresent()
{
#ifdef _WIN32
    if (IsDebuggerPresent())
    {
        DebugBreak();
    }
#endif // _WIN32
}

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P) (P)
#endif //!UNREFERENCED_PARAMETER

#define VA_ARGS(...) , ##__VA_ARGS__

#if _DEBUG || !NDEBUG
#define PRINT_SEPARATOR() \
do \
{ \
        fprintf(stderr, "===========================================================\n"); \
} while (false);

#define DEBUG_PRINTLN_VERBOSE(format, ...) \
do{ \
    fprintf(stderr, format, VA_ARGS(__VA_ARGS__)); \
    fprintf(stderr, ", file %s, line %d\n", __FILE__, __LINE__); \
} while (false);

#define DEBUG_PRINT_VERBOSE(format, ...) \
do{ \
    fprintf(stderr, format, VA_ARGS(__VA_ARGS__)); \
    fprintf(stderr, ", file %s, line %d", __FILE__, __LINE__); \
} while (false);

#define DEBUG_PRINTLN(format, ...) \
do{ \
    fprintf(stderr, format"\n", VA_ARGS(__VA_ARGS__)); \
} while (false);

#define DEBUG_PRINT(format, ...) \
do{ \
    fprintf(stderr, format, VA_ARGS(__VA_ARGS__)); \
} while (false);

#define DEBUG_CALL(expr) \
do{ \
    expr; \
} while (false);

#define ASSERT(expr) \
do \
{ \
    if ((expr) == false) \
    { \
        fprintf(stderr, "Assertion failed: " QUOTE(expr) ", file %s, line %d\n", __FILE__, __LINE__); \
        fflush(stderr); \
        fflush(stdout); \
        breakWhenDebuggerPresent(); \
        abort(); \
    } \
} while (false);

#define ASSERT_VERBOSE(expr, format, ...) \
do{ \
    if((expr) == false) \
    { \
        fprintf(stderr, "Assertion failed: " QUOTE(expr) ", "); \
        fprintf(stderr, format, VA_ARGS(__VA_ARGS__)); \
        fprintf(stderr, ", file %s, line %d\n", __FILE__, __LINE__); \
        fflush(stderr); \
        fflush(stdout); \
        breakWhenDebuggerPresent(); \
        abort(); \
    } \
} while (false);

#define FATAL_ERROR_VERBOSE(format, ...) \
do \
{ \
    fprintf(stderr, "Fatal error occured: "); \
    fprintf(stderr, format, VA_ARGS(__VA_ARGS__)); \
    fprintf(stderr, ", file %s, line %d\n", __FILE__, __LINE__); \
} while (false);

#define FATAL_ERROR() \
do \
{ \
    fprintf(stderr, "Fatal error occured. File %s, line %d\n", __FILE__, __LINE__); \
} while (false);

#ifdef VERBOSITY_LEVEL
#if VERBOSITY_LEVEL >= VERBOSITY_LEVEL_WARNING
#define DEBUG_PRINTLN_VERBOSE_WARNING(format, ...) DEBUG_PRINTLN_VERBOSE(format, VA_ARGS(__VA_ARGS__))
#define DEBUG_PRINT_VERBOSE_WARNING(format, ...) DEBUG_PRINT_VERBOSE(format, VA_ARGS(__VA_ARGS__))
#else
#define DEBUG_PRINTLN_VERBOSE_WARNING(format, ...)
#define DEBUG_PRINT_VERBOSE_WARNING(format, ...)
#endif

#if VERBOSITY_LEVEL >= VERBOSITY_LEVEL_INFO
#define DEBUG_PRINTLN_VERBOSE_INFO(format, ...) DEBUG_PRINTLN_VERBOSE(format, VA_ARGS(__VA_ARGS__))
#define DEBUG_PRINT_VERBOSE_INFO(format, ...) DEBUG_PRINT_VERBOSE(format, VA_ARGS(__VA_ARGS__))
#else
#define DEBUG_PRINTLN_VERBOSE_INFO(format, ...)
#define DEBUG_PRINT_VERBOSE_INFO(format, ...)
#endif

#if VERBOSITY_LEVEL >= VERBOSITY_LEVEL_DEBUG
#define DEBUG_PRINTLN_VERBOSE_DEBUG(format, ...) DEBUG_PRINTLN_VERBOSE(format, VA_ARGS(__VA_ARGS__))
#define DEBUG_PRINT_VERBOSE_DEBUG(format, ...) DEBUG_PRINT_VERBOSE(format, VA_ARGS(__VA_ARGS__))
#else
#define DEBUG_PRINTLN_VERBOSE_DEBUG(format, ...)
#define DEBUG_PRINT_VERBOSE_DEBUG(format, ...)
#endif
#endif

#else
#define PRINT_SEPARATOR()

#define DEBUG_PRINTLN_VERBOSE(format, ...)
#define DEBUG_PRINT_VERBOSE(format, ...)

#define DEBUG_PRINTLN(format, ...)
#define DEBUG_PRINT(format, ...)

#define DEBUG_CALL(expr)
#define ASSERT(expr)
#define ASSERT_VERBOSE(expr, format, ...)

#define FATAL_ERROR_VERBOSE(format, ...)
#define FATAL_ERROR()

#define DEBUG_PRINTLN_VERBOSE_INFO(format, ...)
#define DEBUG_PRINT_VERBOSE_INFO(format, ...)

#define DEBUG_PRINTLN_VERBOSE_WARNING(format, ...)
#define DEBUG_PRINT_VERBOSE_WARNING(format, ...)

#define DEBUG_PRINTLN_VERBOSE_DEBUG(format, ...)
#define DEBUG_PRINT_VERBOSE_DEBUG(format, ...)
#endif // _DEBUG || !NDEBUG
#endif // !_ASSERTS_H_INCLUDED_
