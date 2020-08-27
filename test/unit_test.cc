#include "gtest/gtest.h"
#include "../include/tgaimage.h"


const TGAColor white = TGAColor(255, 255, 255, 255);

void line(int32_t x_0, int32_t y_0, int32_t x_1, int32_t y_1, TGAImage &image, TGAColor color) {
  for (int32_t t = 0; t <= 100; t++) {
    int32_t x = x_0 + float (t * (x_1 - x_0) / 100);
    int32_t y = y_0 + float (t * (y_1 - y_0) / 100);
    image.set(x, y, color);
  }
}

TEST(LineDrawingTests, ShouldDrawSingleLine) {
  TGAImage image(320, 240, TGAImage::RGB);

  line(0, 0, 200, 100, image, white);
  image.flip_vertically();
  image.write_tga_file("output.tga");
}