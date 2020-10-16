#pragma once

#include <Reme/Core/Core.h>
#include <Reme/Events/Event.h>
#include <Reme/GUI/Node.h>

namespace Reme {

struct WindowProps {
    std::string title;
    u32 width, height;
};

class Window {
    MAKE_NONCOPYABLE(Window);

public:
    using EventFunctionCB = std::function<void(Event&)>;
    static OwnPtr<Window> construct(const WindowProps& props);

    virtual ~Window() {};

    virtual void poll_event() = 0;
    virtual void swap_buffers() = 0;
    virtual void make_context_current() = 0;

    virtual u32 width() const = 0;
    virtual u32 height() const = 0;
    virtual void set_size(u32 width, u32 height) = 0;

    virtual void set_title(const std::string& title) = 0;
    virtual const std::string& title() const = 0;

    virtual void enable_VSync(bool enabled) = 0;
    virtual bool is_VSync() const = 0;

    virtual void* native_window() const = 0;
    virtual void set_event_callback(EventFunctionCB) = 0;

    RefPtr<GUI::Node> current_scene() { return m_scene; }
    void set_current_scene(RefPtr<GUI::Node> scene)
    {
        if (m_scene) {
            m_scene->on_exit();
        }

        m_scene = scene;
        scene->on_enter();
    }

    void on_event(Event& event)
    {
        if (m_scene)
            m_scene->on_event({}, event);
    }

private:
    RefPtr<GUI::Node> m_scene;
};

} // namespace Reme
