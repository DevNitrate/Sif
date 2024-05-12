#include "Img.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <raylib.h>

Img::Img(std::string f) {
    std::ifstream file;
    file.open(f);

    if (!file) {
        std::cout << "file does not exist";
        exit(1);
    }

    std::string buf;

    std::string pixs;
    std::string header;

    int line = 1;

    while (std::getline(file, buf)) {
        if (line != 1) {
            pixs += buf;
        } else {
            header += buf;
            line++;
        }
    }

    std::istringstream ih(header);

    int split = 0;
    
    std::string word;

    Vector2 dimensions;

    while (ih >> word) {
        if (split == 0) {
            dimensions.x = std::stoi(word);
            split = 1;
        } else {
            dimensions.y = std::stoi(word);
        }
    }

    word = "";

    std::vector<int> pixVals;

    std::istringstream ip(pixs);

    while (ip >> word) {
        pixVals.push_back(std::stoi(word));
    }

    std::vector<Pixel> pixels;

    int valCount = 1;
    int r;
    int g;
    int b;

    for (int i = 0; i < pixVals.size(); i++) {
        if (valCount == 1) {
            r = pixVals[i];
            valCount = 2;
        } else if (valCount == 2) {
            g = pixVals[i];
            valCount = 3;
        } else if (valCount == 3) {
            b = pixVals[i];
            Pixel pix(r, g, b);
            pixels.push_back(pix);
            valCount = 1;
        }
    }

    this->width = dimensions.x;
    this->height = dimensions.y;
    this->data = pixels;
}