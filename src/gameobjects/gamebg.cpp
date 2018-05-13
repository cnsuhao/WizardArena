#include "gamebg.hpp"

GameBG::GameBG() {
  image = new Image("Content/Textures/GameBG.png", globals->vwidth / 2,
                    globals->vheight / 2);
  GPU_SetImageFilter(image->getImage(), GPU_FILTER_NEAREST);
  GPU_SetWrapMode(image->getImage(), GPU_WRAP_REPEAT, GPU_WRAP_REPEAT);
  image->size = vec2(4.0);
}
GameBG::~GameBG() { delete image; }
void GameBG::Draw() { image->Draw(); }
