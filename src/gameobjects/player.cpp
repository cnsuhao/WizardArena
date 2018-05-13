#include "player.hpp"

Player::Player() {
  image    = GPU_LoadImage("Content/Textures/Player.png");
  rotation = 0;
}

Player::~Player() { GPU_FreeImage(image); }

void Player::Update() {}
void Player::Draw() {
  GPU_BlitRotate(image, nullptr, globals->backbuffer, position.x, position.y,
                 rotation);
}
