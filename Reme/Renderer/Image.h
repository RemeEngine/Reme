#pragma once

#include <Reme/Core/Asset.h>
#include <Reme/Debug/Instrumentor.h>
#include <Reme/Renderer/Color.h>

namespace Reme {
class Image : public Asset {
public:
    static RefPtr<Image> create(u32 width, u32 height)
    {
        PROFILE_FUNCTION();
        return Asset::make<Image>(width, height);
    }

    static RefPtr<Image> create(const std::string& path)
    {
        PROFILE_FUNCTION();
        return Asset::make<Image>(path);
    }

public:    
    Image(u32 width, u32 height);
    Image(const std::string& path);
    virtual ~Image() override;

    inline u32 width() const { return m_width; }
    inline u32 height() const { return m_height; }

    inline Color pixel(u32 x, u32 y) const
    {
        ASSERT(x < m_width && y < m_height, "Access out of bound index");
        return m_pixels[x + y * m_width];
    }

    inline void set_pixel(u32 x, u32 y, const Color& color)
    {
        ASSERT(x < m_width && y < m_height, "Access out of bound index");
        m_pixels[x + y * m_width] = color;
    }

    inline const Color* pixels_data() const { return m_pixels; }
    void set_pixels_data(const Color* pixels);

    inline void copy(const RefPtr<Image>& source, u32 dX, u32 dY, bool apply_alpha = false)
    {
        copy(source, dX, dY, 0, 0, source->width(), source->height(), apply_alpha);
    }

    inline void copy(const RefPtr<Image>& source, u32 dX, u32 dY, u32 sX, u32 sY, bool apply_alpha = false)
    {
        copy(source, dX, dY, sX, sY, source->width(), source->height(), apply_alpha);
    }

    void copy(const RefPtr<Image>& source, u32 dX, u32 dY, u32 sX, u32 sY, u32 sW, u32 sH, bool apply_alpha = false);

    virtual const char* class_name() const override { return "Image"; }

private:

    u32 m_width { 0 };
    u32 m_height { 0 };
    Color* m_pixels { nullptr };
};
} // namespace Reme
