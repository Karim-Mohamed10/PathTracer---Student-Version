#pragma once

#include <glm.hpp>
#include <ray.hpp>

// An Axis Aligned Bounding Box (AABB) which defines a region of space between vmin and vmax.
// This will be used to define the BVH
struct AABB {
    glm::vec3 vmin, vmax;

    // Generate an AABB that encompasses this AABB and the other AABB.
    AABB merge(const AABB& other) const;
    // Intersect a ray with the bounding box. Returns true if the ray intersects the AABB and the distance to the hit.
    bool intersect_ray(const Ray& ray, float& hit_distance) const;
    // Compute the surface area of the AABB.
    float compute_surface_area() const;
};