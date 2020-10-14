#pragma once

#include <Reme/Events/Event.h>
#include <Reme/Events/MouseCodes.h>
#include <sstream>

namespace Reme {
class MouseMoveEvent : public Event {
public:
    MouseMoveEvent(float x, float y)
        : m_mouse_x(x)
        , m_mouse_y(y)
    {
    }

    inline float x() const { return m_mouse_x; }
    inline float y() const { return m_mouse_y; }

    virtual std::string to_string() const override
    {
        std::stringstream ss;
        ss << "MouseMoveEvent: " << m_mouse_x << ", " << m_mouse_y;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseMove)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

private:
    float m_mouse_x;
    float m_mouse_y;
};

class MouseScrollEvent : public Event {
public:
    MouseScrollEvent(float x_ofsset, float y_offset)
        : m_x_offset(x_ofsset)
        , m_y_offset(y_offset)
    {
    }

    inline float x_offset() const { return m_x_offset; }
    inline float y_offset() const { return m_y_offset; }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "MouseScrollEvent: " << x_offset() << ", " << y_offset();
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseScroll)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

private:
    float m_x_offset, m_y_offset;
};

class MouseButtonEvent : public Event {
public:
    inline MouseCode button() const { return m_button; }

    EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryMouse | EventCategoryInput)
protected:
    MouseButtonEvent(MouseCode button)
        : m_button(button)
    {
    }

    MouseCode m_button;
};

class MouseDownEvent : public MouseButtonEvent {
public:
    MouseDownEvent(MouseCode button)
        : MouseButtonEvent(button)
    {
    }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "MouseDownEvent: " << m_button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseDown)
};

class MouseUpEvent : public MouseButtonEvent {
public:
    MouseUpEvent(MouseCode button)
        : MouseButtonEvent(button)
    {
    }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "MouseUpEvent: " << m_button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseUp)
};
} // namespace Reme
