// Author: Jake Rieger
// Created: 11/15/25.
//

#pragma once

namespace X::Math {
    inline f32 Lerp(f32 a, f32 b, f32 t) {
        return a + t * (b - a);
    }
}  // namespace X::Math
