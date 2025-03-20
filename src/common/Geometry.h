#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <array>
#include <iostream>
#include <optional>
#include "fmt/ostream.h"
#include "gmtl/gmtl.h"

struct Triangle {
  std::array<gmtl::Vec3f, 3> vertices;
  std::array<gmtl::Vec2f, 3> uvs;
  std::array<gmtl::Vec3f, 3> normals;
  friend std::ostream& operator<<(std::ostream& os, const Triangle& t) {
    os << t.vertices[0] << " " << t.vertices[1] << " " << t.vertices[2];
    return os;
  }
};

template <>
struct fmt::formatter<Triangle> : ostream_formatter {};

#endif
