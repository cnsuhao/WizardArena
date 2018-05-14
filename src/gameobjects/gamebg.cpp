#include "gamebg.hpp"

GameBG::GameBG() {
  image = new Image("Content/Textures/GameBG.png", globals->vwidth / 2,
                    globals->vheight / 2);
  GPU_SetImageFilter(image->getImage(), GPU_FILTER_NEAREST);
  GPU_SetWrapMode(image->getImage(), GPU_WRAP_REPEAT, GPU_WRAP_REPEAT);
  image->size = vec2(3.0);

  // Load shader
  shader   = new Shader("SkyBG", {"time"});
  uniforms = shader->GetUniforms();
}

GameBG::~GameBG() {
  delete image;
  delete shader;
}
void GameBG::Draw() {
  shader->Activate();
  GPU_SetUniformf(uniforms["time"], globals->Time);
  image->Draw();
  shader->Deactivate();
}

