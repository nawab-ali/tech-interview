/**
 * @file main.cpp
 * @brief This file implements the main thread of execution.
 * @author Nawab Ali
 */

#include "Image.h"
#include "Pixel.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
    long image_height = 1024;
    long image_width = 1024;
    vector<vector<Pixel>> pixels;

    srand(static_cast<int>(time(0)));

    for (long i = 0; i < image_height; i++) {
        vector<Pixel> v;
        for (long j = 0; j < image_width; j++) {
            Pixel pixel;
            pixel.set_channel(rgba_channel::RED,
                              static_cast<uint8_t>(rand() % 256));
            pixel.set_channel(rgba_channel::GREEN,
                              static_cast<uint8_t>(rand() % 256));
            pixel.set_channel(rgba_channel::BLUE,
                              static_cast<uint8_t>(rand() % 256));
            pixel.set_channel(rgba_channel::ALPHA,
                              static_cast<uint8_t>(rand() % 256));
            v.push_back(pixel);
        }
        pixels.push_back(v);
    }

    Image image(pixels);
    image.blur(1);

    return (0);
}
