// Author: Jake Rieger
// Created: 11/11/25.
//

#pragma once

namespace X::Shaders {
    const char* kVertexShaderSource = R""(#version 460 core
layout (location = 0) in vec2 aPos;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
}
    )"";

    const char* kFragmentShaderSource = R""(#version 460 core
out vec4 FragColor;
uniform vec4 uColor;

void main() {
    FragColor = uColor;
}
    )"";
} // X
