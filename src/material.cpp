#include "material.hpp"

#include <gtc/constants.hpp>

// Sample a random uniform value between 0 and 1.
static float sample_uniform_01() {
    return static_cast<float>(rand()) / RAND_MAX;
}

// Sample a random point on a unit sphere's surface.
glm::vec3 sample_sphere_surface() {
    float z = sample_uniform_01() * 2.0f - 1.0f;
    float theta = sample_uniform_01() * glm::pi<float>() * 2.0f;

    float sqrt_1_z = glm::sqrt(1.0f - z * z);
    float x = sqrt_1_z * glm::cos(theta);
    float y = sqrt_1_z * glm::sin(theta);
    return glm::vec3(x, y, z);
}

MaterialSample EmissiveMaterial::sample(const glm::vec3& incoming_ray_direction, const glm::vec3& hit_point, const glm::vec3& hit_normal) const {
    return {
        .outgoing_ray_direction = incoming_ray_direction, // It doesn't matter since path tracing should stop at this point (because factor will become 0).
        .factor = Colors::BLACK, // This object doesn't relfect light from anywhere, so its factor is zero.
        .emission = light // This object emits it's light equally in all directions.
    };
}

MaterialSample LambertMaterial::sample(const glm::vec3& incoming_ray_direction, const glm::vec3& hit_point, const glm::vec3& hit_normal) const {
    //TODO: Implement this function
    // Hints:
    // - Refer to the slides to see how we can sample a new ray direction.
    // - Before you normalize a direction vector, Make sure that it was not zero.
    return {
        .outgoing_ray_direction = incoming_ray_direction,
        .factor = Colors::BLACK,
        .emission = Colors::BLACK
    };
}

MaterialSample SmoothMetalMaterial::sample(const glm::vec3& incoming_ray_direction, const glm::vec3& hit_point, const glm::vec3& hit_normal) const {
    //TODO: Implement this function
    // Hints:
    // - If you sample rays here as we learned in the lecture, you will get a very noisy result on smooth metallic surface.
    //   Instead, just focus on reflecting the ray by the surface normal, and compute the factor using Schlick's approximation of Fresnel reflection.
    return {
        .outgoing_ray_direction = incoming_ray_direction,
        .factor = Colors::BLACK,
        .emission = Colors::BLACK
    };
}