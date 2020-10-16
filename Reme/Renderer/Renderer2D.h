#pragma once

#include <Reme/Core/Core.h>
#include <Reme/Renderer/Buffers.h>
#include <Reme/Renderer/Camera.h>
#include <Reme/Renderer/Color.h>
#include <Reme/Renderer/OrthographicCamera.h>
#include <Reme/Renderer/Shader.h>
#include <Reme/Renderer/Texture.h>
#include <Reme/Renderer/VertexArray.h>

#include <glm/glm.hpp>

namespace Reme {
class Renderer2D {
public:
    static void initialize();
    static void shutdown();

    static void begin(const RefPtr<Camera>& cam = OrthographicCamera::DEFAULT);
    static void end();

    // Basic Quad Drawing API

    static void fill_rect(const Color& color, float x, float y, float width, float height)
    {
        draw_partial_texture(Texture::WHITE, 0.0f, 0.0f, 0.0f, 0.0f, x, y, width, height, color);
    }

    static void draw_texture(const RefPtr<Texture>& texture, float dest_x, float dest_y)
    {
        draw_partial_texture(
            texture,
            0.0f, 0.0f, texture->width(), texture->height(),
            dest_x, dest_y, texture->width(), texture->height());
    }

    static void draw_texture(const RefPtr<Texture>& texture, float dest_x, float dest_y, float dest_width, float dest_height)
    {
        draw_partial_texture(
            texture,
            0.0f, 0.0f, texture->width(), texture->height(),
            dest_x, dest_y, dest_width, dest_height);
    }

    static void draw_partial_texture(
        const RefPtr<Texture>& texture,
        float source_x, float source_y, float source_width, float source_height,
        float dest_x, float dest_y, float dest_width, float dest_height,
        const Color& color = Color::WHITE);

    // Transformation
    static void push_state();
    static void pop_state();

    static const glm::mat3& transformation_matrix();
    static void set_transformation_matrix(const glm::mat3& mat);

    static void translate(float x, float y);
    static void scale(float x, float y);
    static void rotate(float rotation_radian);

    struct Vertex {
        glm::vec2 position;
        glm::vec2 uv;
        glm::vec4 color;
        float texture_index;
    };

    struct Data {
        RefPtr<Shader> flat_color_shader;
        RefPtr<VertexArray> VAO;
        RefPtr<VertexBuffer> VBO;

        // Data for Batch Rendering
        Vertex* buffer;
        u32 vertex_index;

        std::vector<RefPtr<Texture>> textures;
    };

private:
    static void flush();
};
} // namespace Reme
