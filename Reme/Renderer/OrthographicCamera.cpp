#include <Reme/Renderer/OrthographicCamera.h>

#include <glm/gtc/matrix_transform.hpp>

namespace Reme {

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    : m_projection_matrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
    , m_view_matrix(1.0f)
    , m_position(0.0f, 0.0f, 0.0f)
    , m_rotation(0.0f)
{
}

void OrthographicCamera::set_projection(float left, float right, float bottom, float top)
{
    m_projection_matrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
}

void OrthographicCamera::recalculate_matrix()
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0, 0, 1));
    m_view_matrix = glm::inverse(transform);
}

} // namespace Reme
