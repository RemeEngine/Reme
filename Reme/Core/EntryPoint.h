#pragma once

#include <Reme/Core/Application.h>
#include <Reme/Core/Core.h>
#include <Reme/Debug/Backtrace.h>
#include <csignal>

#define REME_APP_ENTRY(AppClass)                              \
    int main(MAYBE_UNUSED int argc, MAYBE_UNUSED char** argv) \
    {                                                         \
        ::Reme::Log::initialize(#AppClass);                   \
        std::signal(SIGABRT, ::Reme::print_backtrace);        \
        std::signal(SIGFPE, ::Reme::print_backtrace);         \
        std::signal(SIGILL, ::Reme::print_backtrace);         \
        std::signal(SIGINT, ::Reme::print_backtrace);         \
        std::signal(SIGSEGV, ::Reme::print_backtrace);        \
        std::signal(SIGTERM, ::Reme::print_backtrace);        \
        std::signal(SIGTRAP, ::Reme::print_backtrace);        \
                                                              \
        auto app = new AppClass();                            \
        app->run();                                           \
        delete app;                                           \
        return 0;                                             \
    }
