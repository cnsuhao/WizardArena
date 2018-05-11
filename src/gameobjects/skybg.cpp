#include "skybg.hpp"

SkyBG::SkyBG() {
  // Load image
  sky = GPU_LoadImage("Content/Textures/SkyBG.png");
  GPU_SetImageFilter(sky, GPU_FILTER_NEAREST);
  GPU_SetWrapMode(sky, GPU_WRAP_MIRRORED, GPU_WRAP_MIRRORED);

  // Fill screen
  rects.x = 0;
  rects.y = 0;
  rects.w = globals->vwidth;
  rects.h = globals->vheight;

  // Load shader
  shader   = new Shader("SkyBG", {"time"});
  uniforms = shader->GetUniforms();
}

SkyBG::~SkyBG() {
  GPU_FreeImage(sky);
  delete shader;
}

void SkyBG::Draw() {
  shader->Activate();
  GPU_SetUniformf(uniforms["time"], globals->Time);
  GPU_BlitRect(sky, nullptr, globals->backbuffer, &rects);
  shader->Deactivate();
}

void SkyBG::Update() {}
