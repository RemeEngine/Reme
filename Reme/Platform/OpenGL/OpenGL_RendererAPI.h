#pragma once

#include <Reme/Renderer/RendererAPI.h>

namespace Reme {

class OpenGL_RendererAPI : public RendererAPI {
public:
    virtual ~OpenGL_RendererAPI() override {};

    virtual void initialize() override;
    virtual void set_viewport(u32 x, u32 y, u32 width, u32 height) override;
    virtual void set_clear_color(const Color& color) override;
    virtual void clear() override;
    virtual void poll_errors() override;

    virtual void draw_indexed(DrawMode mode, u32 count, u32 offset) override;
    virtual void draw_arrays(DrawMode mode, u32 count, u32 offset) override;

    virtual u32 max_texture_unit() override { return m_max_texture_unit; };
    virtual u32 max_texture_size() override { return m_max_texture_size; };

private:
    u32 m_max_texture_unit;
    u32 m_max_texture_size;
    bool m_use_error_polling = true;
};

} // namespace Reme
