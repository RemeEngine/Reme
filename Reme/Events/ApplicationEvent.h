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

    EVENT_CAN_NOT_BE_HANDLED()
    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
private:
    u32 m_width;
    u32 m_height;
};

class WindowCloseEvent : public Event {
public:
    WindowCloseEvent() {};

    EVENT_CAN_NOT_BE_HANDLED()
    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

} // namespace Reme
