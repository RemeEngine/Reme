#pragma once

#include <Reme/Renderer/Color.h>
#include <Reme/Renderer/VertexArray.h>

namespace Reme {

enum class DrawMode {
    POINTS,
    LINE_STRIP,
    LINE_LOOP,
    LINES,
    TRIANGLE_STRIP,
    TRIANGLE_FAN,
    TRIANGLES
};

struct DrawCall {
    DrawMode mode;
    u32 count;
    u32 offset;
    u32 bindedVAO;
};

class RendererAPI {
public:
    enum API {
        None = 0,
        OpenGL
    };

    static RendererAPI* create();

    virtual void initialize() = 0;
    virtual void set_viewport(u32 x, u32 y, u32 width, u32 height) = 0;
    virtual void set_clear_color(const Color& color) = 0;
    virtual void clear() = 0;
    virtual void poll_errors() = 0;

    virtual void draw_indexed(DrawMode mode, u32 count, u32 offset) = 0;
    virtual void draw_arrays(DrawMode mode, u32 count, u32 offset) = 0;

    virtual u32 max_texture_unit() = 0;
    virtual u32 max_texture_size() = 0;

    inline static API api() { return s_api; }

private:
    static API s_api;
};

class RenderCommand {
public:
    inline static void initialize()
    {
        s_renderer_api->initialize();
    }

    inline static void set_viewport(u32 x, u32 y, u32 width, u32 height)
    {
        s_renderer_api->set_viewport(x, y, width, height);
    }

    inline static void set_clear_color(const Color& color)
    {
        s_renderer_api->set_clear_color(color);
    }

    inline static void clear()
    {
        s_renderer_api->clear();
    }

    inline static void poll_errors()
    {
        s_renderer_api->poll_errors();
    }

    inline static void draw_indexed(DrawMode mode, u32 count, u32 offset = 0)
    {
        s_renderer_api->draw_indexed(mode, count, offset);
    }

    inline static void draw_arrays(DrawMode mode, u32 count, u32 offset = 0)
    {
        s_renderer_api->draw_arrays(mode, count, offset);
    }

    inline static u32 max_texture_unit()
    {
        return s_renderer_api->max_texture_unit();
    }

    inline static u32 max_texture_size()
    {
        return s_renderer_api->max_texture_size();
    }

private:
    static RendererAPI* s_renderer_api;
};

} // namespace Reme
