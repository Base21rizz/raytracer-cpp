#pragma once

#include "vec3.h"
#include <algorithm>
#include <iostream>

using color = vec3;

inline double linear_to_gamma(double linear_component) {
    return (linear_component > 0) ? std::sqrt(linear_component) : 0;
}

inline void write_color(std::ostream& out, const color& pixel_color) {
    auto r = linear_to_gamma(pixel_color.x());
    auto g = linear_to_gamma(pixel_color.y());
    auto b = linear_to_gamma(pixel_color.z());

    int rbyte = static_cast<int>(256 * std::clamp(r, 0.0, 0.999));
    int gbyte = static_cast<int>(256 * std::clamp(g, 0.0, 0.999));
    int bbyte = static_cast<int>(256 * std::clamp(b, 0.0, 0.999));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}