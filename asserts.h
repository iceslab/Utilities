#ifndef _ASSERTS_H_INCLUDED_
#define _ASSERTS_H_INCLUDED_

#include <cstdio>
#include <climits>
#include <cassert>

#ifdef _WIN32
#define NOMINMAX // Disable macros for min and max
#include <Windows.h>
#else
#include <unistd.h>
#define TCHAR char
#endif // _WIN32

// Windows
#ifndef DESCRIPTIVE_FUNCNAME
#ifdef __FUNCSIG__
#define DESCRIPTIVE_FUNCNAME __FUNCSIG__
#endif // __FUNCSIG__
#endif // !DESCRIPTIVE_FUNCNAME

// *NIX
#ifndef DESCRIPTIVE_FUNCNAME
#ifdef __PRETTY_FUNCTION__
#define DESCRIPTIVE_FUNCNAME __PRETTY_FUNCTION__
#endif // __PRETTY_FUNCTION__
#endif // !DESCRIPTIVE_FUNCNAME

// Other
#ifndef DESCRIPTIVE_FUNCNAME
#ifdef __FUNCTION__
#define DESCRIPTIVE_FUNCNAME __FUNCTION__
#endif // __FUNCTION__
#endif // !DESCRIPTIVE_FUNCNAME

// No define case
#ifndef DESCRIPTIVE_FUNCNAME
#define DESCRIPTIVE_FUNCNAME "NO_FUNCTION_NAME"
#endif // !DESCRIPTIVE_FUNCNAME

#define QUOTE(x) #x

#define VERBOSITY_LEVEL_NONE_VALUE 0
#define VERBOSITY_LEVEL_ERROR_VALUE 1
#define VERBOSITY_LEVEL_WARNING_VALUE 2
#define VERBOSITY_LEVEL_INFO_VALUE 3
#define VERBOSITY_LEVEL_DEBUG_VALUE 4

#ifdef VERBOSITY_LEVEL_NONE
#define VERBOSITY_LEVEL VERBOSITY_LEVEL_NONE_VALUE
#endif  // VERBOSITY_LEVEL_NONE

#ifdef VERBOSITY_LEVEL_ERROR
#define VERBOSITY_LEVEL VERBOSITY_LEVEL_ERROR_VALUE
#endif  // VERBOSITY_LEVEL_ERROR

#ifdef VERBOSITY_LEVEL_WARNING
#define VERBOSITY_LEVEL VERBOSITY_LEVEL_WARNING_VALUE
#endif  // VERBOSITY_LEVEL_WARNING

#ifdef VERBOSITY_LEVEL_INFO
#define VERBOSITY_LEVEL VERBOSITY_LEVEL_INFO_VALUE
#endif  // VERBOSITY_LEVEL_INFO

#ifdef VERBOSITY_LEVEL_DEBUG
#define VERBOSITY_LEVEL VERBOSITY_LEVEL_DEBUG_VALUE
#endif  // VERBOSITY_LEVEL_DEBUG

#ifndef VERBOSITY_LEVEL
#pragma message("Warning: VERBOSITY_LEVEL not defined. Defaulting to VERBOSITY_LEVEL_WARNING")
#pragma message("Warning: VERBOSITY_LEVELS={0, 1, 2, 3, 4} -> NONE, ERROR, WARNING, INFO, DEBUG")
#pragma message("Warning: Example: #define VERBOSITY_LEVEL_WARNING")
#define VERBOSITY_LEVEL VERBOSITY_LEVEL_WARNING_VALUE
#endif // !VERBOSITY_LEVEL

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

#if _DEBUG || !NDEBUG
#define PRINT_SEPARATOR() \
do \
{ \
        fprintf(stderr, "===========================================================\n"); \
} while (false);

#define DEBUG_PRINTLN_VERBOSE(...) \
do{ \
    fprintf(stderr, __VA_ARGS__); \
    fprintf(stderr, ", file %s, line %d\n", __FILE__, __LINE__); \
} while (false);

#define DEBUG_PRINT_VERBOSE(...) \
do{ \
    fprintf(stderr, __VA_ARGS__; \
    fprintf(stderr, ", file %s, line %d", __FILE__, __LINE__); \
} while (false);

#define DEBUG_PRINTLN(...) \
do{ \
    fprintf(stderr, __VA_ARGS__); \
    fprintf(stderr, "\n"); \
} while (false);

#define DEBUG_PRINT(...) \
do{ \
    fprintf(stderr, __VA_ARGS__); \
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

#define ASSERT_VERBOSE(expr, ...) \
do{ \
    if((expr) == false) \
    { \
        fprintf(stderr, "Assertion failed: " QUOTE(expr) ", "); \
        fprintf(stderr, __VA_ARGS__); \
        fprintf(stderr, ", file %s, line %d\n", __FILE__, __LINE__); \
        fflush(stderr); \
        fflush(stdout); \
        breakWhenDebuggerPresent(); \
        abort(); \
    } \
} while (false);

#define FATAL_ERROR_VERBOSE(...) \
do \
{ \
    fprintf(stderr, "Fatal error occured: "); \
    fprintf(stderr, __VA_ARGS__); \
    fprintf(stderr, ", file %s, line %d\n", __FILE__, __LINE__); \
} while (false);

#define FATAL_ERROR() \
do \
{ \
    fprintf(stderr, "Fatal error occured. File %s, line %d\n", __FILE__, __LINE__); \
} while (false);

#ifdef VERBOSITY_LEVEL
#if VERBOSITY_LEVEL >= VERBOSITY_LEVEL_WARNING_VALUE
#define DEBUG_PRINTLN_VERBOSE_WARNING(...) DEBUG_PRINTLN_VERBOSE(__VA_ARGS__)
#define DEBUG_PRINT_VERBOSE_WARNING(...) DEBUG_PRINT_VERBOSE(__VA_ARGS__)
#else
#define DEBUG_PRINTLN_VERBOSE_WARNING(...)
#define DEBUG_PRINT_VERBOSE_WARNING(...)
#endif

#if VERBOSITY_LEVEL >= VERBOSITY_LEVEL_INFO_VALUE
#define DEBUG_PRINTLN_VERBOSE_INFO(...) DEBUG_PRINTLN_VERBOSE(__VA_ARGS__)
#define DEBUG_PRINT_VERBOSE_INFO(...) DEBUG_PRINT_VERBOSE(__VA_ARGS__)
#else
#define DEBUG_PRINTLN_VERBOSE_INFO(...)
#define DEBUG_PRINT_VERBOSE_INFO(...)
#endif

#if VERBOSITY_LEVEL >= VERBOSITY_LEVEL_DEBUG_VALUE
#define DEBUG_PRINTLN_VERBOSE_DEBUG(...) DEBUG_PRINTLN_VERBOSE(__VA_ARGS__)
#define DEBUG_PRINT_VERBOSE_DEBUG(...) DEBUG_PRINT_VERBOSE(__VA_ARGS__)
#else
#define DEBUG_PRINTLN_VERBOSE_DEBUG(...)
#define DEBUG_PRINT_VERBOSE_DEBUG(...)
#endif
#endif

#else
#define PRINT_SEPARATOR()

#define DEBUG_PRINTLN_VERBOSE(...)
#define DEBUG_PRINT_VERBOSE(...)

#define DEBUG_PRINTLN(...)
#define DEBUG_PRINT(...)

#define DEBUG_CALL(expr)
#define ASSERT(expr)
#define ASSERT_VERBOSE(expr, ...)

#define FATAL_ERROR_VERBOSE(...)
#define FATAL_ERROR()

#define DEBUG_PRINTLN_VERBOSE_INFO(...)
#define DEBUG_PRINT_VERBOSE_INFO(...)

#define DEBUG_PRINTLN_VERBOSE_WARNING(...)
#define DEBUG_PRINT_VERBOSE_WARNING(...)

#define DEBUG_PRINTLN_VERBOSE_DEBUG(...)
#define DEBUG_PRINT_VERBOSE_DEBUG(...)
#endif // _DEBUG || !NDEBUG
#endif // !_ASSERTS_H_INCLUDED_
