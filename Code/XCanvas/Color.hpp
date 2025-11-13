// Author: Jake Rieger
// Created: 11/11/25.
//

#pragma once

namespace X {
    struct Color {
        float r, g, b, a;

        explicit Color(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f) : r(r), g(g), b(b), a(a) {}

        static Color RGB(int r, int g, int b, int a = 255) {
            return Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
        }

        static Color Black() {
            return Color(0, 0, 0, 1);
        }
        static Color White() {
            return Color(1, 1, 1, 1);
        }
        static Color Red() {
            return Color(1, 0, 0, 1);
        }
        static Color Green() {
            return Color(0, 1, 0, 1);
        }
        static Color Blue() {
            return Color(0, 0, 1, 1);
        }
        static Color Transparent() {
            return Color {0, 0, 0, 0};
        }
    };
}  // namespace X
