#pragma once

#include <glm.hpp>
#include <ray.hpp>

// A camera class that defines the camera position, orientation, field of view and resolution.
class Camera {
public:
    // Construct a default camera which sits at the origin, looks in -Z, 
    // and it's up is +Y, with resolution 1x1 and a field of view of 90 degrees.
    Camera();

    // Construct a camera at center, looking at look_at, with its upwards vector pointing to up, and a vertical fov angle of fovy (in radians),
    // and a resolution equal viewport_size.
    Camera(glm::vec3 center, glm::vec3 look_at, glm::vec3 up, float fovy, glm::ivec2 viewport_size);
    // Get the viewport size (resolution)
    inline glm::ivec2 get_viewport_size() const { return viewport_size; }    
    
    // Get a ray from the eye through a pixel position on the viewport.
    // Note: the given pixel position is defined with floats, since it will be used for sub-pixel sampling.
    // So, if the ray should pass through the center of pixel (i,j), this function will receive (i+0.5, j+0.5).
    Ray get_ray(glm::vec2 pixel_pos) const;

private:
    glm::ivec2 viewport_size; // The viewport size (width and height of the renderer image)
    glm::vec3 e; // the position of the camera (eye)
    glm::vec3 u, v, w; // right, up & backward vectors
    float l, r, b, t, d; // the left, right, bottom & top of the near plane and the distance to the near plane.
};