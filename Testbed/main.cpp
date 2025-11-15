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
            Application::OnStartup();
        }

        void OnUpdate(f32 dT) override {}

        void OnPaint(Canvas* canvas) override {
            canvas->Begin();
            {
                canvas->Clear();

                canvas->SetStrokeColor(Colors::Red);
                canvas->DrawLine({10, 10}, {100, 100});

                canvas->SetStrokeColor(Colors::Magenta);
                canvas->DrawRectangle(100, 100, 400, 600, false);

                canvas->SetFillColor(Colors::Green);
                canvas->DrawCircle(200, 300, 100, 32);

                canvas->SetFillColor(Colors::Cyan);
                canvas->DrawPolygon({{300, 300}, {600, 300}, {300, 600}});
            }
            canvas->End();
        }

        void OnKeyPress(u32 keyCode) override {
            if (keyCode == Keys::Escape) { Quit(); }
        }
    };
}  // namespace X

int main(int argc, char* argv[]) {
    X::TestbedApp app(argc, argv);
    return app.Run();
}