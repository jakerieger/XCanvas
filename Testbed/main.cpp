// Author: Jake Rieger
// Created: 11/11/25.
//

#include "XCanvas/Application.hpp"
#include "XCanvas/Canvas.hpp"

#include <iostream>
#include <random>

namespace X {
    static f32 RandomInRange(f32 min, f32 max) {
        X_ASSERT(min != max, "RandomInRange() - min cannot equal max!");

        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<f32> dis(min, max);

        return dis(gen);
    }

    struct Circle {
        Point position;
        Point velocity;
        Color color;
        f32 radius;
        f32 speed;

        void Draw(Canvas* canvas) const {
            canvas->SetFillColor(color);
            canvas->DrawCircle(position.x, position.y, radius, 32);
        }
    };

    class TestbedApp final : public Application {
    public:
        explicit TestbedApp(i32 argc, char* argv[]) : Application(argc, argv, "Testbed") {}

        void OnStartup() override {
            Application::OnStartup();

            const Circle c1 = {{100, 100}, {2, 2}, Colors::Green, 32.0f, 100.0f};
            const Circle c2 = {{200, 200},
                               {
                                 -2,
                                 2,
                               },
                               Colors::Red,
                               48.0f,
                               100.0f};

            mCircles.push_back(c1);
            mCircles.push_back(c2);
        }

        void OnUpdate(f32 dT) override {
            for (auto& circle : mCircles) {
                // Simple, naive approach to collision detection with canvas borders.
                // Only works for perfectly perpendicular walls
                if (circle.position.x <= circle.radius || circle.position.x >= (f32)mWidth - circle.radius) {
                    const f32 boundsRight = X_MIN(circle.position.x, mWidth - circle.radius);
                    const f32 boundsLeft  = X_MAX(circle.radius, circle.position.x);
                    if (circle.position.x >= boundsRight) circle.position.x = boundsRight;
                    if (circle.position.x <= boundsLeft) circle.position.x = boundsLeft;

                    circle.velocity.x = -(circle.velocity.x);
                }
                if (circle.position.y <= circle.radius || circle.position.y >= (f32)mHeight - circle.radius) {
                    const f32 boundsBottom = X_MIN(circle.position.y, mHeight - circle.radius);
                    const f32 boundsTop    = X_MAX(circle.radius, circle.position.y);
                    if (circle.position.y >= boundsBottom) circle.position.y = boundsBottom;
                    if (circle.position.y <= boundsTop) circle.position.y = boundsTop;

                    circle.velocity.y = -(circle.velocity.y);
                }
                circle.position += (circle.velocity * circle.speed) * dT;
            }
        }

        void OnPaint(Canvas* canvas) override {
            canvas->Begin();
            {
                canvas->Clear(Color("#2e2e2e"));

                for (const auto& circle : mCircles) {
                    circle.Draw(canvas);
                }
            }
            canvas->End();
        }

        void OnKeyPress(u32 keyCode) override {
            if (keyCode == Keys::Escape) { Quit(); }
            if (keyCode == Keys::Space) {
                // Generate a random circle with random initial properties and spawn it
                const f32 radius  = RandomInRange(8.0f, 128.0f);
                f32 initPositionX = RandomInRange(radius, (f32)mWidth - radius);
                f32 initPositionY = RandomInRange(radius, (f32)mHeight - radius);
                const Color color(RandomInRange(0.0f, 1.0f),
                                  RandomInRange(0.0f, 1.0f),
                                  RandomInRange(0.0f, 1.0f),
                                  1.0f);
                const f32 speed   = RandomInRange(10.0f, 300.0f);
                f32 initVelocityX = RandomInRange(-10.f, 10.f);
                f32 initVelocityY = RandomInRange(-10.0f, 10.0f);

                const Circle newCircle {{initPositionX, initPositionY},
                                        {initVelocityX, initVelocityY},
                                        color,
                                        radius,
                                        speed};
                mCircles.push_back(newCircle);
            }
        }

    private:
        vector<Circle> mCircles {};
    };
}  // namespace X

int main(int argc, char* argv[]) {
    X::TestbedApp app(argc, argv);
    return app.Run();
}