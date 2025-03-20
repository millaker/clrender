#include "FrameBuffer.h"
#include <cassert>
#include <cstdint>
#include "Color.h"
#include "fmt/format.h"

FrameBuffer::FrameBuffer() {
  buf_ = new Color[1080 * 1080];
  width = 1080;
  height = 1080;
}

FrameBuffer::FrameBuffer(int width, int height) {
  assert(width > 0 && height > 0);
  buf_ = new Color[width * height];
  this->width = width;
  this->height = height;
}

FrameBuffer::~FrameBuffer() {
  delete[] buf_;
}

void FrameBuffer::ClearBuffer() {
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      buf_[j * width + i] = Color();
    }
  }
}

void FrameBuffer::PutPixel(int x, int y, const Color& c) {
  /* Ignore out of bound access */
  if (x < 0 || x >= width || y < 0 || y >= height)
    return;
  buf_[(height - 1 - y) * width + x] = c;
}

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

bool FrameBuffer::SaveToPng(const std::string& filename) {
  uint8_t* ubuf = new uint8_t[width * height * 3];
  if (!ubuf)
    return false;
  for (int i = 0; i < width * height; i++) {
    ubuf[i * 3] = buf_[i].r;
    ubuf[i * 3 + 1] = buf_[i].g;
    ubuf[i * 3 + 2] = buf_[i].b;
  }

  /* comp = number of channels, rgb here */
  /* stride_bytes = comp * channel */
  int res = stbi_write_png(filename.c_str(), width, height, 3, ubuf, 3 * width);
  delete[] ubuf;
  if (!res)
    return false;
  return true;
}
