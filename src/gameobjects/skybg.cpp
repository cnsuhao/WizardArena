#include "skybg.hpp"

SkyBG::SkyBG() {
  sky = GPU_LoadImage("Content/Textures/SkyBG.png");
  for (int i = 0; i < 2; i++) {
    rects[i].x = globals->vwidth * i;
    rects[i].x -= globals->vwidth;
    rects[i].y = 0;
    rects[i].w = globals->vwidth + i;
    rects[i].h = globals->vheight;
  }
  rects[0].x++;
  GPU_SetImageFilter(sky, GPU_FILTER_NEAREST);
}

SkyBG::~SkyBG() { GPU_FreeImage(sky); }

void SkyBG::Draw() {
  GPU_BlitRect(sky, nullptr, globals->window, &rects[0]);
  GPU_BlitRect(sky, nullptr, globals->window, &rects[1]);
}

void SkyBG::Update() {
  for (int i = 0; i < 2; i++) {
    rects[i].x += 20.0 * globals->DeltaTime;
    if (rects[i].x >= globals->vwidth) {
      rects[i].x -= (2 * globals->vwidth) - 1;
    }
  }
}
