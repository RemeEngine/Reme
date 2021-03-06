#pragma once

#include <Reme/Core/Window.h>

typedef struct GLFWwindow GLFWwindow;

namespace Reme {

class GLFW_Window : public Window {
public:
    GLFW_Window(const WindowProps& props);
    virtual ~GLFW_Window() override;

    virtual void poll_event() override;
    virtual void swap_buffers() override;
    virtual void make_context_current() override;

    virtual u32 width() const override;
    virtual u32 height() const override;
    virtual void set_size(u32 width, u32 height) override;

    virtual void set_title(const std::string& title) override;
    virtual const std::string& title() const override;

    virtual void enable_VSync(bool enabled) override;
    virtual bool is_VSync() const override;

    virtual void* native_window() const override { return m_window; };
    virtual void set_event_callback(EventFunctionCB callback) override { m_data.on_event = callback; }

private:
    GLFWwindow* m_window;

    struct WindowData {
        bool is_VSync;
        u32 width;
        u32 height;
        std::string title;
        EventFunctionCB on_event;
    };

    WindowData m_data;
};

} // namespace Reme
