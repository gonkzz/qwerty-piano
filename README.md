# qwerty-synth

<img src="assets/icon.png" alt="" width="140">

A small instrument you play with your laptop keyboard, written in C++ with [raylib](https://www.raylib.com/).
The keys are laid out like a chromatic button accordion instead of a piano.

## Goals

- Play notes from G2 to Gb4 using the computer keyboard (US QWERTY layout)
- Notes sustain while a key is held and stop on release
- Several sounds to switch between (sine, triangle, square, saw, an accordion tone)
- Raylib as the only dependency

## Keybinds

```
 Q row:   Q    W    E    R    T    Y    U    I
          A2   C3   Eb3  Gb3  A3   C4   Eb4  Gb4

 A row:    A    S    D    F    G    H    J    K
           Ab2  B2   D3   F3   Ab3  B3   D4   F4

 Z row:      Z    X    C    V    B    N    M    ,
             G2   Bb2  Db3  E3   G3   Bb3  Db4  E4
```

- Each slanted column of three keys is three consecutive semitones going up,
  so the chromatic scale runs `Z A Q`, `X S W`, `C D E`, and so on.
- Moving one key to the right on a row goes up a minor third.
- The same note an octave higher is four keys to the right on the same row.
- A chord or scale keeps the same shape wherever it starts: G major is `Z S D`,
  and the same shape one key to the right is Bb major.

## Building

Requires a C++23 compiler, make and raylib.

```sh
# Arch Linux
sudo pacman -S raylib

make        # build
make run    # build and run
make clean  # remove the binary
```
