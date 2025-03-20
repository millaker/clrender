#ifndef COLOR_H
#define COLOR_H

#include <cstdint>
#include <iostream>
#include "fmt/ostream.h"

class Color {
 public:
  uint8_t r, g, b;
  Color() {
    r = 0;
    g = 0;
    b = 0;
  }

  Color(uint32_t c) {
    r = (c >> 16) & 0xff;
    g = (c >> 8) & 0xff;
    b = c & 0xff;
  }

  Color(uint32_t r, uint32_t g, uint32_t b) {
    this->r = r > 255 ? 255 : r;
    this->g = g > 255 ? 255 : g;
    this->b = b > 255 ? 255 : b;
  }

  uint32_t asUInt() const {
    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
  }

  Color operator*(float f) const {
    uint32_t nr = r * f;
    uint32_t ng = g * f;
    uint32_t nb = b * f;
    return Color{nr, ng, nb};
  }

  Color operator+(const Color& c) const {
    uint8_t nr = r + c.r;
    uint8_t ng = g + c.g;
    uint8_t nb = b + c.b;
    return Color{nr, ng, nb};
  }

  /* Some command colors */
  static Color Red() { return Color(255, 0, 0); }
  static Color Green() { return Color(0, 255, 0); }
  static Color Blue() { return Color(0, 0, 255); }
  static Color White() { return Color(255, 255, 255); }
  static Color Black() { return Color(0, 0, 0); }

  friend std::ostream& operator<<(std::ostream& os, const Color& c) {
    os << "(" << (int)c.r << ", " << (int)c.g << ", " << (int)c.b << ")";
    return os;
  }
};

template <>
struct fmt::formatter<Color> : ostream_formatter {};

#endif
