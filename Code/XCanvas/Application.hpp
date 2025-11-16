// Author: Jake Rieger
// Created: 11/11/25.
//

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shared.hpp"
#include "Input.hpp"

namespace X {
    class Canvas;

    class Application {
    public:
        explicit Application(i32 argc, char* argv[]);
        explicit Application(i32 argc, char* argv[], const string& title);
        virtual ~Application();

        virtual void OnUpdate(f32 dT) {};
        virtual void OnPaint(Canvas* canvas) {}
        virtual void OnStartup();
        virtual void OnShutdown() {}
        virtual void OnKeyPress(u32 keyCode) {}
        virtual void OnMouseButtonPress(u32 buttonCode) {}
        virtual void OnWindowResize(u32 width, u32 height) {}
        virtual void OnCursorMove(f64 posX, f64 posY) {}

        bool Run();
        void Quit();

        X_ND Canvas* GetRootCanvas() const {
            return mRootCanvas.get();
        }

        X_ND vector<string> GetArgs() const& {
            return mArgs;
        }

        void SetTitle(const string& title) {
            mTitle = title;
        }

    protected:
        u32 mWidth {1280};
        u32 mHeight {720};

    private:
        void Initialize();
        void SetupOpenGL() const;

        static void KeyCallback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods);
        static void MouseButtonCallback(GLFWwindow* window, i32 button, i32 action, i32 mods);
        static void CursorPosCallback(GLFWwindow* window, f64 xpos, f64 ypos);
        static void FramebufferSizeCallback(GLFWwindow* window, i32 width, i32 height);

        GLFWwindow* mWindow {nullptr};
        string mTitle {"XCanvas Application"};
        bool mRunning {false};
        vector<string> mArgs;
        f64 mLastFrameTime {0.0};
        unique_ptr<Canvas> mRootCanvas;
    };
}  // namespace X
