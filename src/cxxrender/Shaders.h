#ifndef SHADERS_H
#define SHADERS_H

#include "CXXPipe.h"

struct PassThruShader : ShaderBase {
  void VertexShader(int idx, const glm::vec3& vert, glm::vec4& gl_Position,
                    void* meta) override {
    gl_Position = glm::vec4(vert, 1.0f);
  }
  void FragmentShader(const glm::vec3& bary, glm::vec4& gl_FragColor) override {
    gl_FragColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
  }
};

struct ShadingShader : ShaderBase {
  void VertexShader(int idx, const glm::vec3& vert, glm::vec4& gl_Position,
                    void* meta) override {
    switch (idx) {
      case 0:
        colors_[0] = glm::vec3(1, 0, 0);
        break;
      case 1:
        colors_[1] = glm::vec3(0, 1, 0);
        break;
      case 2:
        colors_[2] = glm::vec3(0, 0, 1);
        break;
    }
    gl_Position = glm::vec4(vert, 1.0f);
  }
  /* Intermediates */
  glm::vec3 colors_[3];

  void FragmentShader(const glm::vec3& bary, glm::vec4& gl_FragColor) override {
    float r = 0, g = 0, b = 0;
    glm::vec3 c = bary[0] * colors_[0];
    c += bary[1] * colors_[1];
    c += bary[2] * colors_[2];

    gl_FragColor = glm::vec4(c, 1.0f);
  }
};

#endif
