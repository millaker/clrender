#include "CXXPipe.h"
#include <vector>
#include "Geometry.h"
#include "fmt/format.h"

#include "glm.h"

void CXXPipe::Render(const std::vector<Triangle>& tlist) {
  for (auto& t : tlist) {
    /* Run every vertices throught vertex shader */
    glm::vec4 verts[3];
    glm::ivec2 post_vs[3];
    for (int i = 0; i < 3; i++) {
      shader_->VertexShader(i, t.vertices[i], verts[i], nullptr);
      /* Viewport transformation */
      verts[i] = mvp_ * verts[i];
      /* Perspective division */
      post_vs[i] = {verts[i].x / verts[i].w, verts[i].y / verts[i].w};
    }
    /* Rasterize */
    int aabb_xmin = std::min(
        0, std::min(post_vs[0].x, std::min(post_vs[1].x, post_vs[2].x)));
    int aabb_xmax =
        std::min(fb_->width,
                 std::max(post_vs[0].x, std::max(post_vs[1].x, post_vs[2].x)));
    int aabb_ymin = std::min(
        0, std::min(post_vs[0].y, std::min(post_vs[1].y, post_vs[2].y)));
    int aabb_ymax =
        std::min(fb_->height,
                 std::max(post_vs[0].y, std::max(post_vs[1].y, post_vs[2].y)));

    for (int i = aabb_xmin; i < aabb_xmax; i++) {
      for (int j = aabb_ymin; j < aabb_ymax; j++) {
        auto bary = barycentric(post_vs, glm::ivec2(i, j));
        glm::vec4 c;
        shader_->FragmentShader(bary, c);
        if (bary.x < 0 || bary.y < 0 || bary.z < 0)
          continue;
        fb_->PutPixel(i, j, Color(c.x * 255, c.y * 255, c.z * 255));
      }
    }
  }
}

/*
  Transform from canonical coordinates to screen coordinates
  See FCG 8.1.1
  Note: glm::mat is colomn major order
*/
void CXXPipe::ViewPort(const int x, const int y, const int width,
                       const int height) {
  mvp_ = glm::mat4(width / 2, 0, 0, 0, 0, height / 2, 0, 0, 0, 0, 1, 0,
                   (width + x) / 2, (height + y) / 2, 0, 1);
}

void CXXPipe::SetShader(ShaderBase* s) {
  shader_ = s;
}

void CXXPipe::SetFrameBuffer(FrameBuffer* fb) {
  fb_ = fb;
}

/*
  Barycentric coordinate:
  alpha * Ax + beta * Bx + gamma * Cx = Px
  alpha * Ay + beta * By + gamma * Cy = Py
  alpha + beta + gamma = 1

  in matrix form:
  |Ax Bx Cx|   |a|   |Px|
  |Ay By Cy| . |b| = |Py|
  | 1  1  1|   |c|   | 1|

  Solve a b c by multiplying inverse(mABC)

  See: https://ssloy.github.io/tinyrenderer/barycentric/
*/
glm::vec3 CXXPipe::barycentric(const glm::ivec2 tri_verts[3],
                               const glm::ivec2 P) {
  glm::mat3 ABC(glm::vec3{tri_verts[0], 1}, glm::vec3{tri_verts[1], 1},
                glm::vec3{tri_verts[2], 1});
  /* Triangle with no area */
  if (glm::determinant(ABC) <= 0)
    return glm::vec3(-1, 0, 0);
  return glm::inverse(ABC) * glm::vec3{P, 1};
}
