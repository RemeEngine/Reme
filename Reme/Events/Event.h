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
    KeyDown,
    KeyUp,
    KeyPress,
    MouseDown,
    MouseUp,
    MouseMove,
    MouseScroll,
    AppRender,
    AppUpdate,
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

#define EVENT_CAN_NOT_BE_HANDLED() \
    virtual void mark_is_handled() override {}

class Event {
public:
    virtual EventType type() const = 0;
    virtual const char* name() const = 0;
    virtual int category_flags() const = 0;
    virtual std::string to_string() const { return name(); }

    inline bool is_handled() const { return m_handled; }
    virtual void mark_is_handled() { m_handled = true; }

    inline bool should_propagate() const { return m_should_propagate; }
    virtual void stop_propagation() { m_should_propagate = false; }

    inline bool in_category(EventCategory category)
    {
        return category_flags() & category;
    }

private:
    bool m_handled { false };
    bool m_should_propagate { true };
};

class SimpleEventDispatcher {
public:
    SimpleEventDispatcher(Event& event)
        : m_event(event)
    {
    }

    template<typename T, typename F>
    bool dispatch(const F& func)
    {
        if (m_event.type() == T::static_type()) {
            if (func(static_cast<T&>(m_event)))
                m_event.mark_is_handled();

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
