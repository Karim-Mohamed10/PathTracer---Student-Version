#pragma once

#include <glm.hpp>

// An RGB color where each channel is a 32-bit float
using Color = glm::vec3;

namespace Colors {
    static const Color BLACK   = Color(0.0f, 0.0f, 0.0f);
    static const Color WHITE   = Color(1.0f, 1.0f, 1.0f);
    static const Color RED     = Color(1.0f, 0.0f, 0.0f);
    static const Color GREEN   = Color(0.0f, 1.0f, 0.0f);
    static const Color BLUE    = Color(0.0f, 0.0f, 1.0f);
    static const Color YELLOW  = Color(1.0f, 1.0f, 0.0f);
    static const Color CYAN    = Color(0.0f, 1.0f, 1.0f);
    static const Color MAGENTA = Color(1.0f, 0.0f, 1.0f);
}

// Convert from linear scene radiance to linear display radiance using reinhard tonemapping
inline Color tonemap_reinhard(Color color) {
    //TODO: Apply Reinhard Tonemapping
    return color;
}

// An sRGB color where each channel is an 8-bit unsigned integer
using ColorSRGB = glm::tvec3<glm::uint8>;

// Encodes a linear display radiance (linear sRGB) color to an non-linear sRGB color 
// where each channel is an 8-bit unsigned integer
inline ColorSRGB encode_srgb(Color color) {
    //TODO: Encode to sRGB as follows:
    //  - Clamp to the range [0,1].
    //  - Apply gamma-correction.
    //  - Convert each channel from 32-bit float to 8-bit unsigned int.
    return ColorSRGB(color * 255.0f);
}

/////////////////////////////////////////////////////////
// Some Utilities used for Procedural Color Generation //
/////////////////////////////////////////////////////////

// Converts Hue, Saturation, Lightness to a Linear sRGB color
inline Color convert_HSL_to_RGB(float h, float s, float l) {
    auto hue2rgb = [](float p, float q, float t) -> float {
        if (t < 0.0f) t += 1.0f;
        if (t > 1.0f) t -= 1.0f;
        if (t < 1.0f/6) return p + (q - p) * 6 * t;
        if (t < 1.0f/2) return q;
        if (t < 2.0f/3) return p + (q - p) * (2./3 - t) * 6;
        return p;
    };

    Color c;
    if(s == 0.0f) { // achromatic (grey)
        c = Color(l);
    } else {
        float q = l < 0.5f ? l * (1.0f + s) : l + s - l * s;
        float p = 2 * l - q;
        c = Color(
            hue2rgb(p, q, h + 1.0f/3),
            hue2rgb(p, q, h),
            hue2rgb(p, q, h - 1.0f/3)
        );
    }
    return glm::pow(c, Color(2.2f));
}