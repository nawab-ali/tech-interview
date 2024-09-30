/**
 * @file Image.h
 * @brief This file implements an Image class.
 * @author Nawab Ali
 */

#ifndef IMAGE_H
#define IMAGE_H

#include "Pixel.h"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <omp.h>
#include <vector>

using namespace std;

/**
 * @class Image
 * @brief This class implements a 2-dimensional image.
 */

class Image {
  public:
    /**
     * @brief Constructor for the Image class
     * @param height Image height
     * @param width Image width
     * @return None
     */
    Image(long height = 0, long width = 0);

    /**
     * @brief Constructor for the Image class
     * @param pixels Image pixels
     * @return None
     */
    Image(vector<vector<Pixel>> pixels);

    /**
     * @brief Copy Constructor for the Image class
     * @param image Reference to Image object
     * @return None
     */
    Image(const Image &image);

    /**
     * @brief Overload the assignment operator
     * @param image Reference to Image object
     * @return Reference to Image object
     */
    Image &operator=(const Image &image);

    /**
     * @brief Overload the == operator
     * @param image Reference to Image object
     * @return True or False
     */
    bool operator==(const Image &image) const;

    /**
     * @brief Overload the << operator
     * @param ostream Reference to ostream object
     * @param image Reference to Image object
     * @return Reference to ostream object
     */
    friend ostream &operator<<(ostream &out, const Image &image) {
        long height = image.get_height();
        long width = image.get_width();

        out << height << ", " << width << endl;
        for (long row = 0; row < height; row++) {
            for (long col = 0; col < width; col++) {
                out << image.get_pixel(row, col).get_pixel() << " ";
            }
            out << endl;
        }
        return (out);
    }

    /**
     * @brief Getter method for image height
     * @param void
     * @return image height
     */
    long get_height(void) const;

    /**
     * @brief Getter method for image width
     * @param void
     * @return image width
     */
    long get_width(void) const;

    /**
     * @brief Getter method for image pixels
     * @param void
     * @return image pixels
     */
    vector<vector<Pixel>> get_pixels(void) const;

    /**
     * @brief Getter method for image pixel
     * @param row index into image row
     * @param col index into image column
     * @return image pixel
     */
    Pixel get_pixel(const long row, const long col) const;

    /**
     * @brief Setter method for image pixel
     * @param row index into image row
     * @param col index into image column
     * @param pixel image pixel
     * @return void
     */
    void set_pixel(const long row, const long col, const Pixel pixel);

    /**
     * @brief Blur the image
     * @param radius range of neighboring pixels to calculate new pixel value
     * @return Blurred Image
     */
    Image blur(const long radius = 1);

    /**
     * @brief Destructor for the Image class
     * @return None
     */
    ~Image();

  private:
    long height;
    long width;
    vector<vector<Pixel>> pixels;

    /**
     * @brief Calculate new value of pixel at x,y by averaging pixel values
     * from radius pixels
     * @param row index into image row
     * @param col index into image column
     * @param radius range of neighboring pixels to calculate new pixel value
     * @return New pixel
     */
    Pixel box_blur_kernel(const long row, const long col, const long radius);

    /**
     * @brief Calculate new value of pixels for row
     * @param row index into image row
     * @param radius range of neighboring pixels to calculate new pixel value
     * @return vector of blurred pixels
     */
    vector<Pixel> blur_image_row(const long row, const long radius);

    /**
     * @brief Check if row, col are within image bounds
     * @param row index into image row
     * @param col index into image column
     * @return void
     */
    void check_image_bounds(const long row, const long col) const;

    /**
     * @brief Check if row is within image bounds
     * @param row index into image row
     * @return void
     */
    void check_image_row_bound(const long row) const;

    /**
     * @brief Check if col is within image bounds
     * @param col index into image column
     * @return void
     */
    void check_image_col_bound(const long col) const;

    /**
     * @brief Check if radius < 0
     * @param radius range of neighboring pixels to calculate new pixel value
     * @return void
     */
    void check_blur_radius(const long radius) const;
};

Image::Image(long height, long width) : height(height), width(width) {
    for (long row = 0; row < height; row++) {
        vector<Pixel> v;
        for (long col = 0; col < width; col++) {
            Pixel pixel;
            v.push_back(pixel);
        }
        pixels.push_back(v);
    }
}

Image::Image(vector<vector<Pixel>> pixels) : pixels(pixels) {
    height = pixels.size();

    if (height == 0) {
        width = 0;
    } else {
        width = pixels[0].size();
    }
}

Image::Image(const Image &image)
    : height(image.height), width(image.width), pixels(image.pixels) {}

Image &Image::operator=(const Image &image) {
    height = image.height;
    width = image.width;
    pixels = image.pixels;

    return (*this);
}

bool Image::operator==(const Image &image) const {
    return (height == image.height && width == image.width &&
            pixels == image.pixels);
}

long Image::get_height(void) const { return height; }

long Image::get_width(void) const { return width; }

vector<vector<Pixel>> Image::get_pixels(void) const { return pixels; }

Pixel Image::get_pixel(const long row, const long col) const {
    check_image_bounds(row, col);
    return (pixels[row][col]);
}

void Image::set_pixel(const long row, const long col, const Pixel pixel) {
    check_image_bounds(row, col);
    pixels[row][col] = pixel;
}

Image Image::blur(const long radius) {
    long row = 0;
    int chunk = 1;
    vector<vector<Pixel>> pixels(height);

    check_blur_radius(radius);

#pragma omp parallel for shared(pixels, chunk) private(row)                    \
    schedule(static, chunk)
    for (row = 0; row < height; row++) {
        pixels[row] = blur_image_row(row, radius);
    }

    return (Image(pixels));
}

Image::~Image() {
    for_each(pixels.begin(), pixels.end(), [](vector<Pixel> v) { v.clear(); });
    pixels.clear();
}

Pixel Image::box_blur_kernel(const long row, const long col,
                             const long radius) {
    Pixel pixel;
    long num_elements = 0, zero = 0;
    uint32_t red = 0, green = 0, blue = 0, alpha = 0;
    long row_start = max((row - radius), zero);
    long row_end = min((row + radius), height);
    long col_start = max((col - radius), zero);
    long col_end = min((col + radius), width);

    check_image_bounds(row, col);
    check_blur_radius(radius);

    if (row_end == height)
        row_end--;
    if (col_end == width)
        col_end--;

    for (long k = row_start; k <= row_end; k++) {
        for (long l = col_start; l <= col_end; l++) {
            red += pixels[k][l].get_channel(rgba_channel::RED);
            green += pixels[k][l].get_channel(rgba_channel::GREEN);
            blue += pixels[k][l].get_channel(rgba_channel::BLUE);
            alpha += pixels[k][l].get_channel(rgba_channel::ALPHA);
        }
    }

    num_elements = (row_end - row_start + 1) * (col_end - col_start + 1);
    pixel.set_channel(rgba_channel::RED,
                      static_cast<uint8_t>(red / num_elements));
    pixel.set_channel(rgba_channel::GREEN,
                      static_cast<uint8_t>(green / num_elements));
    pixel.set_channel(rgba_channel::BLUE,
                      static_cast<uint8_t>(blue / num_elements));
    pixel.set_channel(rgba_channel::ALPHA,
                      static_cast<uint8_t>(alpha / num_elements));

    return (pixel);
}

vector<Pixel> Image::blur_image_row(const long row, const long radius) {
    vector<Pixel> pixels;

    for (long col = 0; col < width; col++) {
        pixels.push_back(box_blur_kernel(row, col, radius));
    }

    return (pixels);
}

void Image::check_image_bounds(const long row, const long col) const {
    check_image_row_bound(row);
    check_image_col_bound(col);
}

void Image::check_image_row_bound(const long row) const {
    if (row < 0 || row >= height) {
        throw invalid_argument("row < 0 || row >= height");
    }
}

void Image::check_image_col_bound(const long col) const {
    if (col < 0 || col >= width) {
        throw invalid_argument("col < 0 || col >= width");
    }
}

void Image::check_blur_radius(const long radius) const {
    if (radius < 0) {
        throw invalid_argument("radius < 0");
    }
}

#endif // IMAGE_H
