#ifndef SHADER_H
#define SHADER_H
#include "includes.hpp"

/** This is the shader class*/
class Shader {
 public:
  /** The shader constructor
   @param that takes in the shader name.
   */
  Shader(string shaderName);
  /** The shader destructor */
  ~Shader();

  /** This function activates the shader*/
  void Activate();

  /** This function deactivates all shaders */
  static void Deactivate();
};

#endif  // SHADER_H
