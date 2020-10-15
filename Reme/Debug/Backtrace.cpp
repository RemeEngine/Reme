#include <Reme/Debug/Demangle.h>

#include <Reme/Core/Core.h>
#include <cxxabi.h>
#include <dlfcn.h>
#include <execinfo.h>

namespace Reme {

constexpr const size_t BACKTRACE_SIZE = 21;

void print_backtrace(int signal)
{
    void* callstack[BACKTRACE_SIZE];

    size_t size;
    size = backtrace(callstack, BACKTRACE_SIZE);
    char** symbols = backtrace_symbols(callstack, BACKTRACE_SIZE);

    CORE_LOG_CRITICAL("Crash! {} ", strsignal(signal));

    // Skip the first stack frame (this function)
    for (size_t i = 1; i < size && symbols != nullptr; ++i) {
        Dl_info info;
        if (dladdr(callstack[i], &info)) {
            CORE_LOG_WARN("[callstack ({:14})]: ({:2d}) {} + {}", callstack[i], i, demangle(info.dli_sname), (char*)callstack[i] - (char*)info.dli_saddr);
        } else {
            CORE_LOG_WARN("[callstack ({:14})]: ({:2d}) {}", i, callstack[i], symbols[i]);
        }
    }

    std::free(symbols);
    Log::core_logger()->flush();
    std::exit(1);
}

} // namespace Reme
