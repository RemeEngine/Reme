#pragma once

#include <Reme/Core/Application.h>
#include <Reme/Core/Core.h>
#include <Reme/Debug/ExceptionHandler.h>

#define REME_APP_ENTRY(AppClass)                              \
    int main(MAYBE_UNUSED int argc, MAYBE_UNUSED char** argv) \
    {                                                         \
        ::Reme::Logger::initialize(#AppClass);                \
        ::Reme::ExceptionHandler::initialize();               \
                                                              \
        auto app = new AppClass();                            \
        app->run();                                           \
        delete app;                                           \
                                                              \
        return 0;                                             \
    }
