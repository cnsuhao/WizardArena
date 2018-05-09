#ifndef SHADER_H
#define SHADER_H
#include "includes.hpp"

/** This is the shader class*/
class Shader {
 public:
  /** The shader constructor
      @param that takes in the shader name.
  */
  Shader(string shaderName, vector<string> uniformNames);

  /** The shader destructor */
  ~Shader();

  std::map<string, uint> GetUniforms() { return uniforms; };
  /** This function activates the shader*/
  void Activate();
  /** This function deactivates all shaders */
  static void Deactivate();

 private:
  std::map<string, uint> uniforms;
};

#endif  // SHADER_H
