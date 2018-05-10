#ifndef SHADER_H
#define SHADER_H
#include "includes.hpp"

/** This is the shader class*/
class Shader {
 public:
  /** The shader constructor
      @param shaderName Shader name, which is used to find shader files.
      @param uniformNames List of uniform names to get locations of.
  */
  Shader(string shaderName, vector<string> uniformNames);

  /** The shader destructor */
  ~Shader();

  /** Get map of uniforms */
  std::map<string, uint> GetUniforms() { return uniforms; };

  /** This function activates the shader*/
  void Activate();

  /** This function deactivates all shaders */
  static void Deactivate();

 private:
  std::map<string, uint> uniforms;

  // Shader ids and shaderblock
  uint shaderID[2];
  uint programID;

  GPU_ShaderBlock shaderBlock;

  // Shader types
  enum ShaderTypes { VERTEX = 0, FRAGMENT = 1 };
};

#endif  // SHADER_H
