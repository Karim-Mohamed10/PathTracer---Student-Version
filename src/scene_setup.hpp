#pragma once

#include <scene.hpp>

#include <string>

void setup_triangle_test_scene(Scene& scene, int width, int height, int version);
void setup_sphere_test_scene(Scene& scene, int width, int height, int version);

void setup_balls_scene(Scene& scene, int version);
void setup_city_scene(Scene& scene, int version);
void setup_cornell_box_scene(Scene& scene, int version);
void setup_special_scene(Scene& scene, const std::string& name);