#include <Reme/Debug/ExceptionHandler.h>

#include <Reme/Core/Alias.h>
#include <Reme/Debug/Demangle.h>
#include <csignal>
#include <cstdlib>

#ifndef _MSC_VER
#include <cxxabi.h>
#include <dlfcn.h>
#include <execinfo.h>
#endif

namespace Reme {

MAYBE_UNUSED constexpr const size_t BACKTRACE_SIZE = 21;

void print_backtrace(int signal)
{   
#ifndef _MSC_VER
    void* callstack[BACKTRACE_SIZE];

    size_t size = backtrace(callstack, BACKTRACE_SIZE);
    char** symbols = backtrace_symbols(callstack, BACKTRACE_SIZE);

    printf("Crash! %s\n", strsignal(signal));

    Dl_info info;
    for (size_t i = 1; i < size && symbols != nullptr; ++i) {
        if (dladdr(callstack[i], &info)) {
            printf("[callstack (%p)]: (%lu) %s + %ld\n", callstack[i], i, demangle(info.dli_sname).c_str(), (char*)callstack[i] - (char*)info.dli_saddr);
        } else {
            printf("[callstack (%p)]: (%lu) %s\n", callstack[i], i, symbols[i]);
        }
    }

    std::free(symbols);
#else
#endif
    std::_Exit(signal);
}

void ExceptionHandler::initialize()
{
    std::signal(SIGABRT, print_backtrace);
    std::signal(SIGFPE, print_backtrace);
    std::signal(SIGILL, print_backtrace);
    std::signal(SIGINT, print_backtrace);
    std::signal(SIGSEGV, print_backtrace);
    std::signal(SIGTERM, print_backtrace);
//    std::signal(SIGTRAP, print_backtrace);
}

} // namespace Reme
