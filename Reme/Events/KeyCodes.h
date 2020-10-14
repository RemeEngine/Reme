#pragma once

#include <Reme/Core/Core.h>

namespace Reme {

// From glfw3.h
#define __ENUMERATE_KEY_CODE(XX) \
    XX(Space, 32)                \
    XX(Apostrophe, 39)           \
    XX(Comma, 44)                \
    XX(Minus, 45)                \
    XX(Period, 46)               \
    XX(Slash, 47)                \
    XX(D0, 48)                   \
    XX(D1, 49)                   \
    XX(D2, 50)                   \
    XX(D3, 51)                   \
    XX(D4, 52)                   \
    XX(D5, 53)                   \
    XX(D6, 54)                   \
    XX(D7, 55)                   \
    XX(D8, 56)                   \
    XX(D9, 57)                   \
    XX(Semicolon, 59)            \
    XX(Equal, 61)                \
    XX(A, 65)                    \
    XX(B, 66)                    \
    XX(C, 67)                    \
    XX(D, 68)                    \
    XX(E, 69)                    \
    XX(F, 70)                    \
    XX(G, 71)                    \
    XX(H, 72)                    \
    XX(I, 73)                    \
    XX(J, 74)                    \
    XX(K, 75)                    \
    XX(L, 76)                    \
    XX(M, 77)                    \
    XX(N, 78)                    \
    XX(O, 79)                    \
    XX(P, 80)                    \
    XX(Q, 81)                    \
    XX(R, 82)                    \
    XX(S, 83)                    \
    XX(T, 84)                    \
    XX(U, 85)                    \
    XX(V, 86)                    \
    XX(W, 87)                    \
    XX(X, 88)                    \
    XX(Y, 89)                    \
    XX(Z, 90)                    \
    XX(LeftBracket, 91)          \
    XX(Backslash, 92)            \
    XX(RightBracket, 93)         \
    XX(GraveAccent, 96)          \
    XX(World1, 161)              \
    XX(World2, 162)              \
    XX(Escape, 256)              \
    XX(Enter, 257)               \
    XX(Tab, 258)                 \
    XX(Backspace, 259)           \
    XX(Insert, 260)              \
    XX(Delete, 261)              \
    XX(Right, 262)               \
    XX(Left, 263)                \
    XX(Down, 264)                \
    XX(Up, 265)                  \
    XX(PageUp, 266)              \
    XX(PageDown, 267)            \
    XX(Home, 268)                \
    XX(End, 269)                 \
    XX(CapsLock, 280)            \
    XX(ScrollLock, 281)          \
    XX(NumLock, 282)             \
    XX(PrintScreen, 283)         \
    XX(Pause, 284)               \
    XX(F1, 290)                  \
    XX(F2, 291)                  \
    XX(F3, 292)                  \
    XX(F4, 293)                  \
    XX(F5, 294)                  \
    XX(F6, 295)                  \
    XX(F7, 296)                  \
    XX(F8, 297)                  \
    XX(F9, 298)                  \
    XX(F10, 299)                 \
    XX(F11, 300)                 \
    XX(F12, 301)                 \
    XX(F13, 302)                 \
    XX(F14, 303)                 \
    XX(F15, 304)                 \
    XX(F16, 305)                 \
    XX(F17, 306)                 \
    XX(F18, 307)                 \
    XX(F19, 308)                 \
    XX(F20, 309)                 \
    XX(F21, 310)                 \
    XX(F22, 311)                 \
    XX(F23, 312)                 \
    XX(F24, 313)                 \
    XX(F25, 314)                 \
    XX(KP0, 320)                 \
    XX(KP1, 321)                 \
    XX(KP2, 322)                 \
    XX(KP3, 323)                 \
    XX(KP4, 324)                 \
    XX(KP5, 325)                 \
    XX(KP6, 326)                 \
    XX(KP7, 327)                 \
    XX(KP8, 328)                 \
    XX(KP9, 329)                 \
    XX(KPDecimal, 330)           \
    XX(KPDivide, 331)            \
    XX(KPMultiply, 332)          \
    XX(KPSubtract, 333)          \
    XX(KPAdd, 334)               \
    XX(KPEnter, 335)             \
    XX(KPEqual, 336)             \
    XX(LeftShift, 340)           \
    XX(LeftControl, 341)         \
    XX(LeftAlt, 342)             \
    XX(LeftSuper, 343)           \
    XX(RightShift, 344)          \
    XX(RightControl, 345)        \
    XX(RightAlt, 346)            \
    XX(RightSuper, 347)          \
    XX(Menu, 348)

enum class KeyCode : u16 {
#define DECLARE_KEY_CODE(key, value) key = value,
    __ENUMERATE_KEY_CODE(DECLARE_KEY_CODE)
#undef DECLARE_KEY_CODE
};

inline std::ostream& operator<<(std::ostream& os, KeyCode key_code)
{
    os << "Key";
    switch (key_code) {
#define PRINT_KEY_CODE(key, value) \
    case KeyCode::key:             \
        return os << #key;
        __ENUMERATE_KEY_CODE(PRINT_KEY_CODE)
#undef PRINT_KEY_CODE
    default:
        return os << "Unknown";
    }
}

} // namespace Reme
