#include <print>
#include <array>
#include <raylib.h>

struct Note {
    int midi;           // scientific pitch notation
    KeyboardKey key;
    const char* label;  // key label
};

// accordeon mapping to QWERTY
constexpr std::array<std::array<Note, 8>, 3> notes{{
    // Q row
    {Note{45, KEY_Q, "Q"},   // A2
     Note{48, KEY_W, "W"},   // C3
     Note{51, KEY_E, "E"},   // Eb3
     Note{54, KEY_R, "R"},   // Gb3
     Note{57, KEY_T, "T"},   // A3
     Note{60, KEY_Y, "Y"},   // C4
     Note{63, KEY_U, "U"},   // Eb4
     Note{66, KEY_I, "I"}},  // Gb4

    // A row
    {Note{44, KEY_A, "A"},   // Ab2
     Note{47, KEY_S, "S"},   // B2
     Note{50, KEY_D, "D"},   // D3
     Note{53, KEY_F, "F"},   // F3
     Note{56, KEY_G, "G"},   // Ab3
     Note{59, KEY_H, "H"},   // B3
     Note{62, KEY_J, "J"},   // D4
     Note{65, KEY_K, "K"}},  // F4

    // Z row
    {Note{43, KEY_Z, "Z"},       // G2
     Note{46, KEY_X, "X"},       // Bb2
     Note{49, KEY_C, "C"},       // Db3
     Note{52, KEY_V, "V"},       // E3
     Note{55, KEY_B, "B"},       // G3
     Note{58, KEY_N, "N"},       // Bb3
     Note{61, KEY_M, "M"},       // Db4
     Note{64, KEY_COMMA, ","}}   // E4

}};

constexpr float SPACING = 85.0f;    // distance between keys
constexpr float RADIUS = 30.0f;
constexpr float LEFT = 60.0f;
constexpr float TOP = 200.0f;

constexpr std::array<float, 3> ROW_SHIFT{0.0f, 0.25f, 0.75f};  // Q, A, Z

int main() {
    // C++ 23 yay
    std::print("Hello, World\n");

    InitWindow(800, 600, "QWERTY Piano");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GetColor(0x233223FF));

        for (int row = 0; row < 3; ++row) {
            for (std::size_t col = 0; col < notes[0].size(); ++col) {
                float x_pos = LEFT + (col + ROW_SHIFT[row]) * SPACING;
                float y_pos = TOP + row * SPACING;

                const Note& n = notes[row][col];
                Color fill = IsKeyDown(n.key) ? ORANGE : RAYWHITE;

                DrawCircle(x_pos, y_pos, RADIUS, fill);

            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
