#include <Reme/Impl/OpenGL/OpenGL_VertexArray.h>
#include <Reme/Renderer/ShaderDataLayout.h>

#include <glad/glad.h>

namespace Reme {
static GLenum shader_data_type_to_opengl_base_type(ShaderDataType type)
{
    switch (type) {
    case ShaderDataType::Float:
        return GL_FLOAT;
    case ShaderDataType::Float2:
        return GL_FLOAT;
    case ShaderDataType::Float3:
        return GL_FLOAT;
    case ShaderDataType::Float4:
        return GL_FLOAT;
    case ShaderDataType::Mat3:
        return GL_FLOAT;
    case ShaderDataType::Mat4:
        return GL_FLOAT;
    case ShaderDataType::Int:
        return GL_INT;
    case ShaderDataType::Int2:
        return GL_INT;
    case ShaderDataType::Int3:
        return GL_INT;
    case ShaderDataType::Int4:
        return GL_INT;
    default:
        CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }
}

OpenGL_VertexArray::OpenGL_VertexArray()
    : m_vertex_buffer_index(0)
{
    glGenVertexArrays(1, &m_internal_id);
}

OpenGL_VertexArray::~OpenGL_VertexArray()
{
    glDeleteVertexArrays(1, &m_internal_id);
}

void OpenGL_VertexArray::bind()
{
    glBindVertexArray(m_internal_id);
}

void OpenGL_VertexArray::unbind()
{
    glBindVertexArray(0);
}

void OpenGL_VertexArray::add_vertex_buffer(RefPtr<VertexBuffer> vertex_buffer)
{
    bind();
    vertex_buffer->bind();
    const auto& layout = vertex_buffer->layout();

    for (const auto& element : layout) {
        glEnableVertexAttribArray(m_vertex_buffer_index);
        glVertexAttribPointer(
            m_vertex_buffer_index,
            element.component_count(),
            shader_data_type_to_opengl_base_type(element.type),
            element.normalized ? GL_TRUE : GL_FALSE,
            layout.stride(),
            (const void*)static_cast<FlatPtr>(element.offset));
        glVertexAttribDivisor(m_vertex_buffer_index, element.divisor);

        m_vertex_buffer_index++;
    }

    m_vertex_buffers.push_back(vertex_buffer);
    unbind();
}

void OpenGL_VertexArray::set_index_buffer(RefPtr<IndexBuffer> index_buffer)
{
    bind();
    index_buffer->bind();
    m_index_buffer = index_buffer;
    unbind();
}

} // namespace Reme
