#include "scene.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/euler_angles.hpp>

bool Scene::intersect(const Ray& ray, RayHit& hit) const {
    if(root != nullptr) { 
        // If the BVH is defined, use it.
        return root->intersect_ray(ray, hit);
    } else { 
        // Otherwise, loop over the shapes and test for intersection with them one-by-one.
        hit.distance = std::numeric_limits<float>::max();
        bool has_hit = false;
        for(auto shape: shapes) {
            RayHit shape_hit;
            if(shape->intersect(ray, shape_hit) && shape_hit.distance < hit.distance) {
                has_hit = true;
                hit = shape_hit;
            }
        }
        return has_hit;
    }
}

void Scene::start_construction() {
    // Clears the list of shapes and the BVH.
    shapes.clear();
    root = nullptr;
}

void Scene::finish_construction() {
    // Constructs the BVH if use_bvh is true.
    if(use_bvh) {
        root = std::make_shared<BVHNode>(shapes);
    } else {
        root = nullptr;
    }
}

Color Scene::sample_background(const glm::vec3& direction) const {
    // Samples the background color in the given direction if the background exists. Otherwise, returns black.
    return background ? background->sample(direction) : Colors::BLACK;
}

//////////////////////////////////////////
// Functions to add shapes to the scene //
//////////////////////////////////////////

void Scene::add_shape(std::shared_ptr<Shape> shape) {
    shapes.push_back(shape);
}

void Scene::add_sphere(const std::shared_ptr<Material>& material, const glm::vec3& center, float radius) {
    add_shape(std::make_shared<Sphere>(center, radius, material));
}

void Scene::add_triangle(const std::shared_ptr<Material>& material, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2) {
    add_shape(std::make_shared<Triangle>(v0, v1, v2, material));
}

void Scene::add_rectangle(const std::shared_ptr<Material>& material, const glm::vec3& center, const glm::vec2& size, const glm::vec3& angles) {
    glm::mat3 rot = glm::orientate3(angles);
    glm::vec2 half_size = size / 2.0f;
    glm::vec3 verts[] = {
        center + rot * glm::vec3(-half_size.x, 0, -half_size.y),
        center + rot * glm::vec3(-half_size.x, 0,  half_size.y),
        center + rot * glm::vec3( half_size.x, 0, -half_size.y),
        center + rot * glm::vec3( half_size.x, 0,  half_size.y)
    };
    add_triangle(material, verts[0], verts[1], verts[3]);
    add_triangle(material, verts[0], verts[2], verts[3]);
}

void Scene::add_cuboid(const std::shared_ptr<Material>& material, const glm::vec3& center, const glm::vec3& size, const glm::vec3& angles) {
    glm::mat3 rot = glm::orientate3(angles);
    glm::vec3 half_size = size / 2.0f;
    glm::vec3 verts[] = {
        center + rot * glm::vec3(-half_size.x, -half_size.y, -half_size.z),
        center + rot * glm::vec3(-half_size.x, -half_size.y,  half_size.z),
        center + rot * glm::vec3( half_size.x, -half_size.y, -half_size.z),
        center + rot * glm::vec3( half_size.x, -half_size.y,  half_size.z),
        center + rot * glm::vec3(-half_size.x,  half_size.y, -half_size.z),
        center + rot * glm::vec3(-half_size.x,  half_size.y,  half_size.z),
        center + rot * glm::vec3( half_size.x,  half_size.y, -half_size.z),
        center + rot * glm::vec3( half_size.x,  half_size.y,  half_size.z),
    };
    // Bottom
    add_triangle(material, verts[0], verts[1], verts[3]);
    add_triangle(material, verts[0], verts[2], verts[3]);
    // Top
    add_triangle(material, verts[4], verts[5], verts[7]);
    add_triangle(material, verts[4], verts[6], verts[7]);
    // Back
    add_triangle(material, verts[0], verts[2], verts[6]);
    add_triangle(material, verts[0], verts[4], verts[6]);
    // Front
    add_triangle(material, verts[1], verts[3], verts[7]);
    add_triangle(material, verts[1], verts[5], verts[7]);
    // Left
    add_triangle(material, verts[0], verts[1], verts[5]);
    add_triangle(material, verts[0], verts[4], verts[5]);
    // Right
    add_triangle(material, verts[2], verts[3], verts[7]);
    add_triangle(material, verts[2], verts[6], verts[7]);
}