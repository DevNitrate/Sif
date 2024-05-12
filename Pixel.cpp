#include "Pixel.h"

Pixel::Pixel(int r, int g, int b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

Color Pixel::getRGBA() {
    Color col = (Color){ r, g, b, 255 };

    return col;
}