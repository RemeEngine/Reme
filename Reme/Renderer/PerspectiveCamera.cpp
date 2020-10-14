#include <Reme/Renderer/PerspectiveCamera.h>

#include <glm/gtc/matrix_transform.hpp>

namespace Reme {

PerspectiveCamera::PerspectiveCamera(const glm::vec3& position, const glm::vec3& up, float yaw, float pitch)
    : m_front(glm::vec3(0.0f, 0.0f, -1.0f))
    , m_position(position)
    , m_world_up(up)
    , m_yaw(yaw)
    , m_pitch(pitch)
    , m_fov(45.0f)
    , m_aspect_ratio(1.0)
{
    recalculate_matrix();
}

void PerspectiveCamera::recalculate_matrix()
{
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);

    // Also re-calculate the Right and Up vector
    // Normalize the vectors, because their length gets closer to 0
    // the more you look up or down which results in slower movement.
    m_right = glm::normalize(glm::cross(m_front, m_world_up));
    m_up = glm::normalize(glm::cross(m_right, m_front));

    m_view_matrix = glm::lookAt(m_position, m_position + m_front, m_up);
    m_projection_matrix = glm::perspective(glm::radians(m_fov), m_aspect_ratio, 0.1f, 100.0f);
}

} // namespace Reme
