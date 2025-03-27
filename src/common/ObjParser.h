#ifndef OBJPARSER_H
#define OBJPARSER_H

#include <string>
#include <vector>
#include "Geometry.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

class ObjParser {
 public:
  bool Load(std::string);
  const std::vector<Triangle>& GetList();

 private:
  std::vector<Triangle> tlist_;
  std::vector<glm::vec3> vertices_;
  std::vector<glm::vec2> uvs_;
  std::vector<glm::vec3> normals_;

  enum ParseError {
    SUCCESS = 0,
    INVALID_INDEX,
    INVALID_NUMBER,
    INVALID_SYNTAX
  };

  /* Split line into tokens */
  std::vector<std::string> split_line(const std::string& in, char delim,
                                      bool skip = true);
  ParseError parse_vertex(const std::vector<std::string>& tok);
  ParseError parse_face(const std::vector<std::string>& tok);
  ParseError parse_normal(const std::vector<std::string>& tok);
  ParseError parse_uv(const std::vector<std::string>& tok);
};

#endif
