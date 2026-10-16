# qwerty-synth

<img src="assets/icon.png" alt="" width="140">


A small synthesizer in C++ with [raylib](https://www.raylib.com/), played entirely on the laptop keyboard. The keys follow a chromatic button accordion layout instead of a piano.

I wrote about it here: [I'm Learning a New Instrument](https://goncalo-soares.com/blog/qwerty-synth/).


https://github.com/user-attachments/assets/460366cc-7a6f-4039-9f1d-26ce1cbc6545


## Layout

```
 Q row:   Q    W    E    R    T    Y    U    I
          A3   C4   Eb4  Gb4  A4   C5   Eb5  Gb5

 A row:    A    S    D    F    G    H    J    K
           Ab3  B3   D4   F4   Ab4  B4   D5   F5

 Z row:      Z    X    C    V    B    N    M    ,
             G3   Bb3  Db4  E4   G4   Bb4  Db5  E5
```

- the slanted columns are chromatic: `Z A Q` are all a semitone apart, then `X S W`, `C D E` and so forth
- one key to the right is a minor third, four keys to the right is an octave
- shapes are easy to move: G major is `Z S D`, and the same shape one key to the right, `X D F`, is Bb major

Some three-key chords won't sound on a laptop keyboard. That's ghosting, and it depends on your keyboard.

## Building

Requires a C++23 compiler with `std::print` support (GCC 14+ or a recent clang), make and raylib. US QWERTY layout.

### Linux

Install raylib from your package manager, or [build it from source](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux) if your distro doesn't package it.

```sh
# Arch Linux
sudo pacman -S raylib

make run
```

### macOS

Install the Xcode Command Line Tools and [Homebrew](https://brew.sh), then:

```sh
xcode-select --install
brew install raylib

make CXX=clang++ \
     CXXFLAGS="-std=c++23 -O2 -I$(brew --prefix)/include" \
     LDLIBS="-L$(brew --prefix)/lib -lraylib" \
     run
```

The extra variables point the compiler at Homebrew's raylib. If clang reports that `<print>` is missing, update Xcode.

### Windows

Install [MSYS2](https://www.msys2.org), open the **MSYS2 UCRT64** shell, then:

```sh
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-raylib make

make LDLIBS="-lraylib -lopengl32 -lgdi32 -lwinmm" run
```

Run it from the UCRT64 shell, which has raylib's DLL on its path. If the linker complains about `__open_terminal` or `__write_to_terminal`, add `-lstdc++exp` to `LDLIBS`.

## What's next

More sounds, effects, and recording and layering tracks. I don't know how far I'll take it.
