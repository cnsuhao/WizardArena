#include "shader.hpp"
Shader::Shader(string shaderName, vector<string> uniformNames) {
  // Initialize uniform map
  uniforms = std::map<string, uint>();

  // Load shaders
  shaderID[VERTEX] = GPU_LoadShader(
      GPU_VERTEX_SHADER, ("Content/Shaders/" + shaderName + ".vert").c_str());
  shaderID[FRAGMENT] = GPU_LoadShader(
      GPU_FRAGMENT_SHADER, ("Content/Shaders/" + shaderName + ".frag").c_str());

  // Create shader program
  programID = GPU_CreateShaderProgram();

  // Link shaders
  GPU_LinkShaders(shaderID[VERTEX], shaderID[FRAGMENT]);

  // Attach shaders
  GPU_AttachShader(programID, shaderID[VERTEX]);
  GPU_AttachShader(programID, shaderID[FRAGMENT]);

  // Link shader program
  GPU_LinkShaderProgram(programID);

#ifdef DEBUG
  // Print shader message
  printf("Shader message: %s\n", GPU_GetShaderMessage());
#endif

  // Get attributes and uniforms
  // Load shader block
  shaderBlock =
      GPU_LoadShaderBlock(programID, "gpu_Vertex", "gpu_TexCoords", "gpu_Color",
                          "gpu_ModelViewProjectionMatrix");
  // Load uniforms
  for (uint i = 0; i < uniformNames.size(); i++) {
    uniforms[uniformNames[i].c_str()] =
        GPU_GetUniformLocation(programID, uniformNames[i].c_str());
  }
}

Shader::~Shader() {
  // Free shaders
  GPU_FreeShader(shaderID[VERTEX]);
  GPU_FreeShader(shaderID[FRAGMENT]);

  // Free shader program
  GPU_FreeShaderProgram(programID);
}

void Shader::Activate() { GPU_ActivateShaderProgram(programID, &shaderBlock); }

void Shader::Deactivate() { GPU_DeactivateShaderProgram(); };
