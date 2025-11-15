// Author: Jake Rieger
// Created: 11/13/25.
//

#pragma once

#define X_ND [[nodiscard]]

#define CAST static_cast
#define CCAST const_cast
#define DCAST dynamic_cast
#define RCAST reinterpret_cast

#define X_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define X_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define X_CLAMP(value, min, max) (X_MIN(X_MAX(value, min), max))

#if defined(_MSC_VER)
    // MSVC
    #define X_DEBUG_BREAK() __debugbreak()
#elif defined(__clang__) || defined(__GNUC__)
    // Clang/GCC
    #if defined(__i386__) || defined(__x86_64__)
        #define X_DEBUG_BREAK() __asm__ volatile("int $0x03")
    #elif defined(__aarch64__)
        #define X_DEBUG_BREAK() __asm__ volatile(".inst 0xd4200000")
    #else
        #include <signal.h>
        #define X_DEBUG_BREAK() raise(SIGTRAP)
    #endif
#else
    #include <signal.h>
    #define X_DEBUG_BREAK() raise(SIGTRAP)
#endif

#define X_ASSERT(condition, message)                                                                                   \
    do {                                                                                                               \
        if (!(condition)) {                                                                                            \
            std::cerr << "Assertion failed: " << #condition << "\n"                                                    \
                      << "Message: " << message << "\n"                                                                \
                      << "File: " << __FILE__ << "\n"                                                                  \
                      << "Line: " << __LINE__ << "\n";                                                                 \
            X_DEBUG_BREAK();                                                                                           \
        }                                                                                                              \
    } while (0)
