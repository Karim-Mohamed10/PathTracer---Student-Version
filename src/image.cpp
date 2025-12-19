#include "image.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

void Image::save(const std::string& path) {
    std::vector<uint8_t> encoded(width * height * 4);

    for(size_t i = 0, j = 0; i < pixels.size(); ++i) {
        // Apply reinhard tonemapping
        Color color = tonemap_reinhard(pixels[i]);
        // Encode to non-linear sRGB color space
        ColorSRGB srgb = encode_srgb(color);
        encoded[j++] = srgb.r;
        encoded[j++] = srgb.g;
        encoded[j++] = srgb.b;
        encoded[j++] = 255;
    }
    
    stbi_flip_vertically_on_write(true);
    stbi_write_png(path.c_str(), width, height, 4, encoded.data(), width * 4);
}