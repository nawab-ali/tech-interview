/**
 * @file unit_tests.cpp
 * @brief This file implements the unit tests.
 * @author Nawab Ali
 */

#include "Image.h"
#include "Pixel.h"
#include <gtest/gtest.h>

// Unit tests for Pixel class
TEST(BoxBlurFilterTest, PixelDefaultConstructor) {
    Pixel pixel(255);
    ASSERT_EQ(pixel.get_pixel(), 255);
}

TEST(BoxBlurFilterTest, PixelDefaultConstructorNoValue) {
    Pixel pixel;
    ASSERT_EQ(pixel.get_pixel(), 0);
}

TEST(BoxBlurFilterTest, PixelCopyConstructor) {
    Pixel pixel_1(255);
    Pixel pixel_2 = pixel_1;
    ASSERT_EQ(pixel_1, pixel_2);
}

TEST(BoxBlurFilterTest, PixelOverloadAssignmentOperator) {
    Pixel pixel_1(255);
    Pixel pixel_2(0);

    pixel_2 = pixel_1;
    ASSERT_EQ(pixel_1, pixel_2);
}

TEST(BoxBlurFilterTest, PixelSetGetRedChannel) {
    Pixel pixel;

    pixel.set_channel(rgba_channel::RED, 255);
    uint8_t value = pixel.get_channel(rgba_channel::RED);

    ASSERT_EQ(value, 255);
}

TEST(BoxBlurFilterTest, PixelSetGetGreenChannel) {
    Pixel pixel;

    pixel.set_channel(rgba_channel::GREEN, 5);
    uint8_t value = pixel.get_channel(rgba_channel::GREEN);

    ASSERT_EQ(value, 5);
}

TEST(BoxBlurFilterTest, PixelSetGetBlueChannel) {
    Pixel pixel;

    pixel.set_channel(rgba_channel::BLUE, 128);
    uint8_t value = pixel.get_channel(rgba_channel::BLUE);

    ASSERT_EQ(value, 128);
}

TEST(BoxBlurFilterTest, PixelSetGetAlphaChannel) {
    Pixel pixel;

    pixel.set_channel(rgba_channel::ALPHA, 64);
    uint8_t value = pixel.get_channel(rgba_channel::ALPHA);

    ASSERT_EQ(value, 64);
}

// Unit tests for Image class
TEST(BoxBlurFilterTest, ImageConstructor1) {
    Image image(4, 5);
    vector<vector<Pixel>> pixels;

    for (int i = 0; i < 4; i++) {
        vector<Pixel> v;
        for (int j = 0; j < 5; j++) {
            Pixel pixel;
            v.push_back(pixel);
        }
        pixels.push_back(v);
    }

    ASSERT_EQ(image.get_height(), 4);
    ASSERT_EQ(image.get_width(), 5);
    ASSERT_EQ(image.get_pixels(), pixels);
}

TEST(BoxBlurFilterTest, ImageConstructor2) {
    vector<vector<Pixel>> pixels;

    for (int i = 0; i < 4; i++) {
        vector<Pixel> v;
        for (int j = 0; j < 5; j++) {
            Pixel pixel;
            v.push_back(pixel);
        }
        pixels.push_back(v);
    }

    Image image(pixels);

    ASSERT_EQ(image.get_height(), 4);
    ASSERT_EQ(image.get_width(), 5);
    ASSERT_EQ(image.get_pixels(), pixels);
}

TEST(BoxBlurFilterTest, ImageConstructor3) {
    vector<vector<Pixel>> pixels;
    Image image(pixels);

    ASSERT_EQ(image.get_height(), 0);
    ASSERT_EQ(image.get_width(), 0);
    ASSERT_EQ(image.get_pixels(), pixels);
}

TEST(BoxBlurFilterTest, ImageCopyConstructor) {
    Image image1(4, 5);
    Image image2 = image1;

    ASSERT_EQ(image1, image2);
}

TEST(BoxBlurFilterTest, ImageOverloadAssignmentOperator) {
    Image image1(4, 5);
    Image image2;

    image2 = image1;

    ASSERT_EQ(image1, image2);
}

TEST(BoxBlurFilterTest, ImageSetGetPixel) {
    Pixel pixel(255);
    Image image(4, 5);

    image.set_pixel(2, 3, pixel);

    ASSERT_EQ(image.get_pixel(2, 3), pixel);
}

TEST(BoxBlurFilterTest, ImageSetPixelIEqualToHeight) {
    Pixel pixel(255);
    Image image(4, 5);

    EXPECT_THROW(image.set_pixel(4, 3, pixel), invalid_argument);
}

TEST(BoxBlurFilterTest, ImageSetPixelIEqualToNegativeOne) {
    Pixel pixel(255);
    Image image(4, 5);

    EXPECT_THROW(image.set_pixel(-1, 3, pixel), invalid_argument);
}

TEST(BoxBlurFilterTest, ImageSetPixelJEqualToWidth) {
    Pixel pixel(255);
    Image image(4, 5);

    EXPECT_THROW(image.set_pixel(2, 5, pixel), invalid_argument);
}

TEST(BoxBlurFilterTest, ImageSetPixelJEqualToNegativeOne) {
    Pixel pixel(255);
    Image image(4, 5);

    EXPECT_THROW(image.set_pixel(2, -1, pixel), invalid_argument);
}

TEST(BoxBlurFilterTest, ImageBlurRadiusNegativeOne) {
    vector<vector<Pixel>> pixels;
    vector<Pixel> row0 = {Pixel(0), Pixel(255), Pixel(11), Pixel(128)};
    vector<Pixel> row1 = {Pixel(17), Pixel(5), Pixel(255), Pixel(236)};
    vector<Pixel> row2 = {Pixel(24), Pixel(26), Pixel(31), Pixel(0)};

    pixels.push_back(row0);
    pixels.push_back(row1);
    pixels.push_back(row2);

    Image image(pixels);

    EXPECT_THROW(image.blur(-1), invalid_argument);
}

TEST(BoxBlurFilterTest, ImageBlurRadiusZero) {
    vector<vector<Pixel>> pixels;
    vector<Pixel> row0 = {Pixel(0), Pixel(255), Pixel(11), Pixel(128)};
    vector<Pixel> row1 = {Pixel(17), Pixel(5), Pixel(255), Pixel(236)};
    vector<Pixel> row2 = {Pixel(24), Pixel(26), Pixel(31), Pixel(0)};

    pixels.push_back(row0);
    pixels.push_back(row1);
    pixels.push_back(row2);

    Image image(pixels);

    ASSERT_EQ(image.blur(0), image);
}

TEST(BoxBlurFilterTest, ImageBlurRadiusOne) {
    vector<vector<Pixel>> pixels, blurred_pixels;
    vector<Pixel> row0 = {Pixel(0), Pixel(255), Pixel(11), Pixel(128)};
    vector<Pixel> row1 = {Pixel(17), Pixel(5), Pixel(255), Pixel(236)};
    vector<Pixel> row2 = {Pixel(24), Pixel(26), Pixel(31), Pixel(0)};

    vector<Pixel> blurred_row0 = {Pixel(69), Pixel(90), Pixel(148), Pixel(157)};
    vector<Pixel> blurred_row1 = {Pixel(54), Pixel(69), Pixel(105), Pixel(110)};
    vector<Pixel> blurred_row2 = {Pixel(18), Pixel(59), Pixel(92), Pixel(130)};

    pixels.push_back(row0);
    pixels.push_back(row1);
    pixels.push_back(row2);

    blurred_pixels.push_back(blurred_row0);
    blurred_pixels.push_back(blurred_row1);
    blurred_pixels.push_back(blurred_row2);

    Image image(pixels);
    Image blurred_image(blurred_pixels);

    ASSERT_EQ(image.blur(1), blurred_image);
}

TEST(BoxBlurFilterTest, ImageBlurRadiusTwo) {
    vector<vector<Pixel>> pixels, blurred_pixels;
    vector<Pixel> row0 = {Pixel(0), Pixel(255), Pixel(11), Pixel(128)};
    vector<Pixel> row1 = {Pixel(17), Pixel(5), Pixel(255), Pixel(236)};
    vector<Pixel> row2 = {Pixel(24), Pixel(26), Pixel(31), Pixel(0)};

    vector<Pixel> blurred_row0 = {Pixel(69), Pixel(82), Pixel(82), Pixel(105)};
    vector<Pixel> blurred_row1 = {Pixel(69), Pixel(82), Pixel(82), Pixel(105)};
    vector<Pixel> blurred_row2 = {Pixel(69), Pixel(82), Pixel(82), Pixel(105)};

    pixels.push_back(row0);
    pixels.push_back(row1);
    pixels.push_back(row2);

    blurred_pixels.push_back(blurred_row0);
    blurred_pixels.push_back(blurred_row1);
    blurred_pixels.push_back(blurred_row2);

    Image image(pixels);
    Image blurred_image(blurred_pixels);

    ASSERT_EQ(image.blur(2), blurred_image);
}

TEST(BoxBlurFilterTest, ImageBlurRadiusThree) {
    vector<vector<Pixel>> pixels, blurred_pixels;
    vector<Pixel> row0 = {Pixel(0), Pixel(255), Pixel(11), Pixel(128)};
    vector<Pixel> row1 = {Pixel(17), Pixel(5), Pixel(255), Pixel(236)};
    vector<Pixel> row2 = {Pixel(24), Pixel(26), Pixel(31), Pixel(0)};

    vector<Pixel> blurred_row0 = {Pixel(82), Pixel(82), Pixel(82), Pixel(82)};
    vector<Pixel> blurred_row1 = {Pixel(82), Pixel(82), Pixel(82), Pixel(82)};
    vector<Pixel> blurred_row2 = {Pixel(82), Pixel(82), Pixel(82), Pixel(82)};

    pixels.push_back(row0);
    pixels.push_back(row1);
    pixels.push_back(row2);

    blurred_pixels.push_back(blurred_row0);
    blurred_pixels.push_back(blurred_row1);
    blurred_pixels.push_back(blurred_row2);

    Image image(pixels);
    Image blurred_image(blurred_pixels);

    ASSERT_EQ(image.blur(3), blurred_image);
}

TEST(BoxBlurFilterTest, ImageBlurRadiusFour) {
    vector<vector<Pixel>> pixels, blurred_pixels;
    vector<Pixel> row0 = {Pixel(0), Pixel(255), Pixel(11), Pixel(128)};
    vector<Pixel> row1 = {Pixel(17), Pixel(5), Pixel(255), Pixel(236)};
    vector<Pixel> row2 = {Pixel(24), Pixel(26), Pixel(31), Pixel(0)};

    vector<Pixel> blurred_row0 = {Pixel(82), Pixel(82), Pixel(82), Pixel(82)};
    vector<Pixel> blurred_row1 = {Pixel(82), Pixel(82), Pixel(82), Pixel(82)};
    vector<Pixel> blurred_row2 = {Pixel(82), Pixel(82), Pixel(82), Pixel(82)};

    pixels.push_back(row0);
    pixels.push_back(row1);
    pixels.push_back(row2);

    blurred_pixels.push_back(blurred_row0);
    blurred_pixels.push_back(blurred_row1);
    blurred_pixels.push_back(blurred_row2);

    Image image(pixels);
    Image blurred_image(blurred_pixels);

    ASSERT_EQ(image.blur(4), blurred_image);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return (RUN_ALL_TESTS());
}
