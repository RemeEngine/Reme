#pragma once

#include <glm/glm.hpp>

namespace Reme {

class Camera {
public:
    virtual ~Camera() {};

    virtual const glm::mat4& view_matrix() const = 0;
    virtual const glm::mat4& projection_matrix() const = 0;
};

} // namespace Reme
