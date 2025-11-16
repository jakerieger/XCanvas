// Author: Jake Rieger
// Created: 11/11/25.
//

#pragma once

#include "Typedefs.hpp"

namespace X {
    struct Point {
        f32 x, y;
        Point(f32 x, f32 y) : x(x), y(y) {}

        Point& operator+=(const Point& other) {
            x += other.x;
            y += other.y;
            return *this;
        }

        Point operator*(const f32 scalar) const {
            return {x * scalar, y * scalar};
        }
    };
}  // namespace X
