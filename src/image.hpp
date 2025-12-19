#pragma once

#include <color.hpp>

#include <string>
#include <vector>

// A simple image class where each pixel is a Color in linear scene RGB color space
class Image {
public:
    Image(int width, int height) : width(width), height(height), pixels(width * height) {}

    // Access pixel by coordinates
    inline Color& operator()(int x, int y) { return pixels[y * width + x]; }
    inline Color operator()(int x, int y) const { return pixels[y * width + x]; }
    // Getters for dimensions
    inline int get_width() const { return width; }
    inline int get_height() const { return height; }
    
    // Save the image to a PNG file after applying tone mapping and gamma correction.
    void save(const std::string& path);

private:
    std::vector<Color> pixels;
    int width, height;
};