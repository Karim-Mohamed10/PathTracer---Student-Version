#include "pathtracer.hpp"

#include <glm.hpp>
#include <gtc/constants.hpp>

#include <cstdlib>
#include <iostream>

// Sample a random uniform value between 0 and 1.
static float sample_uniform_01() {
    return static_cast<float>(rand()) / RAND_MAX;
}

// Pathtraces the scene and updates the image with the rendered scene.
// The number of samples per pixel here is just 1, and each ray can bounce at most `max_bounces` times before being discarded.
void path_trace_1spp(Image& image, const Scene& scene, uint32_t max_bounces) {
    //TODO: Write a path tracers that traces 1 sample per pixel.
    // Note: Cast the ray from the random point inside the pixel to apply Anti-aliasing.
    // Hints: When casting a new ray from the hit point, move it slightly away from the hit point to avoid self-intersection. 
    //        For example, you can move the new ray origin from the hit point a distance of 0.0001 in the new ray direction. 
}

// Pathtraces the scene and returns an image of the rendered scene.
// The number of samples per pixel is given by `sample_count`, and each ray can bounce at most `max_bounces` times before being discarded.
Image path_trace(const Scene& scene, uint32_t sample_count, uint32_t max_bounces) {
    srand(time(NULL));

    glm::ivec2 viewport_size = scene.get_camera().get_viewport_size();
    Image final_image(viewport_size.x, viewport_size.y); // The image containing the average of all the samples
    Image sample_image(viewport_size.x, viewport_size.y); // The image containing the current sample only

    for(uint32_t sample = 0; sample < sample_count; ++sample) {
        // Trace 1 sample per pixel into the scene
        path_trace_1spp(sample_image, scene, max_bounces);
        // Mix new sample image into the final image
        float lr = 1.0f / (1.0f + sample);
        for(int y = 0; y < viewport_size.y; ++y) {
            for(int x = 0; x < viewport_size.x; ++x) {
                final_image(x, y) = glm::mix(final_image(x, y), sample_image(x, y), lr);
            }
        }
        // Print progress
        std::cout << "\rSample: " << sample + 1 << "/" << sample_count << std::flush;
    }

    std::cout << std::endl;
    return final_image;
}

////////////////////////////
// Debug Drawing Function //
////////////////////////////

template<typename F>
Image debug_draw(const Scene& scene, Color default_color, F&& color_fn) {
    const Camera& camera = scene.get_camera();
    glm::ivec2 viewport_size = camera.get_viewport_size();
    Image image(viewport_size.x, viewport_size.y);
    for(int y = 0; y < viewport_size.y; ++y) {
        for(int x = 0; x < viewport_size.x; ++x) {
            Ray ray = camera.get_ray(glm::vec2(x + sample_uniform_01(), y + sample_uniform_01()));
            RayHit hit;
            Color color = default_color;
            if(scene.intersect(ray, hit)) {
                color = color_fn(hit);
            }
            image(x, y) = color;
        }
    }
    return image;
}

Image debug_draw_hit_distance(const Scene& scene) {
    return debug_draw(scene, Color(1000000.0f), [](const RayHit& hit) {
        return Color(hit.distance * 0.1f);
    });
}

Image debug_draw_hit_normal(const Scene& scene) {
    return debug_draw(scene, Color(1000000.0f), [](const RayHit& hit) {
        return hit.normal * 0.5f + 0.5f;
    });
}