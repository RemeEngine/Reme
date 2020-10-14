#pragma once

#include <Reme/Events/Event.h>
#include <Reme/Events/KeyCodes.h>
#include <Reme/Events/MouseCodes.h>
#include <Reme/Forward.h>

#include <glm/glm.hpp>
#include <unordered_map>

namespace Reme {

class Input {
public:
    enum class KeyState {
        KeyUp = 0,
        KeyDown = 1,
        KeyRepeat = 2
    };

public:
    static void on_event(Event& event);
    static bool is_key_pressed(KeyCode key);
    static bool is_key_repeated(KeyCode key);
    static bool is_mouse_pressed(MouseCode button);
    static glm::vec2 mouse_position();

private:
    static bool on_key_down(KeyDownEvent e);
    static bool on_key_up(KeyUpEvent e);
    static bool on_mouse_down(MouseDownEvent e);
    static bool on_mouse_up(MouseUpEvent e);
    static bool on_mouse_move(MouseMoveEvent e);

    struct InputData {
        std::unordered_map<u16, KeyState> key_map;
        float mouse_x, mouse_y;
    };

    static InputData s_data;
};

} // namespace Reme
