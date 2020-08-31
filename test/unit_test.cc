#include "gtest/gtest.h"
#include "../include/tgaimage.h"


static uint8_t line_implementation = 0;
const TGAColor white = TGAColor(255, 255, 255, 255);

void line_implementation_0(int32_t x_0, int32_t y_0, int32_t x_1, int32_t y_1, TGAImage &image, TGAColor color) {
  for (int32_t t = 0; t <= 100; t++) {
    int32_t x = x_0 + float (t * (x_1 - x_0) / 100);
    int32_t y = y_0 + float (t * (y_1 - y_0) / 100);
    image.set(x, y, color);
  }
}

void line_implementation_1(int32_t x_0, int32_t y_0, int32_t x_1, int32_t y_1, TGAImage &image, TGAColor color) {

}

void line(int32_t x_0, int32_t y_0, int32_t x_1, int32_t y_1, TGAImage &image, TGAColor color) {
  if (!line_implementation)
    line_implementation_0(x_0, y_0, x_1, y_1, image, color);
  else if (line_implementation == 1)
    line_implementation_1(x_0, y_0, x_1, y_1, image, color);
}

TEST(LineDrawingTests, ShouldDrawSingleLine) {
  line_implementation = 0;
  TGAImage image_0(320, 240, TGAImage::RGB);
  line(0, 0, 200, 100, image_0, white);
  image_0.flip_vertically();
  image_0.write_tga_file("output_line0.tga");

  line_implementation = 1;
  TGAImage image_1(320, 240, TGAImage::RGB);
  line(0, 0, 200, 100, image_1, white);
  image_1.flip_vertically();
  image_1.write_tga_file("output_line1.tga");
}