#include "bvh.hpp"

#include <vector>
#include <algorithm>

BVHNode::BVHNode() {
    this->left = this->right = nullptr;
    this->shapes = {};
}

BVHNode::BVHNode(std::span<std::shared_ptr<Shape>> shapes) {
    build(shapes);
}

void BVHNode::build(std::span<std::shared_ptr<Shape>> shapes) {
    this->left = this->right = nullptr;
    this->shapes = {};
    if(shapes.size() == 0) return;
    // Compute the AABB of this node.
    bounds = shapes[0]->get_bounds();
    for(int i = 1; i < shapes.size(); ++i)
        bounds = bounds.merge(shapes[i]->get_bounds());
    // Call the internal build function to take the work from here.
    _build(shapes, bounds);
}

bool BVHNode::intersect_ray(const Ray& ray, RayHit& hit) const {
    hit.distance = std::numeric_limits<float>::max();
    float t;
    // The ray doesn't hit this node's AABB, we can skip it.
    if(!bounds.intersect_ray(ray, t)) return false;
    // Call the internal intersect function to take the work from here.
    return _intersect_ray(ray, hit);
}

void BVHNode::_build(std::span<std::shared_ptr<Shape>> shapes, AABB bounds) {
    this->bounds = bounds;
    // We stop the construction if the remaining shape count is 1 or 0.
    if(shapes.size() <= 1) {
        this->shapes = shapes;
        left = right = nullptr;
        return;
    }

    // Select the splitting dimension. We choose the dimension with the maximum length on the AABB.
    glm::vec3 aabb_size = bounds.vmax - bounds.vmin;
    int split_dim = 0;
    if(aabb_size[1] > aabb_size[split_dim]) split_dim = 1;
    if(aabb_size[2] > aabb_size[split_dim]) split_dim = 2;

    // We sort the shapes along the splitting dimension, so that we can split later by just taking slices.
    std::sort(shapes.begin(), shapes.end(), [split_dim](const auto& a, const auto& b) { 
        return a->get_bounds().vmin[split_dim] < b->get_bounds().vmin[split_dim]; 
    });

    // At each possible splitting point, we compute that the AABBs for both sides of the split.  
    std::vector<AABB> aabbs_left, aabbs_right;
    aabbs_left.resize(shapes.size());
    aabbs_left[0] = shapes[0]->get_bounds();
    for(int i = 1; i < shapes.size(); ++i) aabbs_left[i] = aabbs_left[i-1].merge(shapes[i]->get_bounds());
    aabbs_right.resize(shapes.size());
    aabbs_right[shapes.size()-1] = shapes[shapes.size()-1]->get_bounds();
    for(int i = shapes.size()-2; i >= 0; --i) aabbs_right[i] = aabbs_right[i+1].merge(shapes[i]->get_bounds());

    // We will select the splitting point using the Surface Area Heuristic (SAH)
    // Initially, the best choice is not the split and it is cost is the SAH of this node.
    int best_split_point = 0;
    float best_cost = shapes.size() * bounds.compute_surface_area();
    // Then we loop over the split points, compute the SAH, and check if it is better than our current choice.
    for(int split_point = 1; split_point < shapes.size() - 1; split_point++) {
        AABB aabb_left = aabbs_left[split_point-1];
        AABB aabb_right = aabbs_right[split_point];
        float cost = split_point * aabb_left.compute_surface_area() + (shapes.size() - split_point) * aabb_right.compute_surface_area();
        if(cost < best_cost) {
            best_cost = cost;
            best_split_point = split_point;
        }
    }

    if(best_split_point == 0) {
        // If not splitting is still the best option based on SAH, we make this a leaf node.
        this->shapes = shapes;
        left = right = nullptr;
    } else {
        // Otherwise, we split the shapes at the splitting point, recursively construct two children, one for each split.
        left = std::make_shared<BVHNode>();
        left->_build(shapes.subspan(0, best_split_point), aabbs_left[best_split_point-1]);
        right = std::make_shared<BVHNode>();
        right->_build(shapes.subspan(best_split_point), aabbs_right[best_split_point]);
        this->shapes = {};
    }
}

bool BVHNode::_intersect_ray(const Ray& ray, RayHit& hit) const {
    // Note: we assume the hit.distance constains the best hit distance found till now while traversing the BVH.
    if(left) { // If left (or right) is not null, then this is not a leaf node.
        // First, we check if the ray intersects the AABBs of the children and if they yield a closer intersection than the current best.
        float left_dist;
        bool left_hit = left->bounds.intersect_ray(ray, left_dist) && left_dist < hit.distance;
        float right_dist;
        bool right_hit = right->bounds.intersect_ray(ray, right_dist) && right_dist < hit.distance;

        if(left_hit && right_hit) {
            // If it hits both, we start at the child with the closer AABB hit first,
            // since it may yield a hit that occludes the other child's AABB, so we can skip the other child; 
            if(left_dist < right_dist) {
                // Intersect ray with left child first.
                left_hit = left->_intersect_ray(ray, hit);
                // If the best hit distance is still farther than the right child's AABB hit, 
                // we intersect the ray with the right child.
                if(right_dist < hit.distance) {
                    right_hit = right->_intersect_ray(ray, hit);    
                }
                return left_hit || right_hit;
            } else {
                // Intersect ray with left child first.
                right_hit = right->_intersect_ray(ray, hit);
                // If the best hit distance is still farther than the left child's AABB hit, 
                // we intersect the ray with the left child.
                if(left_dist < hit.distance) {
                    left_hit = left->_intersect_ray(ray, hit);    
                }
                // Return true if either child was a hit.
                return left_hit || right_hit;
            }
        } else if(left_hit) {
            // If only the left AABBs intersected the ray, intersect ray with left child only.
            return left->_intersect_ray(ray, hit);
        } else if(right_hit) {
            // If only the right AABBs intersected the ray, intersect ray with right child only.
            return right->_intersect_ray(ray, hit);
        } else {
            // No hit
            return false;
        }
    } else {
        // If this is a child node, we loop over the shapes and intersect the ray against them.
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