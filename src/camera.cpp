#include "camera.hpp"

Camera::Camera() {
    // Default camera parameters
    viewport_size = glm::ivec2(1, 1);
    e = glm::vec3(0.0f);
    u = glm::vec3(1.0f, 0.0f, 0.0f);
    v = glm::vec3(0.0f, 1.0f, 0.0f);
    w = glm::vec3(0.0f, 0.0f, 1.0f);
    l = b = -1.0f; t = b = 1.0f;
    d = 1.0f;
}

Camera::Camera(glm::vec3 center, glm::vec3 look_at, glm::vec3 up, float fovy, glm::ivec2 viewport_size) {
    this->viewport_size = viewport_size;
    this->e = center;
    // Compute the u, v, w directions from the given arguments
    w = glm::normalize(center - look_at);
    u = glm::normalize(glm::cross(up, w));
    v = glm::cross(w, u);
    // Compute the left, right, bottom, top and near values from the given arguments. 
    d = 1.0f; // We assume the near plane is always at distance 1.0f from the camera.
              // Normally, this is a large value, but in a path tracing, 
              // we can hit & see objects closer than the near plane, so it is not an issue.
    t = d * tan(fovy / 2.0f);
    b = -t;
    float aspect_ratio = static_cast<float>(viewport_size.x) / viewport_size.y;
    r = aspect_ratio * t;
    l = -r;
}

Ray Camera::get_ray(glm::vec2 pixel_pos) const {
    //TODO: Get ray for a given position in pixel space.
    // Note: the given pixel position is defined with floats, since it will be used for sub-pixel sampling.
    // So, if the ray should pass through the center of pixel (i,j), this function will receive (i+0.5, j+0.5).
    return {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, -1.0f)
    };
}