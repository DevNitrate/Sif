#pragma once
#include <raylib.h>

class Pixel {
public:
    Pixel(int r, int g, int b);

    int r;
    int g;
    int b;

    Color getRGBA();
};