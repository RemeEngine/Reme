#include <Reme/Platform/OpenGL/OpenGL_Shader.h>
#include <Reme/Utility/Utils.h>

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Reme {

OpenGL_Shader::OpenGL_Shader(const std::string& filepath)
{
    std::unordered_map<u32, std::string> sources;
    sources[GL_VERTEX_SHADER] = ReadFile(filepath + ".vert");
    sources[GL_FRAGMENT_SHADER] = ReadFile(filepath + ".frag");
    compile(sources);

    // Extract name from filepath
    auto last_slash_pos = filepath.find_last_of("/\\");
    last_slash_pos = last_slash_pos == std::string::npos ? 0 : last_slash_pos + 1;
    auto last_dot_pos = filepath.rfind('.');
    auto count = last_dot_pos == std::string::npos ? filepath.size() - last_slash_pos : last_dot_pos - last_slash_pos;
    m_name = filepath.substr(last_slash_pos, count);
}

OpenGL_Shader::OpenGL_Shader(const std::string& name, const std::string& vertex_source, const std::string& fragment_source)
    : m_name(name)
{
    std::unordered_map<u32, std::string> sources;
    sources[GL_VERTEX_SHADER] = vertex_source;
    sources[GL_FRAGMENT_SHADER] = fragment_source;
    compile(sources);
}

OpenGL_Shader::~OpenGL_Shader()
{
    glDeleteProgram(m_program_id);
}

void OpenGL_Shader::compile(const std::unordered_map<u32, std::string>& shader_sources)
{
    m_program_id = glCreateProgram();
    std::array<u32, 2> gl_shader_ids;

    int gl_shader_index = 0;
    for (auto& kv : shader_sources) {
        GLenum type = kv.first;
        const std::string& source = kv.second;

        GLuint shader = glCreateShader(type);

        const GLchar* cstr_source = source.c_str();
        glShaderSource(shader, 1, &cstr_source, 0);

        glCompileShader(shader);

        GLint is_compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
        if (is_compiled == GL_FALSE) {
            GLint max_length = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

            std::vector<GLchar> info_log(max_length);
            glGetShaderInfoLog(shader, max_length, &max_length, &info_log[0]);

            glDeleteShader(shader);

            CORE_LOG_ERROR("{0}", info_log.data());
            CORE_ASSERT(false, "Shader compilation failure!");
            break;
        }

        glAttachShader(m_program_id, shader);
        gl_shader_ids[gl_shader_index++] = shader;
    }

    glLinkProgram(m_program_id);

    GLint is_linked = 0;
    glGetProgramiv(m_program_id, GL_LINK_STATUS, (int*)&is_linked);
    if (is_linked == GL_FALSE) {
        GLint max_length = 0;
        glGetProgramiv(m_program_id, GL_INFO_LOG_LENGTH, &max_length);

        // The maxLength includes the NULL character
        std::vector<GLchar> info_log(max_length);
        glGetProgramInfoLog(m_program_id, max_length, &max_length, &info_log[0]);

        glDeleteProgram(m_program_id);

        for (auto id : gl_shader_ids)
            glDeleteShader(id);

        CORE_LOG_ERROR("{0}", info_log.data());
        CORE_ASSERT(false, "Shader link failure!");
        return;
    }

    for (auto id : gl_shader_ids) {
        glDetachShader(m_program_id, id);
        glDeleteShader(id);
    }
}

void OpenGL_Shader::bind() const
{
    glUseProgram(m_program_id);
}

void OpenGL_Shader::unbind() const
{
    glUseProgram(0);
}

GLint OpenGL_Shader::uniform_location(const std::string& name)
{
    GLint location;
    auto it = m_uniform_locations.find(name);

    if (it == m_uniform_locations.cend()) {
        location = glGetUniformLocation(m_program_id, name.c_str());
        CORE_LOG_TRACE("Uniform Location '{}' = {}", name, location);
        m_uniform_locations.insert({ name, location });
    } else
        location = it->second;

    return location;
}

void OpenGL_Shader::set_int(const std::string& name, i32 value)
{
    glUniform1i(OpenGL_Shader::uniform_location(name), value);
}

void OpenGL_Shader::set_int_array(const std::string& name, const i32* const values, u32 count)
{
    glUniform1iv(OpenGL_Shader::uniform_location(name), count, values);
}

void OpenGL_Shader::set_float(const std::string& name, float value)
{
    glUniform1f(OpenGL_Shader::uniform_location(name), value);
}

void OpenGL_Shader::set_float2(const std::string& name, const glm::vec2& value)
{
    glUniform2f(OpenGL_Shader::uniform_location(name), value.x, value.y);
}

void OpenGL_Shader::set_float3(const std::string& name, const glm::vec3& value)
{
    glUniform3f(
        OpenGL_Shader::uniform_location(name),
        value.x, value.y, value.z);
}

void OpenGL_Shader::set_float4(const std::string& name, const glm::vec4& value)
{
    glUniform4f(
        OpenGL_Shader::uniform_location(name),
        value.x, value.y, value.z, value.w);
}

void OpenGL_Shader::set_mat3(const std::string& name, const glm::mat3& matrix)
{
    glUniformMatrix3fv(
        OpenGL_Shader::uniform_location(name),
        1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGL_Shader::set_mat4(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(
        OpenGL_Shader::uniform_location(name),
        1, GL_FALSE, glm::value_ptr(matrix));
}

} // namespace Reme
