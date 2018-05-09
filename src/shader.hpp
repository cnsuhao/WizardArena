#ifndef SHADER_H
#define SHADER_H
#include "includes.hpp"

class Shader {
 public:
  Shader(string shaderName, vector<string> uniformNames);
  ~Shader();

  std::map<string, uint> GetUniforms() { return uniforms; };
  void                   Activate();
  static void            Deactivate();

 private:
  std::map<string, uint> uniforms;
};

#endif  // SHADER_H
