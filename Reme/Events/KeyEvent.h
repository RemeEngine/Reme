#pragma once

#include <Reme/Events/Event.h>
#include <Reme/Events/KeyCodes.h>
#include <sstream>

namespace Reme {

class KeyEvent : public Event {
public:
    inline KeyCode key_code() const { return m_keycode; }

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
protected:
    KeyEvent(KeyCode keycode)
        : m_keycode(keycode)
    {
    }

    KeyCode m_keycode;
};

class KeyDownEvent : public KeyEvent {
public:
    KeyDownEvent(KeyCode keycode, int repeat_count)
        : KeyEvent(keycode)
        , m_repeat_count(repeat_count)
    {
    }

    inline int repeat_count() const { return m_repeat_count; }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "KeyDownEvent: " << m_keycode << " (" << m_repeat_count << " repeats)";
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyDown)
private:
    int m_repeat_count;
};

class KeyUpEvent : public KeyEvent {
public:
    KeyUpEvent(KeyCode keycode)
        : KeyEvent(keycode)
    {
    }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "KeyUpEvent: " << m_keycode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyUp)
};

class KeyPressEvent : public KeyEvent {
public:
    KeyPressEvent(KeyCode keycode)
        : KeyEvent(keycode)
    {
    }

    std::string to_string() const override
    {
        std::stringstream ss;
        ss << "KeyPressEvent: " << m_keycode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPress)
};

} // namespace Reme
