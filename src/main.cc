#include "CXXPipe.h"
#include "ObjParser.h"
#include "Shaders.h"

#include <iostream>
#include <string>
#include "fmt/format.h"

int main() {
  ObjParser o;
  bool res = o.Load("a.obj");
  if (!res)
    return -1;

  auto& tl = o.GetList();
  for (auto& t : tl) {
    fmt::print("Triangle {}\n", t);
  }

  CXXPipe CP;
  FrameBuffer fb(320, 320);
  ShadingShader pts;
  fb.ClearBuffer();
  CP.ViewPort(320 / 10, 320 / 10, 320 * 9 / 10, 320 * 9 / 10);
  CP.SetFrameBuffer(&fb);
  CP.SetShader(&pts);

  std::vector<Triangle> tlist;
  Triangle t;
  t.vertices[0] = glm::vec3(-1, -1, 0);
  t.vertices[1] = glm::vec3(0.5, -0.5, 0);
  t.vertices[2] = glm::vec3(0, 1, 0);
  tlist.push_back(t);

  CP.Render(tlist);
  fb.SaveToPng("tri.png");

  return 0;
}
