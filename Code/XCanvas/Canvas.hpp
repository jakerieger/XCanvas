// Author: Jake Rieger
// Created: 11/11/25.
//

#pragma once

#include <glad/glad.h>

#include "Color.hpp"
#include "Point.hpp"
#include "Typedefs.hpp"
#include "Macros.hpp"

namespace X {
    class Canvas {
    public:
        Canvas(u32 width, u32 height);
        ~Canvas();

        void Clear(const Color& clearColor = Colors::Black) const;
        void Resize(u32 width, u32 height);

        void Begin() const;
        void End() const;

        void SetFillColor(const Color& fillColor) {
            mFillColor = fillColor;
        }

        void SetStrokeColor(const Color& strokeColor) {
            mStrokeColor = strokeColor;
        }

        void SetStrokeWidth(const f32 width) {
            mStrokeWidth = width;
        }

        void DrawLine(f32 x0, f32 y0, f32 x1, f32 y1) const;
        void DrawLine(const Point& start, const Point& end) const;
        void DrawRectangle(f32 x, f32 y, f32 width, f32 height, bool filled = true) const;
        void DrawCircle(f32 x, f32 y, f32 radius, u32 segments, bool filled = true) const;
        void DrawPolygon(const vector<Point>& points, bool filled = true) const;

        X_ND u32 GetWidth() const {
            return mWidth;
        }

        X_ND u32 GetHeight() const {
            return mHeight;
        }

    private:
        void InitShaders();
        void SetupBuffers();
        void DrawVertices(const vector<f32>& vertices, GLenum mode) const;

        X_ND f32 ScreenToClipX(f32 x) const;
        X_ND f32 ScreenToClipY(f32 y) const;

        u32 mWidth;
        u32 mHeight;

        Color mFillColor {Colors::Transparent};
        Color mStrokeColor {Colors::Transparent};
        f32 mStrokeWidth {0.0f};

        GLuint mShaderProgram {0};
        GLuint mVAO {0};
        GLuint mVBO {0};

        GLint mColorLocation {0};
    };
}  // namespace X
