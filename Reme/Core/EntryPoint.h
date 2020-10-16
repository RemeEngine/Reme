#pragma once

#include <Reme/Core/Application.h>
#include <Reme/Core/Core.h>
#include <Reme/Debug/ExceptionHandler.h>
#include <Reme/Debug/Instrumentor.h>

#define REME_APP_ENTRY(AppClass)                                  \
    int main(MAYBE_UNUSED int argc, MAYBE_UNUSED char** argv)     \
    {                                                             \
        ::Reme::Logger::initialize(#AppClass);                    \
        ::Reme::ExceptionHandler::initialize();                   \
                                                                  \
        PROFILE_BEGIN_SESSION("Startup", "startup-profile.json"); \
        auto app = new AppClass();                                \
        PROFILE_END_SESSION();                                    \
                                                                  \
        PROFILE_BEGIN_SESSION("Running", "profile.json");         \
        app->run();                                               \
        PROFILE_END_SESSION();                                    \
                                                                  \
        PROFILE_BEGIN_SESSION("Cleanup", "cleanup-profile.json"); \
        delete app;                                               \
        PROFILE_END_SESSION();                                    \
                                                                  \
        return 0;                                                 \
    }
