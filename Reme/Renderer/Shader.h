#pragma once

#include <Reme/Core/Asset.h>

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

namespace Reme {

class Shader : public Asset {
public:
    static RefPtr<Shader> create(const std::string& filepath);
    static RefPtr<Shader> create(const std::string& name, const std::string& vertex_shader, const std::string& fragment_shader);

public:
    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void set_int(const std::string& name, i32 value) = 0;
    virtual void set_int_array(const std::string& name, const i32* const values, u32 count) = 0;
    virtual void set_float(const std::string& name, float value) = 0;
    virtual void set_float2(const std::string& name, const glm::vec2& value) = 0;
    virtual void set_float3(const std::string& name, const glm::vec3& value) = 0;
    virtual void set_float4(const std::string& name, const glm::vec4& value) = 0;

    virtual void set_mat3(const std::string& name, const glm::mat3& matrix) = 0;
    virtual void set_mat4(const std::string& name, const glm::mat4& matrix) = 0;

    virtual const std::string& name() const = 0;

    virtual const char* class_name() const override { return "Shader"; }
};

} // namespace Reme
