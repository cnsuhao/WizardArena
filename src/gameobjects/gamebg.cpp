#include "gamebg.hpp"

GameBG::GameBG() {
  image = new Image("Content/Textures/GameBG.png", globals->vwidth / 2,
                    globals->vheight / 2);
}
GameBG::~GameBG() { delete image; }
void GameBG::Draw() { image->Draw(); }
