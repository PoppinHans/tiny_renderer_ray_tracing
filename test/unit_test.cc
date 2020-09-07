#include "gtest/gtest.h"
#include "../include/tgaimage.h"
#include "../include/model.h"
#include "../include/geometry.h"


static uint8_t line_implementation = 0;
const TGAColor white = TGAColor(255, 255, 255, 255);

void line_implementation_0(int32_t x0, int32_t y0, int32_t x1, int32_t y1, TGAImage &image, TGAColor color) {
  for (int32_t t = 0; t <= 100; t++) {
    int32_t x = x0 + float (t * (x1 - x0) / 100);
    int32_t y = y0 + float (t * (y1 - y0) / 100);
    image.set(x, y, color);
  }
}

void line_implementation_1(int32_t x0, int32_t y0, int32_t x1, int32_t y1, TGAImage &image, TGAColor color) {
  bool is_steep = false;
  if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
    is_steep = true;
    std::swap(x0, y0);
    std::swap(x1, y1);
  }
  if (x0 > x1) {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }
  int32_t dx = x1 - x0;
  int32_t dy = y1 - y0;
  int32_t d_error = std::abs(dy) * 2;
  int32_t error = 0;
  int32_t y = y0;

  for (int x = x0; x <= x1; x++) {
    if (is_steep)
      image.set(y, x, color);
    else
      image.set(x, y, color);

    error += d_error;
    if (error > dx) {
      y += (y1 > y0 ? 1 : -1);
      error -= dx * 2;
    }
  }
}

void line(int32_t x0, int32_t y0, int32_t x1, int32_t y1, TGAImage &image, TGAColor color) {
  if (!line_implementation)
    line_implementation_0(x0, y0, x1, y1, image, color);
  else if (line_implementation == 1)
    line_implementation_1(x0, y0, x1, y1, image, color);
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

TEST(WireFrameTests, ShouldDrawWireFrame) {
  Model model("../obj/african_head/african_head.obj");

  line_implementation = 1;
  uint32_t width = 800, height = 800;
  TGAImage image(width, height, TGAImage::RGB);
  uint32_t n_faces = model.nfaces();

  for (int i = 0; i < n_faces; i++) {
    const std::vector<int> &face = model.face(i);
    for (int j = 0; j < 3; j++) {
       Vec3f v0 = model.vert(face[j]);
       Vec3f v1 = model.vert(face[(j + 1) % 3]);
       int x0 = (v0.x + 1) * width / 2;
       int y0 = (v0.y + 1) * height / 2;
       int x1 = (v1.x + 1) * width / 2;
       int y1 = (v1.y + 1) * height / 2;

       line_implementation_1(x0, y0, x1, y1, image, white);
    }
  }

  image.flip_vertically();
  image.write_tga_file("output_model.tga");
}