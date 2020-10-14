#pragma once

#include <Reme/Core/Core.h>

namespace Reme {

enum class EventType {
    None = 0,
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLostFocus,
    WindowMove,
    AppUpdate,
    AppRender,
    KeyDown,
    KeyUp,
    KeyPress,
    MouseDown,
    MouseUp,
    MouseMove,
    MouseScroll
};

enum EventCategory {
    None = 0,
    EventCategoryApplication = BIT(0),
    EventCategoryInput = BIT(1),
    EventCategoryKeyboard = BIT(2),
    EventCategoryMouse = BIT(3),
    EventCategoryMouseButton = BIT(4)
};

#define EVENT_CLASS_TYPE(event_type)                                  \
    static EventType static_type() { return EventType::event_type; }  \
    virtual EventType type() const override { return static_type(); } \
    virtual const char* name() const override { return #event_type; }

#define EVENT_CLASS_CATEGORY(category) \
    virtual int category_flags() const override { return category; }

class Event {
public:
    bool handled = false;

    virtual EventType type() const = 0;
    virtual const char* name() const = 0;
    virtual int category_flags() const = 0;
    virtual std::string to_string() const { return name(); }

    inline bool in_category(EventCategory category)
    {
        return category_flags() & category;
    }
};

class EventDispatcher {
public:
    EventDispatcher(Event& event)
        : m_event(event)
    {
    }

    template<typename T, typename F>
    bool dispatch(const F& func)
    {
        if (m_event.type() == T::static_type()) {
            m_event.handled = func(static_cast<T&>(m_event));
            return true;
        }

        return false;
    }

private:
    Event& m_event;
};

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
    return os << e.to_string();
}

} // namespace Reme
