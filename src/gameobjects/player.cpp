#include "player.hpp"

Player::Player(vec2 pos) {
  image    = GPU_LoadImage("Content/Textures/Player.png");
  rotation = 0;
  position = pos;
  speed    = 0;
}

Player::~Player() { GPU_FreeImage(image); }

void Player::Update() {}
void Player::Draw() {
  GPU_BlitRotate(image, nullptr, globals->backbuffer, position.x, position.y,
                 rotation);
}
