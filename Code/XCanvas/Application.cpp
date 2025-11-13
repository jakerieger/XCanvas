// Author: Jake Rieger
// Created: 11/11/25.
//

#include "Application.hpp"
#include "Canvas.hpp"

#include <stdexcept>
#include <sstream>

namespace X {
    Application::Application(i32 argc, char* argv[]) {
        if (argc <= 0) { throw std::runtime_error("Attempted to initialize app with args length of zero or less."); }

        for (auto i = 0; i < argc; ++i) {
            mArgs.emplace_back(argv[i]);
        }

        if (mArgs.size() != argc) {
            std::stringstream err;
            err << "Failed to capture correct number of arguments. Captured " << mArgs.size() << ", expected " << argc;
            throw std::runtime_error(err.str());
        }
    }

    Application::~Application() {
        if (mRootCanvas) { mRootCanvas.reset(); }  // Make sure canvas is reset before GLFW destroys the window context
        if (mWindow) { glfwDestroyWindow(mWindow); }
        glfwTerminate();
    }

    bool Application::Run() {
        mRunning       = true;
        mLastFrameTime = glfwGetTime();
        {
            Initialize();

            OnStartup();

            while (mRunning && !glfwWindowShouldClose(mWindow)) {
                const f64 currentTime = glfwGetTime();
                const auto dT         = CAST<f32>(currentTime - mLastFrameTime);
                mLastFrameTime        = currentTime;

                OnUpdate(dT);
                OnPaint(GetRootCanvas());

                glfwSwapBuffers(mWindow);
                glfwPollEvents();
            }

            OnShutdown();
        }
        mRunning = false;

        return EXIT_SUCCESS;
    }

    void Application::Quit() {
        mRunning = false;
    }

    void Application::Initialize() {
        if (!glfwInit()) { throw std::runtime_error("Failed to initialize GLFW"); }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        mWindow = glfwCreateWindow((i32)mWidth, (i32)mHeight, mTitle.c_str(), nullptr, nullptr);
        if (!mWindow) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }

        glfwMakeContextCurrent(mWindow);
        glfwSetWindowUserPointer(mWindow, this);

        SetupOpenGL();

        glfwSetKeyCallback(mWindow, KeyCallback);
        glfwSetMouseButtonCallback(mWindow, MouseButtonCallback);
        glfwSetCursorPosCallback(mWindow, CursorPosCallback);
        glfwSetFramebufferSizeCallback(mWindow, FramebufferSizeCallback);

        glfwSwapInterval(1);

        mRootCanvas = std::make_unique<Canvas>(mWidth, mHeight);
    }

    void Application::SetupOpenGL() const {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            glfwDestroyWindow(mWindow);
            glfwTerminate();
            throw std::runtime_error("Failed to initialize GLAD");
        }

        glViewport(0, 0, (i32)mWidth, (i32)mHeight);

        // Enable depth testing (common OpenGL setup)
        glEnable(GL_DEPTH_TEST);

        // Enable blending for transparency
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Application::KeyCallback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods) {
        auto* app = CAST<Application*>(glfwGetWindowUserPointer(window));
        if (app) { app->OnKeyPress(key); }
    }

    void Application::MouseButtonCallback(GLFWwindow* window, i32 button, i32 action, i32 mods) {
        auto* app = CAST<Application*>(glfwGetWindowUserPointer(window));
        if (app) { app->OnMouseButtonPress(button); }
    }

    void Application::CursorPosCallback(GLFWwindow* window, f64 xpos, f64 ypos) {
        auto* app = CAST<Application*>(glfwGetWindowUserPointer(window));
        if (app) { app->OnCursorMove(xpos, ypos); }
    }

    void Application::FramebufferSizeCallback(GLFWwindow* window, i32 width, i32 height) {
        auto* app = CAST<Application*>(glfwGetWindowUserPointer(window));
        if (app) {
            app->mWidth  = width;
            app->mHeight = height;
            app->GetRootCanvas()->Resize(width, height);
            app->OnWindowResize(width, height);
        }
    }
}  // namespace X