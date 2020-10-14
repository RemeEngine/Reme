#pragma once

#include <Reme/Core/Core.h>

namespace Reme {

// From glfw3.h
#define __ENUMERATE_MOUSE_CODE(XX) \
    XX(ButtonLeft, 0)              \
    XX(ButtonRight, 1)             \
    XX(ButtonMiddle, 2)            \
    XX(ButtonLast, 7)              \
    XX(Button0, ButtonLeft)        \
    XX(Button1, ButtonRight)       \
    XX(Button2, ButtonMiddle)      \
    XX(Button3, 3)                 \
    XX(Button4, 4)                 \
    XX(Button5, 5)                 \
    XX(Button6, 6)                 \
    XX(Button7, ButtonLast)

enum class MouseCode : u16 {
#define DECLARE_MOUSE_CODE(key, value) key = value,
    __ENUMERATE_MOUSE_CODE(DECLARE_MOUSE_CODE)
#undef DECLARE_MOUSE_CODE
};

inline std::ostream& operator<<(std::ostream& os, MouseCode mouse_code)
{
    switch (mouse_code) {
#define PRINT_MOUSE_CODE(key, value) \
    case MouseCode::key:             \
        return os << #key;
#undef PRINT_MOUSE_CODE
    default:
        return os;
    }
}

} // namespace Reme
