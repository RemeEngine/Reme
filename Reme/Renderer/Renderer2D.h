#pragma once

#include <Reme/Core/Core.h>
#include <Reme/Renderer/Buffers.h>
#include <Reme/Renderer/Camera.h>
#include <Reme/Renderer/Color.h>
#include <Reme/Renderer/Shader.h>
#include <Reme/Renderer/Texture.h>
#include <Reme/Renderer/VertexArray.h>

#include <glm/glm.hpp>

namespace Reme {
class Renderer2D {
public:
    static void initialize();
    static void shutdown();

    static void begin(const RefPtr<Camera>& cam);
    static void end();

    // Basic Quad Drawing API

    static void fill_rect(const Color& color, float x, float y, float w, float h)
    {
        draw_partial_texture(Texture::WHITE, 0.0f, 0.0f, 0.0f, 0.0f, x, y, w, h, color);
    }

    static void draw_texture(const RefPtr<Texture>& texture, float dX, float dY)
    {
        draw_partial_texture(
            texture,
            0.0f, 0.0f, texture->width(), texture->height(),
            dX, dY, texture->width(), texture->height());
    }

    static void draw_texture(const RefPtr<Texture>& texture, float dX, float dY, float dW, float dH)
    {
        draw_partial_texture(
            texture,
            0.0f, 0.0f, texture->width(), texture->height(),
            dX, dY, dW, dH);
    }

    static void draw_partial_texture(
        const RefPtr<Texture>& texture,
        float sX, float sY, float sW, float sH,
        float dX, float dY, float dW, float dH,
        const Color& color = Color::WHITE);

    // Transformation
    static void push_state();
    static void pop_state();

    static const glm::mat3& transformation_matrix();
    static void set_transformation_matrix(const glm::mat3& mat);

    static void translate(float x, float y);
    static void scale(float x, float y);
    static void rotate(float rotRadian);

    struct Vertex {
        glm::vec2 position;
        glm::vec2 UV;
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

        std::vector<WeakPtr<Texture>> textures;
        u32 textureIndex;
    };

private:
    static void flush();
};
} // namespace Reme
