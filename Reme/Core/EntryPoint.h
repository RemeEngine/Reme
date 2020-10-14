#pragma once

#include <Reme/Core/Application.h>
#include <Reme/Core/Core.h>

#define REME_APP_ENTRY(AppClass)                              \
    int main(MAYBE_UNUSED int argc, MAYBE_UNUSED char** argv) \
    {                                                         \
        ::Reme::Log::initialize(#AppClass);                   \
                                                              \
        auto app = new AppClass();                            \
        app->exec();                                          \
        delete app;                                           \
        return 0;                                             \
    }
