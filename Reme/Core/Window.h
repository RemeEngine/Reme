#pragma once

#include <Reme/Core/Core.h>

namespace Reme {

struct WindowProps {
    std::string title;
    u32 width, height;
};

class Window {
public:
    static OwnPtr<Window> construct(const WindowProps& props);

    virtual ~Window() = default;

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
};

} // namespace Reme
