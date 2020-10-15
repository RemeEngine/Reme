#pragma once

#include <Reme/Core/Alias.h>
#include <Reme/Core/Logger.h>

// Platform detection using predefined macros
#ifdef _WIN32
/* Windows x64/x86 */
#    ifdef _WIN64
/* Windows x64  */
#        define REME_PLATFORM_WINDOWS
#    else
/* Windows x86 */
#        error "x86 Builds are not supported!"
#    endif
#elif defined(__APPLE__) || defined(__MACH__)
#    include <TargetConditionals.h>
/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
#    if TARGET_IPHONE_SIMULATOR == 1
#        error "IOS simulator is not supported!"
#    elif TARGET_OS_IPHONE == 1
#        define REME_PLATFORM_IOS
#        error "IOS is not supported!"
#    elif TARGET_OS_MAC == 1
#        define REME_PLATFORM_MACOS
#    else
#        error "Unknown Apple platform!"
#    endif
/* We also have to check __ANDROID__ before __linux__
 * since android is based on the linux kernel
 * it has __linux__ defined */
#elif defined(__ANDROID__)
#    define REME_PLATFORM_ANDROID
#    error "Android is not supported!"
#elif defined(__linux__)
#    define REME_PLATFORM_LINUX
#else
/* Unknown compiler/platform */
#    error "Unknown platform!"
#endif // End of platform detection

#ifndef REME_DISABLE_ASSERT
#    ifdef _MSC_VER
#        define DEBUG_BREAK __debugbreak()
#    else
#        include <signal.h>
#        define DEBUG_BREAK raise(SIGINT)
#    endif

#    define CORE_ASSERT(x, ...)                                   \
        if (!(x)) {                                               \
            CORE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
            DEBUG_BREAK;                                          \
        }
#    define ASSERT(x, ...)                                   \
        if (!(x)) {                                          \
            LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
            DEBUG_BREAK;                                     \
        }
#else
#    define DEBUG_BREAK
#    define CORE_ASSERT(x, ...) x
#    define ASSERT(x, ...) x
#endif
