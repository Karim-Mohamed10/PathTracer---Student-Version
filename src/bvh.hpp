#pragma once

#include <span>
#include <memory>

#include <ray.hpp>
#include <shapes.hpp>

// A Bounding Volume Hierarchy (BVH) node which contains a bounding box and either a list of shapes or two child BVH nodes.
class BVHNode {
public:
    // Construct an Empty BVH node (you can call build later to construct it from shapes).
    BVHNode();
    // Construct a BVH node from a list of shapes (Similar to calling the default constructor then build).
    // Warning: this function will probably reorder the shapes in the given span.
    BVHNode(std::span<std::shared_ptr<Shape>> shapes);

    // Builds a BVH from a list of shapes.
    // Warning: this function will probably reorder the shapes in the given span.
    void build(std::span<std::shared_ptr<Shape>> shapes);
    // Intersects the ray with the BVH and returns true if the ray intersects any of the shapes in the BVH.
    bool intersect_ray(const Ray& ray, RayHit& hit) const;

private:
    AABB bounds; // the AABB of the shape.
    std::shared_ptr<BVHNode> left, right; // The two children BVH nodes (we be null in leaf nodes).
    std::span<std::shared_ptr<Shape>> shapes; // The shapes in this node (will be empty except in leaf nodes).

    // Internal functions.
    void _build(std::span<std::shared_ptr<Shape>> shapes, AABB bounds);
    bool _intersect_ray(const Ray& ray, RayHit& hit) const;
};