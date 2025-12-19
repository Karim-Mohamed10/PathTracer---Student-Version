#include "backgrounds.hpp"

Color SimpleBackground::sample(glm::vec3 direction) {
    return color;
}

SkyBackground::SkyBackground(
    Color top, Color horizon, Color bottom, 
    Color sun, glm::vec3 sun_direction, float sun_angle, float sun_feathering
) : top(top), horizon(horizon), bottom(bottom), sun(sun) {
    
    // Normalize the sun direction to make sure our calculations work correctly.
    this->sun_direction = glm::normalize(sun_direction);
    // Precompute the cosines of the inner and other sun angle.
    this->sun_cos_angles = glm::vec2(
        cos((sun_angle - sun_feathering) * 0.5f), 
        cos((sun_angle + sun_feathering) * 0.5f)
    );
}

Color SkyBackground::sample(glm::vec3 direction) {
    // First, we sample the sky color from the gradient defined by [top, horizon, bottom].
    Color sky = glm::mix(horizon, (direction.y > 0.0f ? top : bottom), direction.y * direction.y);
    // Then we mix it with the sun color if the ray is facing towards the sun.
    float sun_mixing_factor = glm::smoothstep(sun_cos_angles.y, sun_cos_angles.x, glm::dot(direction, sun_direction));
    return glm::mix(sky, sun, sun_mixing_factor);
}