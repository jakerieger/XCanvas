// Author: Jake Rieger
// Created: 11/11/25.
//

#include "XCanvas/Application.hpp"
#include "XCanvas/Canvas.hpp"

#include <iostream>

namespace X {
    class TestbedApp final : public Application {
    public:
        explicit TestbedApp(i32 argc, char* argv[]) : Application(argc, argv, "Testbed") {}

        void OnStartup() override {
            std::cout << "Provided arguments:\n";
            for (auto& arg : GetArgs()) {
                std::cout << arg << std::endl;
            }
        }

        void OnUpdate(f32 dT) override {}

        void OnPaint(Canvas* canvas) override {
            canvas->Begin();
            {
                canvas->Clear();

                canvas->SetFillColor(Color::Red());
                canvas->SetStrokeColor(Color::White());
                canvas->SetStrokeWidth(4.0f);

                canvas->DrawLine(Point(10.f, 10.f), Point(200.f, 10.f));
                canvas->DrawRectangle(100, 100, 400, 600);
            }
            canvas->End();
        }

        void OnKeyPress(u32 keyCode) override {
            if (keyCode == GLFW_KEY_ESCAPE) { Quit(); }
        }
    };
}  // namespace X

int main(int argc, char* argv[]) {
    X::TestbedApp app(argc, argv);
    return app.Run();
}