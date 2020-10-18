#pragma once

#include <Reme/Core/Window.h>
#include <Reme/Events/ApplicationEvent.h>
#include <Reme/Events/Event.h>

namespace Reme {

class Application {
public:
    static inline Application& the()
    {
        ASSERT(s_instance, "Application need to be initialize before use");
        return *s_instance;
    }

    Application(const WindowProps& props = { "Reme Engine", 1280, 720 });
    virtual ~Application();

    inline float delta_time() const { return m_delta_time; }
    inline void set_delta_time(float dt) { m_delta_time = dt; }

    inline Window& window() { return *m_window; }
    void run();

private:
    void on_event(Event&);
    bool on_window_close(WindowCloseEvent);
    bool on_window_resize(WindowResizeEvent);

    static Application* s_instance;

    OwnPtr<Window> m_window;
    bool m_running { false };
    bool m_minimized { false };
    float m_delta_time { 1.0 / 60 };
};

} // namespace Reme
