#pragma once

#include <memory>

#include <glm.hpp>
#include <ray.hpp>
#include <aabb.hpp>
#include <material.hpp>

// A struct defining a ray hit
struct RayHit {
    float distance; // The distance from the origin of the ray to the hit point.
    glm::vec3 normal; // The surface normal at the hit point.
    std::weak_ptr<Material> material; // The surface material at the hit point.
};

// The base class of all shapes
class Shape {
public:
    Shape(const std::shared_ptr<Material>& material) : material(material) {}
    inline AABB get_bounds() const { return bounds; }
    
    // Intersects a ray with the shape and returns true if the ray intersects it.
    // hit will contain the hit information if the ray intersects the shape.
    virtual bool intersect(const Ray& ray, RayHit& hit) const = 0;

protected:
    std::shared_ptr<Material> material; // The material of the shape.
    AABB bounds; // The AABB encompassing the shape.
};

// A 3D triangle shape
class Triangle : public Shape {
public:
    Triangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const std::shared_ptr<Material>& material);
    bool intersect(const Ray& ray, RayHit& hit) const override;
private:
    // The three vertices of the triangle.
    glm::vec3 v0, v1, v2;
};

// A sphere shape
class Sphere : public Shape {
public:
    Sphere(const glm::vec3& center, float radius, const std::shared_ptr<Material>& material);
    bool intersect(const Ray& ray, RayHit& hit) const override;
private:
    // The center and radius of the sphere.
    glm::vec3 center;
    float radius;
};