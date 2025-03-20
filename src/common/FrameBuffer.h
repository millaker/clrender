#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <string>
#include "Color.h"

/*
  The origin in OpenGL is located at the botton left corner of the frame.
*/

class FrameBuffer {
 public:
  FrameBuffer();
  FrameBuffer(int width, int height);
  ~FrameBuffer();
  /* ClearBuffer */
  void ClearBuffer();
  /* PutPixel */
  void PutPixel(int x, int y, const Color& c);
  /* SaveToFile */
  bool SaveToPng(const std::string&);
  int width;
  int height;

 private:
  Color* buf_;
};

#endif
