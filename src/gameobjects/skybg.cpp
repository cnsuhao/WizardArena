#include "skybg.hpp"

SkyBG::SkyBG() {
  sky = GPU_LoadImage("Content/Textures/SkyBG.png");

  rects.x = 0;
  rects.y = 0;
  rects.w = globals->vwidth;
  rects.h = globals->vheight;

  GPU_SetImageFilter(sky, GPU_FILTER_NEAREST);
}

SkyBG::~SkyBG() { GPU_FreeImage(sky); }

void SkyBG::Draw() { GPU_BlitRect(sky, nullptr, globals->window, &rects); }

void SkyBG::Update() {}
