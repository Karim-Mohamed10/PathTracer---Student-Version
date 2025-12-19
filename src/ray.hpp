#pragma once

#include <glm.hpp>

// A basic ray structure containing the origin point of the ray and its direction vector.
struct Ray {
    glm::vec3 origin, direction;
};