#include "ObjParser.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include "fmt/format.h"

bool ObjParser::Load(std::string filename) {
  std::ifstream f(filename, std::ifstream::in);
  if (!f.is_open()) {
    fmt::print("Unablt to open {}\n", filename);
    return false;
  }

  tlist_.clear();
  vertices_.clear();
  uvs_.clear();
  normals_.clear();

  int line_count = 1;
  for (std::string line; std::getline(f, line);) {
    /* Parse line */
    auto toks = split_line(line, ' ');

    if (toks.size() == 0)
      continue;

    /* Compare first token to determine type */
    auto res = SUCCESS;
    if (toks[0] == "v") {
      res = parse_vertex(toks);
    } else if (toks[0] == "vn") {
      res = parse_normal(toks);
    } else if (toks[0] == "vt") {
      res = parse_uv(toks);
    } else if (toks[0] == "f") {
      res = parse_face(toks);
    }

    if (res != SUCCESS) {
      fmt::print("Parse error at line {}: ", line_count);
      switch (res) {
        case INVALID_INDEX:
          fmt::print("Invalid index\n");
          break;
        case INVALID_NUMBER:
          fmt::print("Invalid number\n");
          break;
        case INVALID_SYNTAX:
          fmt::print("Invalid syntax\n");
          break;
        default:
          assert(0);
          break;
      }
      return false;
    }

    line_count++;
  }
  fmt::print("Successfully parsed {} with {} triangles\n", filename,
             tlist_.size());
  return true;
}

std::vector<std::string> ObjParser::split_line(const std::string& in,
                                               char delim, bool skip) {
  std::vector<std::string> res;
  size_t start = 0, pos;
  while (true) {
    pos = in.find_first_of(delim, start);
    std::string tok = in.substr(start, pos - start);
    if (!skip || tok.length() > 0)
      res.push_back(tok);
    if (pos == std::string::npos)
      break;
    start = pos + 1;
  }
  return res;
}

const std::vector<Triangle>& ObjParser::GetList() {
  return tlist_;
}

ObjParser::ParseError ObjParser::parse_vertex(
    const std::vector<std::string>& tok) {
  assert(tok[0] == "v" && "Line type should be v");
  if (tok.size() != 4)
    return INVALID_SYNTAX;

  gmtl::Vec3f tmp;
  try {
    tmp[0] = std::stof(tok[1]);
    tmp[1] = std::stof(tok[2]);
    tmp[2] = std::stof(tok[3]);
  } catch (std::invalid_argument) {
    return INVALID_NUMBER;
  }
  vertices_.push_back(tmp);
  return SUCCESS;
}

ObjParser::ParseError ObjParser::parse_normal(
    const std::vector<std::string>& tok) {
  assert(tok[0] == "vn" && "Line type should be vn");
  if (tok.size() != 4)
    return INVALID_SYNTAX;

  gmtl::Vec3f tmp;
  try {
    tmp[0] = std::stof(tok[1]);
    tmp[1] = std::stof(tok[2]);
    tmp[2] = std::stof(tok[3]);
  } catch (std::invalid_argument) {
    return INVALID_NUMBER;
  }
  normals_.push_back(tmp);
  return SUCCESS;
}

ObjParser::ParseError ObjParser::parse_uv(const std::vector<std::string>& tok) {
  assert(tok[0] == "vt" && "Line type should be uv");
  if (tok.size() != 3)
    return INVALID_SYNTAX;

  gmtl::Vec2f tmp;
  try {
    tmp[0] = std::stof(tok[1]);
    tmp[1] = std::stof(tok[2]);
  } catch (std::invalid_argument) {
    return INVALID_NUMBER;
  }
  uvs_.push_back(tmp);
  return SUCCESS;
}

ObjParser::ParseError ObjParser::parse_face(
    const std::vector<std::string>& tok) {
  assert(tok[0] == "f" && "Line type should be f");
  /* Assume triangulated model */
  if (tok.size() != 4)
    return INVALID_SYNTAX;

  Triangle tmp;
  /* Count number of tokens and parse with different strat */
  for (int i = 0; i < 3; i++) {
    auto toks = split_line(tok[i + 1], '/', false);
    assert(toks.size() > 0 && toks.size() <= 3);

    int vidx = -1, vtidx = -1, vnidx = -1;

    try {
      /* f v1 v2 v3 */
      if (toks.size() == 1) {
        vidx = std::stoi(toks[0]) - 1;
      }

      /* f v1/vt1 v2/vt2 v3/vt3 */
      if (toks.size() == 2) {
        vidx = std::stoi(toks[0]) - 1;
        vtidx = std::stoi(toks[1]) - 1;
      }

      /*
        f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3
        f v1//vn1 v2//vn2 v3//vn3
      */
      if (toks.size() == 3) {
        vidx = std::stoi(toks[0]) - 1;
        if (toks[1] != "") {
          vtidx = std::stoi(toks[1]) - 1;
        }
        if (toks[2] != "") {
          vnidx = std::stoi(toks[2]) - 1;
        }
      }
    } catch (std::invalid_argument) {
      return INVALID_NUMBER;
    }

    assert(vidx != -1 && "Face should always have a vertex index");
    if (vidx >= vertices_.size())
      return INVALID_INDEX;
    if (vtidx != -1 && vtidx >= uvs_.size())
      return INVALID_INDEX;
    if (vnidx != -1 && vnidx >= normals_.size())
      return INVALID_INDEX;

    tmp.vertices[i] = vertices_[vidx];
    if (vtidx != -1) {
      tmp.uvs[i] = uvs_[vtidx];
    }

    if (vnidx != -1) {
      tmp.normals[i] = normals_[vnidx];
    }
  }
  tlist_.push_back(tmp);
  return SUCCESS;
}
