#pragma once

#include <Reme/Core/Alias.h>

namespace Reme {

class Color {
public:
    Color();
    Color(const Color& c);
    Color(u8 red, u8 green, u8 blue, u8 alpha = 255);
    explicit Color(u32 hexColor);

    static const Color BLACK;
    static const Color WHITE;
    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color YELLOW;
    static const Color MAGENTA;
    static const Color CYAN;
    static const Color TRANSPARENT;

    union {
        struct {
            u8 r, g, b, a;
        };
        u32 data;
    };
};

bool operator==(const Color& left, const Color& right);
bool operator!=(const Color& left, const Color& right);
Color operator+(const Color& left, const Color& right);
Color operator-(const Color& left, const Color& right);
Color operator*(const Color& left, const Color& right);
Color& operator+=(Color& left, const Color& right);
Color& operator-=(Color& left, const Color& right);
Color& operator*=(Color& left, const Color& right);

static_assert(sizeof(Color) == 4, "Color must be tight packed 4 bytes struct!");

} // namespace Reme
