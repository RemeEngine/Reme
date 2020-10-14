#pragma once

#include <Reme/Core/Window.h>

int main(int, char**);

namespace Reme {

class Application {
public:
	static inline Application& the() { return *s_instance; }

    Application(const WindowProps& props = { "Reme Engine", 1280, 720 });
    virtual ~Application();

    inline Window& window() { return *m_window; }    

private:
    void exec();

    static Application* s_instance;
    friend int ::main(int, char**);

    OwnPtr<Window> m_window;
    bool m_running { true };
    bool m_minimized { false };
    float m_delta_time { 1.0 / 60 };
};

} // namespace Reme
