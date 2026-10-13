#include <print>
#include <raylib.h>

int main() {
    // C++ 23 yay
    std::print("Hello, World\n");

    InitWindow(800, 600, "QWERTY Piano");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GetColor(0x2323CC));

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
