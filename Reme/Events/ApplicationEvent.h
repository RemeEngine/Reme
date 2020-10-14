#pragma once

#include <Reme/Events/Event.h>
#include <sstream>

namespace Reme {

class WindowResizeEvent : public Event {
public:
    WindowResizeEvent(u32 width, u32 height)
        : m_width(width)
        , m_height(height)
    {
    }

    inline unsigned int width() const { return m_width; }
    inline unsigned int height() const { return m_height; }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << m_width << ", " << m_height;
        return ss.str();
    }

    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
private:
    u32 m_width;
    u32 m_height;
};

class WindowCloseEvent : public Event {
public:
    WindowCloseEvent() {};

    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppUpdateEvent : public Event {
public:
    AppUpdateEvent(float elapsed_time)
        : m_elapsed_time(elapsed_time)
    {
    }

    float delta_time() const { return m_elapsed_time; }

    EVENT_CLASS_TYPE(AppUpdate)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
private:
    float m_elapsed_time;
};

class AppRenderEvent : public Event {
public:
    AppRenderEvent() {};

    EVENT_CLASS_TYPE(AppRender)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

} // namespace Reme
