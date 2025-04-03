#ifndef CXXPIPE_H
#define CXXPIPE_H

#include <vector>
#include "Color.h"
#include "FrameBuffer.h"
#include "Geometry.h"
#include "glm/mat4x4.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

struct ShaderBase {
  virtual void VertexShader(int idx, const glm::vec3& vert,
                            glm::vec4& gl_Position, void* meta) = 0;
  virtual void FragmentShader(const glm::vec3& bary,
                              glm::vec4& gl_FragColor) = 0;
};

class CXXPipe {
 public:
  void ViewPort(const int x, const int y, const int width, const int height);
  void SetShader(ShaderBase*);
  void SetFrameBuffer(FrameBuffer*);
  void Render(const std::vector<Triangle>& tlist);

 private:
  glm::vec3 barycentric(const glm::ivec2 tri_verts[3], const glm::ivec2 P);

  ShaderBase* shader_ = nullptr;
  FrameBuffer* fb_ = nullptr;
  glm::mat4 mvp_;
};

#endif
