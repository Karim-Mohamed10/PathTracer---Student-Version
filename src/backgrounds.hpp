#pragma once

#include <glm.hpp>
#include <color.hpp>

// The base class for all backgrounds.
// It is used to sample a color from the background based on the given direction.
class Background {
public:
    // Given a direction from the camera to a point on the background, return the color at that point.
    virtual Color sample(glm::vec3 direction) = 0;
};

// A simple background that returns a constant color everywhere.
class SimpleBackground : public Background {
public:
    SimpleBackground(Color color) : color(color) {}
    Color sample(glm::vec3 direction) override;
private:
    Color color;
};

// A simplified sky background that returns a gradient of colors based on the direction, then adds a sun over it.
class SkyBackground : public Background {
public:
    // The sky color is defined as a gradient from the top to bottom using the colors in order [top, horizon, bottom].
    // Then a sun with the sun color is added over the sky in the given direction. The sun size is defined by the sun angle and feathering.
    SkyBackground(
        Color top, Color horizon, Color bottom, 
        Color sun, glm::vec3 sun_direction, float sun_angle = glm::radians(1.0f), float sun_feathering = glm::radians(1.0f)
    );
    Color sample(glm::vec3 direction) override;
private:
    Color top, horizon, bottom, sun;
    glm::vec2 sun_cos_angles;
    glm::vec3 sun_direction;
};