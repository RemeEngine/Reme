#pragma once

namespace Reme {

class Renderer {
public:
    static void initialize();
    static void shutdown();

    static void on_window_resize(float width, float height);
};

} // namespace Reme
