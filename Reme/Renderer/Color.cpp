#include <Reme/Renderer/Color.h>

#include <algorithm>

namespace Reme {

const Color Color::BLACK(0, 0, 0);
const Color Color::WHITE(255, 255, 255);
const Color Color::RED(255, 0, 0);
const Color Color::GREEN(0, 255, 0);
const Color Color::BLUE(0, 0, 255);
const Color Color::YELLOW(255, 255, 0);
const Color Color::MAGENTA(255, 0, 255);
const Color Color::CYAN(0, 255, 255);
const Color Color::TRANSPARENT(0, 0, 0, 0);

Color::Color()
    : r(0)
    , g(0)
    , b(0)
    , a(255)
{
}

Color::Color(const Color& c)
    : r(c.r)
    , g(c.g)
    , b(c.b)
    , a(c.a)
{
}

Color::Color(u8 red, u8 green, u8 blue, u8 alpha)
    : r(red)
    , g(green)
    , b(blue)
    , a(alpha)
{
}

Color::Color(u32 color)
    : data(color)
{
}

bool operator==(const Color& left, const Color& right)
{
    return left.data == right.data;
}

bool operator!=(const Color& left, const Color& right)
{
    return !(left == right);
}

Color operator+(const Color& left, const Color& right)
{
    return Color(u8(std::min(int(left.r) + right.r, 255)),
        u8(std::min(int(left.g) + right.g, 255)),
        u8(std::min(int(left.b) + right.b, 255)),
        u8(std::min(int(left.a) + right.a, 255)));
}

Color operator-(const Color& left, const Color& right)
{
    return Color(u8(std::max(int(left.r) - right.r, 0)),
        u8(std::max(int(left.g) - right.g, 0)),
        u8(std::max(int(left.b) - right.b, 0)),
        u8(std::max(int(left.a) - right.a, 0)));
}

Color operator*(const Color& left, const Color& right)
{
    return Color(u8(int(left.r) * right.r / 255),
        u8(int(left.g) * right.g / 255),
        u8(int(left.b) * right.b / 255),
        u8(int(left.a) * right.a / 255));
}

Color& operator+=(Color& left, const Color& right)
{
    return left = left + right;
}

Color& operator-=(Color& left, const Color& right)
{
    return left = left - right;
}

Color& operator*=(Color& left, const Color& right)
{
    return left = left * right;
}

} // namespace Reme
