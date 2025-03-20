#include "ObjParser.h"

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

  return 0;
}
