#include "CXXPipe.h"
#include "ObjParser.h"
#include "Shaders.h"

#include <iostream>
#include <string>
#include "fmt/format.h"

int main() {
  CXXPipe CP;
  FrameBuffer fb(320, 320);
  ShadingShader pts;
  PassThruShader pass;
  fb.ClearBuffer();
  CP.ViewPort(320 / 10, 320 / 10, 320 * 9 / 10, 320 * 9 / 10);
  CP.SetFrameBuffer(&fb);
  CP.SetShader(&pts);

  CP.ClearBuffer();

  std::vector<Triangle> tlist;
  Triangle t;
  t.vertices[0] = glm::vec3(-1, -1, 0);
  t.vertices[1] = glm::vec3(0.5, -0.5, 0);
  t.vertices[2] = glm::vec3(0, 1, 0);
  tlist.push_back(t);
  CP.Render(tlist);

  t.vertices[0] = glm::vec3(-1, 1, -1);
  t.vertices[1] = glm::vec3(-1, -0.5, -1);
  t.vertices[2] = glm::vec3(1, 0, 1);
  tlist[0] = t;
  CP.SetShader(&pass);
  CP.Render(tlist);

  fb.SaveToPng("tri.png");

  return 0;
}
