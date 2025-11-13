// Author: Jake Rieger
// Created: 11/11/25.
//

#include "Canvas.hpp"
#include "Shaders.hpp"

#include <iostream>

namespace X {
    Canvas::Canvas(u32 width, u32 height) : mWidth(width), mHeight(height) {
        InitShaders();
        SetupBuffers();
    }

    Canvas::~Canvas() {
        glDeleteVertexArrays(1, &mVAO);
        glDeleteBuffers(1, &mVBO);
        glDeleteProgram(mShaderProgram);
    }

    void Canvas::Clear(const Color& clearColor) const {
        if (mShaderProgram == 0) { std::cout << "Canvas::Clear() - No currently bound shader program\n"; }
        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Canvas::Resize(u32 width, u32 height) {
        if (width <= 0 || height <= 0) return;
        mWidth  = width;
        mHeight = height;
    }

    void Canvas::Begin() const {
        glUseProgram(mShaderProgram);
        glBindVertexArray(mVAO);
    }

    void Canvas::End() const {
        if (mVAO != 0) glBindVertexArray(0);
        if (mShaderProgram != 0) glUseProgram(0);
    }

    void Canvas::DrawLine(const f32 x0, const f32 y0, const f32 x1, const f32 y1) const {
        const vector<f32> vertices = {ScreenToClipX(x0), ScreenToClipY(y0), ScreenToClipX(x1), ScreenToClipY(y1)};
        glUniform4f(mColorLocation, mStrokeColor.r, mStrokeColor.g, mStrokeColor.b, mStrokeColor.a);
        DrawVertices(vertices, GL_LINES);
    }

    void Canvas::DrawLine(const Point& start, const Point& end) const {
        DrawLine(start.x, start.y, end.x, end.y);
    }

    void Canvas::DrawRectangle(f32 x, f32 y, f32 width, f32 height, bool filled) const {
        vector<f32> vertices;

        if (filled) {
            // Two triangles for filled rectangle
            vertices = {ScreenToClipX(x),
                        ScreenToClipY(y),
                        ScreenToClipX(x + width),
                        ScreenToClipY(y),
                        ScreenToClipX(x + width),
                        ScreenToClipY(y + height),

                        ScreenToClipX(x),
                        ScreenToClipY(y),
                        ScreenToClipX(x + width),
                        ScreenToClipY(y + height),
                        ScreenToClipX(x),
                        ScreenToClipY(y + height)};

            glUniform4f(mColorLocation, mFillColor.r, mFillColor.g, mFillColor.b, mFillColor.a);
            DrawVertices(vertices, GL_TRIANGLES);
        } else {
            // Line loop for outline
            vertices = {ScreenToClipX(x),
                        ScreenToClipY(y),
                        ScreenToClipX(x + width),
                        ScreenToClipY(y),
                        ScreenToClipX(x + width),
                        ScreenToClipY(y + height),
                        ScreenToClipX(x),
                        ScreenToClipY(y + height)};

            glUniform4f(mColorLocation, mStrokeColor.r, mStrokeColor.g, mStrokeColor.b, mStrokeColor.a);
            DrawVertices(vertices, GL_LINE_LOOP);
        }
    }

    void Canvas::InitShaders() {
        const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &Shaders::kVertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        GLint success;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            std::cerr << "Vertex shader compilation failed:\n" << infoLog << std::endl;
        }

        const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &Shaders::kFragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            std::cerr << "Fragment shader compilation failed:\n" << infoLog << std::endl;
        }

        mShaderProgram = glCreateProgram();
        glAttachShader(mShaderProgram, vertexShader);
        glAttachShader(mShaderProgram, fragmentShader);
        glLinkProgram(mShaderProgram);

        glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(mShaderProgram, 512, nullptr, infoLog);
            std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        mColorLocation = glGetUniformLocation(mShaderProgram, "uColor");
    }

    void Canvas::SetupBuffers() {
        glGenVertexArrays(1, &mVAO);
        glGenBuffers(1, &mVBO);

        glBindVertexArray(mVAO);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);

        // Position attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(f32), (void*)nullptr);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Canvas::DrawVertices(const vector<f32>& vertices, GLenum mode) const {
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(f32), vertices.data(), GL_DYNAMIC_DRAW);
        glDrawArrays(mode, 0, vertices.size() / 2);
    }

    f32 Canvas::ScreenToClipX(f32 x) const {
        return (2.0f * x / (f32)mWidth) - 1.0f;
    }

    f32 Canvas::ScreenToClipY(f32 y) const {
        return 1.0f - (2.0f * y / (f32)mHeight);
    }
}  // namespace X