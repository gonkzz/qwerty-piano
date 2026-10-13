# keyboard

A small piano you play with your laptop keyboard, written in C++ with [raylib](https://www.raylib.com/).

## Goals

- Piano range from G2 to F4 using the computer keyboard (US QWERTY layout)
- Notes sustain while a key is held and stop on release
- Several sounds to switch between (sine, triangle, square, saw, a piano tone)
- Raylib as the only dependency

## Keybinds

```
upper half (G3–F4)
 black:   1    2   3       5   6
         F#3  G#3 A#3     C#4 D#4
 white:     Q    W   E   R   T   Y   U
            G3   A3  B3  C4  D4  E4  F4

lower half (G2–F3)
 black:        S   D       G   H       K
              G#2 A#2     C#3 D#3     F#3
 white:     Z    X   C   V   B   N   M
            G2   A2  B2  C3  D3  E3  F3
```

F#3 is on both `K` and `1`, so it is reachable from either half.

## Building

Requires a C++ compiler and raylib.

```sh
# Arch Linux
sudo pacman -S raylib

g++ main.cpp -o keyboard -lraylib
./keyboard
```
