#include "shapes.hpp"

Triangle::Triangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const std::shared_ptr<Material>& material) : 
    v0(v0), v1(v1), v2(v2), Shape(material) {
    // Compute the AABB for the triangle.
    bounds = {
        .vmin = glm::min(glm::min(v0, v1), v2), 
        .vmax = glm::max(glm::max(v0, v1), v2) 
    };
}

bool Triangle::intersect(const Ray& ray, RayHit& hit) const {
    //TODO: implement ray intersection test for triangle.
    // Remember to return the hit distance, normal and material in hit if the ray intersects the triangle. 
    return false;
}

Sphere::Sphere(const glm::vec3& center, float radius, const std::shared_ptr<Material>& material) : 
    center(center), radius(radius), Shape(material) 
{
    // Compute the AABB for the sphere
    bounds = { center - radius, center + radius };
}

bool Sphere::intersect(const Ray& ray, RayHit& hit) const {
    //TODO: Implement ray intersection test with sphere.
    // Remember to return the hit distance, normal and material in hit if the ray intersects the sphere.
    return false; 
}