#pragma once

#include <Reme/Renderer/Camera.h>

namespace Reme {

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(
        const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
        const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = -90.0f,
        float pitch = 0.0f);

    void set_position(const glm::vec3& pos)
    {
        m_position = pos;
        recalculate_matrix();
    };

    void set_world_up(const glm::vec3& up)
    {
        m_world_up = up;
        recalculate_matrix();
    };

    void set_yaw(float yaw)
    {
        m_yaw = yaw;
        recalculate_matrix();
    };

    void set_pitch(float pitch)
    {
        m_pitch = pitch;
        recalculate_matrix();
    };

    void set_fov(float fov)
    {
        m_fov = fov;
        recalculate_matrix();
    };

    void set_aspect_ratio(float ratio)
    {
        m_aspect_ratio = ratio;
        recalculate_matrix();
    };

    const glm::vec3& position() { return m_position; };
    const glm::vec3& world_up() { return m_world_up; };
    float yaw() { return m_yaw; };
    float pitch() { return m_pitch; };
    float fov() { return m_fov; };
    float aspect_ratio() { return m_aspect_ratio; };

    const glm::mat4& view_matrix() const override { return m_view_matrix; };
    const glm::mat4& projection_matrix() const override { return m_projection_matrix; };

private:
    void recalculate_matrix();

    glm::mat4 m_view_matrix;
    glm::mat4 m_projection_matrix;

    // Internal value for calculation
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;

    glm::vec3 m_position;
    glm::vec3 m_world_up;

    // Euler Angles
    float m_yaw;
    float m_pitch;

    // Field of view
    float m_fov;
    float m_aspect_ratio;
};

} // namespace Reme
