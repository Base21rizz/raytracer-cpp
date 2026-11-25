#pragma once

#include "vec3.h"
#include <algorithm>
#include <iostream>

using color = vec3;

inline void write_color(std::ostream& out, const color& pixel_color) {
    int rbyte = static_cast<int>(256 * std::clamp(pixel_color.x(), 0.0, 0.999));
    int gbyte = static_cast<int>(256 * std::clamp(pixel_color.y(), 0.0, 0.999));
    int bbyte = static_cast<int>(256 * std::clamp(pixel_color.z(), 0.0, 0.999));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}