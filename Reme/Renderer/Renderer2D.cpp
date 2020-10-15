#include <Reme/Renderer/Renderer2D.h>
#include <Reme/Renderer/RendererAPI.h>

#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

namespace Reme {

static const u32 MAX_QUAD_COUNT = 100000;

static const u32 MAX_VERTEX_COUNT = MAX_QUAD_COUNT * 4;
static const u32 MAX_INDEX_COUNT = MAX_QUAD_COUNT * 6;
static u32 MAX_TEXTURE_UNIT;

static Renderer2D::Data s_data;
static std::vector<glm::mat3> s_tranform_stack;

void Renderer2D::initialize()
{
    s_tranform_stack.push_back(glm::mat3(1.0f));
    s_data.buffer = new Vertex[MAX_QUAD_COUNT * 4];

    MAX_TEXTURE_UNIT = RenderCommand::max_texture_unit();

    s_data.flat_color_shader = Shader::create("Flat Shader",
        // Vertex shader
        "#version 330 core\n"

        "uniform mat4 viewMat;\n"
        "uniform mat4 projMat;\n"

        "layout (location = 0) in vec2 Position;\n"
        "layout (location = 1) in vec2 UV;\n"
        "layout (location = 2) in vec4 Color;\n"
        "layout (location = 3) in float TexIndex;\n"

        "out vec2 Frag_UV;\n"
        "out vec4 Frag_Color;\n"
        "out float Frag_TexIndex;\n"

        "void main()\n"
        "{\n"
        "	  Frag_UV = UV;\n"
        "     Frag_Color = Color;\n"
        "     Frag_TexIndex = TexIndex;\n"
        "	  gl_Position = projMat * viewMat * vec4(Position, 0, 1);\n"
        "}\n",
        // Fragment shader
        "#version 330 core\n"

        "in vec2 Frag_UV;\n"
        "in vec4 Frag_Color;\n"
        "in float Frag_TexIndex;\n"

        "out vec4 Out_Color;\n"

        "uniform sampler2D Textures[6];\n"

        "void main()\n"
        "{\n"
        "    vec4 texColor;\n"
        "    if (Frag_TexIndex < 0.5) texColor = texture(Textures[0], Frag_UV);\n"
        "    else if (Frag_TexIndex < 1.5) texColor = texture(Textures[1], Frag_UV);\n"
        "    else if (Frag_TexIndex < 2.5) texColor = texture(Textures[2], Frag_UV);\n"
        "    else if (Frag_TexIndex < 3.5) texColor = texture(Textures[3], Frag_UV);\n"
        "    else if (Frag_TexIndex < 4.5) texColor = texture(Textures[4], Frag_UV);\n"
        "    else texColor = texture(Textures[5], Frag_UV);\n"

        "    Out_Color = Frag_Color * texColor;\n"
        "}\n");

    s_data.flat_color_shader->bind();

    i32* u_texture_indexes = new i32[MAX_TEXTURE_UNIT];
    for (u32 i = 0; i < MAX_TEXTURE_UNIT; i++)
        u_texture_indexes[i] = i;

    s_data.flat_color_shader->set_int_array("Textures", u_texture_indexes, MAX_TEXTURE_UNIT);
    delete[] u_texture_indexes;

    s_data.VAO = VertexArray::create();

    s_data.VBO = VertexBuffer::create(MAX_VERTEX_COUNT * sizeof(Vertex), false);
    s_data.VBO->set_layout({
        { ShaderDataType::Float2, "Position" },
        { ShaderDataType::Float2, "UV" },
        { ShaderDataType::Float4, "Color" },
        { ShaderDataType::Float, "TexIndex" },
    });

    s_data.VAO->add_vertex_buffer(s_data.VBO);

    u32 offset = 0;
    u32* indicies = new u32[MAX_INDEX_COUNT];
    for (u32 i = 0; i < MAX_INDEX_COUNT; i += 6) {
        indicies[i + 0] = offset + 0;
        indicies[i + 1] = offset + 1;
        indicies[i + 2] = offset + 2;
        indicies[i + 3] = offset + 1;
        indicies[i + 4] = offset + 2;
        indicies[i + 5] = offset + 3;
        offset += 4;
    }

    auto IBO = IndexBuffer::create(MAX_INDEX_COUNT * sizeof(u32));
    IBO->set_data(indicies, 0, MAX_INDEX_COUNT * sizeof(u32));
    s_data.VAO->set_index_buffer(IBO);
    delete[] indicies;

    s_data.vertex_index = 0;
}

void Renderer2D::shutdown()
{
    s_data.flat_color_shader = nullptr;
    s_data.VBO = nullptr;
    s_data.VAO = nullptr;
    delete s_data.buffer;
}

void Renderer2D::begin(const RefPtr<Camera>& cam)
{
    RenderCommand::clear();
    s_data.flat_color_shader->bind();
    s_data.flat_color_shader->set_mat4("viewMat", cam->view_matrix());
    s_data.flat_color_shader->set_mat4("projMat", cam->projection_matrix());

    s_data.VAO->bind();
}

void Renderer2D::end()
{
    flush();
    s_data.VAO->unbind();
    RenderCommand::poll_errors();
}

void Renderer2D::flush()
{
    if (s_data.vertex_index == 0)
        return;

    for (u32 i = 0; i < s_data.textures.size(); i++) {
        s_data.textures[i]->bind(i);
    }

    s_data.VBO->set_data((float*)s_data.buffer, 0, s_data.vertex_index * sizeof(Vertex));
    RenderCommand::draw_indexed(DrawMode::TRIANGLES, s_data.vertex_index / 4 * 6);

    s_data.vertex_index = 0;
    s_data.textures.clear();
}

void Renderer2D::draw_partial_texture(
    const RefPtr<Texture>& texture,
    float source_x, float source_y, float source_width, float source_height,
    float dest_x, float dest_y, float dest_width, float dest_height,
    const Color& color)
{
    float texture_index = -1.0f;
    for (u32 i = 0; i < s_data.textures.size(); i++) {
        if (texture->uid() == s_data.textures[i]->uid()) {
            texture_index = (float)i;
            break;
        }
    }

    if (
        s_data.vertex_index + 4 >= MAX_QUAD_COUNT || (texture_index == -1.0f && s_data.textures.size() == MAX_TEXTURE_UNIT)) {
        flush();
    }

    if (texture_index == -1.0f) {
        texture_index = (float)s_data.textures.size();
        s_data.textures.push_back(texture);
    }

    const glm::mat3& transform_matrix = s_tranform_stack.back();
    const glm::vec4 float_color(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);

    source_x = source_x / texture->width();
    source_y = source_y / texture->height();
    source_width = source_width / texture->width();
    source_height = source_height / texture->height();

    s_data.buffer[s_data.vertex_index++] = {
        .position = transform_matrix * glm::vec3(dest_x, dest_y, 1.0f),
        .uv = { source_x, source_y },
        .color = float_color,
        .texture_index = texture_index,
    };

    s_data.buffer[s_data.vertex_index++] = {
        .position = transform_matrix * glm::vec3(dest_x + dest_width, dest_y, 1.0f),
        .uv = { source_x + source_width, source_y },
        .color = float_color,
        .texture_index = texture_index,
    };

    s_data.buffer[s_data.vertex_index++] = {
        .position = transform_matrix * glm::vec3(dest_x, dest_y + dest_height, 1.0f),
        .uv = { source_x, source_y + source_height },
        .color = float_color,
        .texture_index = texture_index,
    };

    s_data.buffer[s_data.vertex_index++] = {
        .position = transform_matrix * glm::vec3(dest_x + dest_width, dest_y + dest_height, 1.0f),
        .uv = { source_x + source_width, source_y + source_height },
        .color = float_color,
        .texture_index = texture_index,
    };
}

void Renderer2D::push_state()
{
    s_tranform_stack.push_back(glm::mat3(1.0f));
}

void Renderer2D::pop_state()
{
    ASSERT(s_tranform_stack.size() > 1, "Must call push_state() before pop_state()");
    s_tranform_stack.pop_back();
}

const glm::mat3& Renderer2D::transformation_matrix()
{
    return s_tranform_stack.back();
}

void Renderer2D::set_transformation_matrix(const glm::mat3& mat)
{
    s_tranform_stack.back() = mat;
}

void Renderer2D::translate(float x, float y)
{
    s_tranform_stack.back() = glm::translate(s_tranform_stack.back(), glm::vec2(x, y));
}

void Renderer2D::scale(float x, float y)
{
    s_tranform_stack.back() = glm::scale(s_tranform_stack.back(), glm::vec2(x, y));
}

void Renderer2D::rotate(float r)
{
    s_tranform_stack.back() = glm::rotate(s_tranform_stack.back(), r);
}

} // namespace Reme
