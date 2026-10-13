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
    float level = 0.0f;
    std::atomic<bool> on = false;   // written by main and read by audio thread
};

// accordeon mapping to QWERTY
constexpr std::array<std::array<Note, 8>, 3> notes{{
    // Q row
    {Note{57, KEY_Q},   // A3
     Note{60, KEY_W},   // C4
     Note{63, KEY_E},   // Eb4
     Note{66, KEY_R},   // Gb4
     Note{69, KEY_T},   // A4
     Note{72, KEY_Y},   // C5
     Note{75, KEY_U},   // Eb5
     Note{78, KEY_I}},  // Gb5

    // A row
    {Note{56, KEY_A},   // Ab3
     Note{59, KEY_S},   // B3
     Note{62, KEY_D},   // D4
     Note{65, KEY_F},   // F4
     Note{68, KEY_G},   // Ab4
     Note{71, KEY_H},   // B4
     Note{74, KEY_J},   // D5
     Note{77, KEY_K}},  // F5

    // Z row
    {Note{55, KEY_Z},       // G3
     Note{58, KEY_X},       // Bb3
     Note{61, KEY_C},       // Db4
     Note{64, KEY_V},       // E4
     Note{67, KEY_B},       // G4
     Note{70, KEY_N},       // Bb4
     Note{73, KEY_M},       // Db5
     Note{76, KEY_COMMA}}   // E5

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

constexpr float SPACING = 100.0f;    // distance between keys
constexpr float RADIUS = 50.0f;
constexpr float LEFT = 60.0f;
constexpr float TOP = 200.0f;

constexpr std::array<float, 3> ROW_SHIFT{0.0f, 0.25f, 0.75f};  // Q, A, Z

constexpr int SAMPLE_RATE = 44100;

constexpr float ATTACK_SECONDS = 0.03f;
constexpr float RELEASE_SECONDS = 0.15f;

constexpr float ATTACK_STEP = 1.0f / (ATTACK_SECONDS * SAMPLE_RATE);
constexpr float RELEASE_STEP = 1.0f / (ATTACK_SECONDS * SAMPLE_RATE);

void audio_callback(void* buffer, unsigned int frames) {
    float* out = static_cast<float*>(buffer);

    for (unsigned int i = 0; i < frames; ++i) {
        float sample = 0.0f;

        for (Voice& voice: voices) {
            if (voice.on) {
                voice.level = std::min(voice.level + ATTACK_STEP, 1.0f);
            } else {
                voice.level = std::max(voice.level - RELEASE_STEP, 0.0f);
            }

            if (voice.level == 0.0f) continue;

            sample += std::sin(2.0f * PI * voice.phase) * voice.level * 0.5f;
            voice.phase += voice.freq / SAMPLE_RATE;

            if (voice.phase >= 1.0f) voice.phase -= 1.0f;
        }

        out[i] = sample;
    }
}

float midi_to_freq(int midi) {
    return 440.0f * std::pow(2.0f, (midi - 69) / 12.0f);
}


int main() {
    // C++ 23 yay
    std::print("Hello, World\n");

    InitWindow(1280, 720, "QWERTY Piano");
    SetTargetFPS(60);

    InitAudioDevice();
    SetAudioStreamBufferSizeDefault(512);
    AudioStream stream = LoadAudioStream(SAMPLE_RATE, 32, 1);
    SetAudioStreamCallback(stream, audio_callback);
    PlayAudioStream(stream);

    for (std::size_t row = 0; row < notes.size(); ++row) {
        for (std::size_t col = 0; col < notes[0].size(); ++col) {
            voices[row * 8 + col].freq = midi_to_freq(notes[row][col].midi);
        }
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GetColor(0x233223FF));

        for (std::size_t row = 0; row < notes.size(); ++row) {
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

                voices[row * 8 + col].on = IsKeyDown(n.key);
            }
        }

        EndDrawing();
    }

    UnloadAudioStream(stream);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
