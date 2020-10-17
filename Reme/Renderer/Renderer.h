#pragma once

#include <Reme/Core/Badge.h>

namespace Reme {

class Application;

class Renderer {
public:
    static void initialize();
    static void shutdown();

    static void on_window_resize(Badge<Application>, float width, float height);
};

} // namespace Reme
