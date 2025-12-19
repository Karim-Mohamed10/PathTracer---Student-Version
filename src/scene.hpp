#pragma once

#include <ray.hpp>
#include <color.hpp>
#include <shapes.hpp>
#include <camera.hpp>
#include <backgrounds.hpp>
#include <bvh.hpp>

#include <vector>

// A scene class containing a camera, a list of shapes, and a background.
// Optionally, it also contains a BVH for efficient intersection testing.
class Scene {
public:
    // Setters and getters
    inline std::shared_ptr<Background> get_background() const { return background; }
    inline void set_background(const std::shared_ptr<Background>& background) { this->background = background; }
    inline Camera& get_camera() { return camera; }
    inline const Camera& get_camera() const { return camera; }
    inline void set_camera(const Camera& camera) { this->camera = camera; }
    inline bool get_use_bvh() const { return use_bvh; }
    inline void set_use_bvh(bool value) { this->use_bvh = value; }

    // Checks for ray intersections with any of the shapes in the scene.
    // If use_bvh was true when the scene was constructed, this will use the BVH to speed up intersection testing.
    bool intersect(const Ray& ray, RayHit& hit) const;
    
    // Get the color of the background in the given direction.
    Color sample_background(const glm::vec3& direction) const;

     // Call before adding any shape.
    void start_construction();
    // Call after adding all shapes.
    // If use_bvh was true, this function will construct the BVH.
    void finish_construction(); 

    // Functions for adding shapes.
    // Note: "angles" define rotation as euler angles (Yaw, Pitch, Roll) in radians where the vector contains (Pitch, Roll, Yaw). 
    void add_shape(std::shared_ptr<Shape> shape);
    void add_sphere(const std::shared_ptr<Material>& material, const glm::vec3& center, float radius);
    void add_triangle(const std::shared_ptr<Material>& material, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2);
    void add_rectangle(const std::shared_ptr<Material>& material, const glm::vec3& center, const glm::vec2& size, const glm::vec3& angles = glm::vec3(0.0f));
    void add_cuboid(const std::shared_ptr<Material>& material, const glm::vec3& center, const glm::vec3& size, const glm::vec3& angles = glm::vec3(0.0f));


private:
    Camera camera;
    std::shared_ptr<Background> background;
    std::vector<std::shared_ptr<Shape>> shapes;
    std::shared_ptr<BVHNode> root;
    bool use_bvh = false;
};