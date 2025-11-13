// Author: Jake Rieger
// Created: 11/11/25.
//

#pragma once

#include <glad/glad.h>

#include "Color.hpp"
#include "Typedefs.hpp"
#include "Macros.hpp"

namespace X {
    class Canvas {
    public:
        Canvas(u32 width, u32 height);
        ~Canvas();

        void Clear(const Color& clearColor = Color::Black()) const;
        void Resize(u32 width, u32 height);

        void Begin() const;
        void End() const;

    private:
        void InitShaders();
        void SetupBuffers();
        void DrawVertices(const vector<f32>& vertices, GLenum mode);

        X_ND f32 ScreenToClipX(f32 x) const;
        X_ND f32 ScreenToClipY(f32 y) const;

        u32 mWidth;
        u32 mHeight;

        Color mFillColor {Color::Transparent()};
        Color mStrokeColor {Color::Transparent()};
        f32 mStrokeWidth {0.0f};

        GLuint mShaderProgram {0};
        GLuint mVAO {0};
        GLuint mVBO {0};

        GLint mColorLocation {0};
    };
}  // namespace X
