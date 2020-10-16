#pragma once

#include <Reme/Core/Core.h>
#include <Reme/Renderer/Camera.h>

namespace Reme {

class OrthographicCamera : public Camera {
public:
    static RefPtr<OrthographicCamera> DEFAULT;

    OrthographicCamera(float left, float right, float bottom, float top);
    void set_projection(float left, float right, float bottom, float top);

    void set_position(const glm::vec3& pos)
    {
        m_position = pos;
        recalculate_matrix();
    };

    void set_rotation(float rot)
    {
        m_rotation = rot;
        recalculate_matrix();
    };

    float rotation() const { return m_rotation; };
    const glm::vec3& position() const { return m_position; };
    const glm::mat4& view_matrix() const override { return m_view_matrix; };
    const glm::mat4& projection_matrix() const override { return m_projection_matrix; };

private:
    void recalculate_matrix();
    glm::mat4 m_projection_matrix;
    glm::mat4 m_view_matrix;

    glm::vec3 m_position;
    float m_rotation = 0.0f;
};

} // namespace Reme
