#include <print>
#include <raylib.h>

struct Note {
    int midi;           // scientific pitch notation, C1 = MIDI 0
    KeyboardKey key;
    const char* label;  // key label
};

constexpr std::array<Note, 12> notes{
    Note{48, KEY_A, "A"},  // C3
    Note{49, KEY_W, "W"},  // Db3
    Note{50, KEY_S, "S"},  // D3
    Note{51, KEY_E, "E"},  // Eb3
    Note{52, KEY_D, "D"},  // E3
    Note{53, KEY_F, "F"},  // F3
    Note{54, KEY_T, "T"},  // Gb3
    Note{55, KEY_G, "G"},  // G3
    Note{56, KEY_Y, "Y"},  // Ab3
    Note{57, KEY_H, "H"},  // A3
    Note{58, KEY_U, "U"},  // Bb3
    Note{59, KEY_J, "J"},  // B3
};

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
