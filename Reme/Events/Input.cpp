#include <Reme/Events/Input.h>

#include <Reme/Events/KeyEvent.h>
#include <Reme/Events/MouseEvent.h>

namespace Reme {

Input::InputData Input::s_data;

void Input::on_event(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.dispatch<KeyDownEvent>(Input::on_key_down);
    dispatcher.dispatch<KeyUpEvent>(Input::on_key_up);
    dispatcher.dispatch<MouseDownEvent>(Input::on_mouse_down);
    dispatcher.dispatch<MouseUpEvent>(Input::on_mouse_up);
    dispatcher.dispatch<MouseMoveEvent>(Input::on_mouse_move);
}

bool Input::is_key_pressed(KeyCode key)
{
    if (s_data.key_map.count((u16)key)) {
        auto state = s_data.key_map[(u16)key];
        return state == KeyState::KeyDown || state == KeyState::KeyRepeat;
    }

    return false;
}

bool Input::is_key_repeated(KeyCode key)
{
    if (s_data.key_map.count((u16)key)) {
        return s_data.key_map[(u16)key] == KeyState::KeyRepeat;
    }

    return false;
}

bool Input::is_mouse_pressed(MouseCode button)
{
    if (s_data.key_map.count((u16)button)) {
        auto state = s_data.key_map[(u16)button];
        return state == KeyState::KeyDown;
    }

    return false;
}

glm::vec2 Input::mouse_position()
{
    return { s_data.mouse_x, s_data.mouse_y };
}

bool Input::on_key_down(KeyDownEvent e)
{
    s_data.key_map[(u16)e.key_code()] = e.repeat_count() ? KeyState::KeyRepeat : KeyState::KeyDown;
    return false;
}

bool Input::on_key_up(KeyUpEvent e)
{
    s_data.key_map[(u16)e.key_code()] = KeyState::KeyUp;
    return false;
}

bool Input::on_mouse_down(MouseDownEvent e)
{
    s_data.key_map[(u16)e.button()] = KeyState::KeyDown;
    return false;
}

bool Input::on_mouse_up(MouseUpEvent e)
{
    s_data.key_map[(u16)e.button()] = KeyState::KeyUp;
    return false;
}

bool Input::on_mouse_move(MouseMoveEvent e)
{
    s_data.mouse_x = e.x();
    s_data.mouse_y = e.y();
    return false;
}

} // namespace Reme
