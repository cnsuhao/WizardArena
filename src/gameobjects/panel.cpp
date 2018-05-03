#include "panel.hpp"

Panel::Panel() {
  panel              = GPU_CreateImage(32, 32, GPU_FORMAT_RGBA);
  GPU_Target* target = GPU_LoadTarget(panel);
  GPU_ClearRGBA(target, 0, 0, 0, 128);
  GPU_FreeTarget(target);
  position = vec2(globals->vwidth / 2.0, globals->vheight / 2.0);
}

Panel::Panel(SDL_Color color) {
  panel              = GPU_CreateImage(32, 32, GPU_FORMAT_RGBA);
  GPU_Target* target = GPU_LoadTarget(panel);
  GPU_ClearRGBA(target, color.r, color.g, color.b, color.a);
  GPU_FreeTarget(target);
}

Panel::~Panel() { GPU_FreeImage(panel); }

void Panel::Draw() {
  GPU_Rect dest = {position.x - (size.x / 2), position.y - (size.y / 2), size.x,
                   size.y};
  GPU_BlitRect(panel, nullptr, globals->window, &dest);
}
