#pragma once

#include <glm.hpp>
#include <color.hpp>

// This struct will hold a sample from a material to be used by the path tracer.
struct MaterialSample {
    // The new ray direction starting from the hit point. The path tracer should trace a new ray starting from the hit point and moving in this direction.
    // It must be normalized.
    glm::vec3 outgoing_ray_direction;
    // The factor to be multiplied by the light coming from the outgoing ray's direction and going out into the incoming ray's direction.
    Color factor;
    // The light emitted by the material itself and going out into the incoming ray's direction.
    Color emission;
};

// Base class for all materials.
class Material {
public:
    // Returns a material sample given an incoming ray direction and its hit point & normal on the shape surface. 
    virtual MaterialSample sample(const glm::vec3& incoming_ray_direction, const glm::vec3& hit_point, const glm::vec3& hit_normal) const = 0;
};

// A simple emissive material that only emits light.
class EmissiveMaterial : public Material {
public:
    EmissiveMaterial(Color light) : light(light) {}
    MaterialSample sample(const glm::vec3& incoming_ray_direction, const glm::vec3& hit_point, const glm::vec3& hit_normal) const override;
private:
    Color light;
};

// A simple lambert material that scatters light equally in all directions of the hemisphere.
class LambertMaterial : public Material {
public:
    LambertMaterial(Color albedo) : albedo(albedo) {}
    MaterialSample sample(const glm::vec3& incoming_ray_direction, const glm::vec3& hit_point, const glm::vec3& hit_normal) const override;
private:
    Color albedo;
};

// A simple metallic material with a smooth surface that reflects light in the reflection direction.
class SmoothMetalMaterial : public Material {
public:
    SmoothMetalMaterial(Color specular) : specular(specular) {}
    MaterialSample sample(const glm::vec3& incoming_ray_direction, const glm::vec3& hit_point, const glm::vec3& hit_normal) const override;
private:
    Color specular;
};