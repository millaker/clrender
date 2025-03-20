#ifndef OBJPARSER_H
#define OBJPARSER_H

#include <string>
#include <vector>
#include "Geometry.h"
#include "gmtl/gmtl.h"

class ObjParser {
 public:
  bool Load(std::string);
  const std::vector<Triangle>& GetList();

 private:
  std::vector<Triangle> tlist_;
  std::vector<gmtl::Vec3f> vertices_;
  std::vector<gmtl::Vec2f> uvs_;
  std::vector<gmtl::Vec3f> normals_;

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
