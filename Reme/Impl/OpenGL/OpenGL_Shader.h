#pragma once

#include <Reme/Renderer/Shader.h>

#include <glm/glm.hpp>

#include <string>
#include <unordered_map>

namespace Reme {

class OpenGL_Shader : public Shader {
public:
    OpenGL_Shader(const std::string& filePath);
    OpenGL_Shader(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader);
    virtual ~OpenGL_Shader() override;

    void bind() const override;
    void unbind() const override;

    void set_int(const std::string& name, i32 value) override;
    void set_int_array(const std::string& name, const i32* const values, u32 count) override;

    void set_float(const std::string& name, float value) override;
    void set_float2(const std::string& name, const glm::vec2& value) override;
    void set_float3(const std::string& name, const glm::vec3& value) override;
    void set_float4(const std::string& name, const glm::vec4& value) override;

    void set_mat3(const std::string& name, const glm::mat3& matrix) override;
    void set_mat4(const std::string& name, const glm::mat4& matrix) override;

    const std::string& name() const override { return m_name; }

private:
    i32 uniform_location(const std::string& name);
    void compile(const std::unordered_map<u32, std::string>& shader_sources);

private:
    u32 m_program_id;
    std::string m_name;
    std::unordered_map<std::string, i32> m_uniform_locations;
};

} // namespace Reme
