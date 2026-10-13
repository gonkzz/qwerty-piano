#include <print>
#include <array>
#include <format>
#include <string>
#include <atomic>
#include <cmath>

#include <raylib.h>

struct Note {
    int midi;           // scientific pitch notation
    KeyboardKey key;
};

struct Voice {
    float freq = 0.0f;
    float phase = 0.0f;
};

// accordeon mapping to QWERTY
constexpr std::array<std::array<Note, 8>, 3> notes{{
    // Q row
    {Note{45, KEY_Q},   // A2
     Note{48, KEY_W},   // C3
     Note{51, KEY_E},   // Eb3
     Note{54, KEY_R},   // Gb3
     Note{57, KEY_T},   // A3
     Note{60, KEY_Y},   // C4
     Note{63, KEY_U},   // Eb4
     Note{66, KEY_I}},  // Gb4

    // A row
    {Note{44, KEY_A},   // Ab2
     Note{47, KEY_S},   // B2
     Note{50, KEY_D},   // D3
     Note{53, KEY_F},   // F3
     Note{56, KEY_G},   // Ab3
     Note{59, KEY_H},   // B3
     Note{62, KEY_J},   // D4
     Note{65, KEY_K}},  // F4

    // Z row
    {Note{43, KEY_Z},       // G2
     Note{46, KEY_X},       // Bb2
     Note{49, KEY_C},       // Db3
     Note{52, KEY_V},       // E3
     Note{55, KEY_B},       // G3
     Note{58, KEY_N},       // Bb3
     Note{61, KEY_M},       // Db4
     Note{64, KEY_COMMA}}   // E4

}};

constexpr std::array<const char*, 12>NOTE_NAMES {
    "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"
};

std::string note_name(int midi) {
    // % 12 note within octave
    // / 12 - 1
    return std::format("{}{}", NOTE_NAMES[midi % 12], midi / 12 - 1);
}

std::array<Voice, 24> voices;

constexpr float SPACING = 85.0f;    // distance between keys
constexpr float RADIUS = 30.0f;
constexpr float LEFT = 60.0f;
constexpr float TOP = 200.0f;

constexpr std::array<float, 3> ROW_SHIFT{0.0f, 0.25f, 0.75f};  // Q, A, Z

constexpr int SAMPLE_RATE = 44100;

void audio_callback(void* buffer, unsigned int frames) {
    static float phase = 0.0f;
    float* out = static_cast<float*>(buffer);

    for (unsigned int i = 0; i < frames; ++i) {
        out[i] = std::sin(2.0f * PI * phase) * 0.2f;
        phase += 220.0f / SAMPLE_RATE;
        if (phase >= 1.0f) phase -= 1.0f;
    }
}


int main() {
    // C++ 23 yay
    std::print("Hello, World\n");

    InitWindow(800, 600, "QWERTY Piano");
    SetTargetFPS(60);

    InitAudioDevice();
    SetAudioStreamBufferSizeDefault(512);
    AudioStream stream = LoadAudioStream(SAMPLE_RATE, 32, 1);
    SetAudioStreamCallback(stream, audio_callback);
    PlayAudioStream(stream);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GetColor(0x233223FF));

        for (int row = 0; row < 3; ++row) {
            for (std::size_t col = 0; col < notes[0].size(); ++col) {
                float x_pos = LEFT + (col + ROW_SHIFT[row]) * SPACING;
                float y_pos = TOP + row * SPACING;

                const Note& n = notes[row][col];
                Color fill = IsKeyDown(n.key) ? BLACK : RAYWHITE;

                DrawCircle(x_pos, y_pos, RADIUS, fill);

                std::string name = note_name(n.midi);
                int size = 25;
                int w = MeasureText(name.c_str(), size);
                DrawText(name.c_str(), x_pos - w / 2, y_pos - size / 2, size, GRAY);
            }
        }

        EndDrawing();
    }

    UnloadAudioStream(stream);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
