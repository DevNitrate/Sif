#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <raylib.h>
#include "Pixel.h"

class Img {
public:
    Img(std::string f);

    int width;
    int height;
    std::vector<Pixel> data;
};