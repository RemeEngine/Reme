#pragma once

#include <Reme/Renderer/Image.h>
#include <Reme/Renderer/Texture.h>

namespace Reme {
class OpenGL_Texture : public Texture {
public:
    OpenGL_Texture(u32 width, u32 height);
    OpenGL_Texture(const RefPtr<Image>& image);
    virtual ~OpenGL_Texture() override;

    inline u32 width() const override { return m_width; }
    inline u32 height() const override { return m_height; }
    inline u32 internal_id() const override { return m_texture_id; }

    void generate_mipmap() const override;
    void set_data(const Color* data, u32 x, u32 y, u32 width, u32 height) override;

    void bind(u32 slot) override;

private:
    u32 m_width;
    u32 m_height;
    u32 m_texture_id;
};
} // namespace Reme
