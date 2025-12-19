#pragma once

#include <image.hpp>
#include <scene.hpp>

// Pathtraces the scene and returns an image of the rendered scene.
// The number of samples per pixel is given by `sample_count`, and each ray can bounce at most `max_bounces` times before being discarded.
Image path_trace(const Scene& scene, uint32_t sample_count, uint32_t max_bounces);

// Some debug drawing functions
Image debug_draw_hit_distance(const Scene& scene);
Image debug_draw_hit_normal(const Scene& scene);