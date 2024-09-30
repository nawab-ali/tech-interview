/**
 * @file Pixel.h
 * @brief This file implements a Pixel class.
 * @author Nawab Ali
 */

#ifndef PIXEL_H
#define PIXEL_H

#include <cstdint>
#include <iostream>

using namespace std;

enum class rgba_channel { RED, GREEN, BLUE, ALPHA };

typedef union {
    uint32_t value;
    uint8_t bytes[4];
} pixel_t;

/**
 * @class Pixel
 * @brief This class implements a pixel in an image.
 */

class Pixel {
  public:
    /**
     * @brief Constructor for the Pixel class
     * @param rgba Pixel value
     * @return None
     */
    Pixel(uint32_t rgba = 0);

    /**
     * @brief Copy Constructor for the Pixel class
     * @param pixel Reference to Pixel object
     * @return None
     */
    Pixel(const Pixel &pixel);

    /**
     * @brief Overload the assignment operator
     * @param pixel Reference to Pixel object
     * @return Reference to Pixel object
     */
    Pixel &operator=(const Pixel &pixel);

    /**
     * @brief Overload the == operator
     * @param pixel Reference to Pixel object
     * @return True or False
     */
    bool operator==(const Pixel &pixel) const;

    /**
     * @brief Overload the << operator
     * @param ostream Reference to ostream object
     * @param pixel Reference to Pixel object
     * @return Reference to ostream object
     */
    friend ostream &operator<<(ostream &out, const Pixel &pixel) {
        out << static_cast<uint32_t>(pixel.get_channel(rgba_channel::RED))
            << ","
            << static_cast<uint32_t>(pixel.get_channel(rgba_channel::GREEN))
            << ","
            << static_cast<uint32_t>(pixel.get_channel(rgba_channel::BLUE))
            << ","
            << static_cast<uint32_t>(pixel.get_channel(rgba_channel::ALPHA))
            << "," << pixel.get_pixel() << endl;
        return (out);
    }

    /**
     * @brief Getter method for rgba value of pixel
     * @param void
     * @return RGBA value of pixel
     */
    uint32_t get_pixel(void) const;

    /**
     * @brief Getter method for RGBA channel of pixel
     * @param channel RGBA channel
     * @return RGBA channel of pixel
     */
    uint8_t get_channel(const rgba_channel channel) const;

    /**
     * @brief Setter method for rgba value of pixel
     * @param rgba RGBA value of pixel
     * @return void
     */
    void set_pixel(const uint32_t rgba);

    /**
     * @brief Setter method for RGBA channel of pixel
     * @param channel RGBA channel
     * @param value Value of pixel channel
     * @return void
     */
    void set_channel(const rgba_channel channel, const uint8_t value);

  private:
    pixel_t rgba;
};

Pixel::Pixel(uint32_t rgba) { this->rgba.value = rgba; }

// Copy constructor
Pixel::Pixel(const Pixel &pixel) : Pixel(pixel.rgba.value) {}

Pixel &Pixel::operator=(const Pixel &pixel) {
    rgba = pixel.rgba;
    return (*this);
}

bool Pixel::operator==(const Pixel &pixel) const {
    return (rgba.value == pixel.rgba.value);
}

uint32_t Pixel::get_pixel(void) const { return (rgba.value); }

uint8_t Pixel::get_channel(const rgba_channel channel) const {
    uint8_t value = 0;

    switch (channel) {
    case rgba_channel::RED:
        value = rgba.bytes[0];
        break;
    case rgba_channel::GREEN:
        value = rgba.bytes[1];
        break;
    case rgba_channel::BLUE:
        value = rgba.bytes[2];
        break;
    case rgba_channel::ALPHA:
        value = rgba.bytes[3];
        break;
    default:
        throw invalid_argument("Invalid channel");
        break;
    }

    return (value);
}

void Pixel::set_pixel(const uint32_t rgba) { this->rgba.value = rgba; }

void Pixel::set_channel(const rgba_channel channel, const uint8_t value) {
    switch (channel) {
    case rgba_channel::RED:
        rgba.bytes[0] = value;
        break;
    case rgba_channel::GREEN:
        rgba.bytes[1] = value;
        break;
    case rgba_channel::BLUE:
        rgba.bytes[2] = value;
        break;
    case rgba_channel::ALPHA:
        rgba.bytes[3] = value;
        break;
    default:
        throw invalid_argument("Invalid channel");
        break;
    }
}

#endif // PIXEL_H
