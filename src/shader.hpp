#ifndef SHADER_H
#define SHADER_H
#include "includes.hpp"

class Shader {
 public:
  Shader(string shaderName);
  ~Shader();

  void Activate();

  static void Deactivate();
};

#endif  // SHADER_H
