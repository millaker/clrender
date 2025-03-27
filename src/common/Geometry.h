#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <array>
#include <iostream>
#include <optional>
#include "fmt/ostream.h"
#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"

struct Triangle {
  std::array<glm::vec3, 3> vertices;
  std::array<glm::vec2, 3> uvs;
  std::array<glm::vec3, 3> normals;
  friend std::ostream& operator<<(std::ostream& os, const Triangle& t) {
    os << t.vertices[0] << " " << t.vertices[1] << " " << t.vertices[2];
    return os;
  }
};

template <>
struct fmt::formatter<Triangle> : ostream_formatter {};

#endif
