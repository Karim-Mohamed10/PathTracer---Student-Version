#include "aabb.hpp"

AABB AABB::merge(const AABB& other) const {
    return {glm::min(vmin, other.vmin), glm::max(vmax, other.vmax)};
}

bool AABB::intersect_ray(const Ray& ray, float& hit_distance) const {
    // Ray vs AABB using the Slab Method
    glm::vec3 frac = 1.0f / ray.direction;
    float tx0 = (vmin.x - ray.origin.x)*frac.x;
    float tx1 = (vmax.x - ray.origin.x)*frac.x;
    float ty0 = (vmin.y - ray.origin.y)*frac.y;
    float ty1 = (vmax.y - ray.origin.y)*frac.y;
    float tz0 = (vmin.z - ray.origin.z)*frac.z;
    float tz1 = (vmax.z - ray.origin.z)*frac.z;
    float tmin = glm::max(glm::max(glm::min(tx0, tx1), glm::min(ty0, ty1)), glm::min(tz0, tz1));
    float tmax = glm::min(glm::min(glm::max(tx0, tx1), glm::max(ty0, ty1)), glm::max(tz0, tz1));
    if (tmax < 0) return false; // AABB is behind us
    if (tmin > tmax) return false; // no intersection
    hit_distance = tmin;
    return true;
}

float AABB::compute_surface_area() const {
    glm::vec3 size = vmax - vmin;
    return 2 * (size.x * size.y + size.y * size.z + size.z * size.x);
}