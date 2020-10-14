#pragma once

#include <Reme/Core/Application.h>
#include <Reme/Core/Core.h>

#define REME_APP_ENTRY(AppClass)                 \
    int main(MAYBE_UNUSED int argc, char** argv) \
    {                                            \
        ::Reme::Log::init(#AppClass);            \
                                                 \
        auto app = new AppClass();               \
        app->exec();                             \
        delete app;                              \
        return 0;                                \
    }