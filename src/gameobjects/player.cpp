#include "player.hpp"

#define MAX_SPEED 1000.0f

Player::Player(vec2 pos) {
  image    = GPU_LoadImage("Content/Textures/Player.png");
  rotation = 0;
  position = pos;
  velocity = vec2(0);
  dead     = false;
}

Player::~Player() { GPU_FreeImage(image); }

void Player::Update() {
  if (velocity != vec2(0, 0)) {
    // normalize and set speed
    // velocity = glm::normalize(velocity);
    // velocity *= MAX_SPEED;

    // Move  player
    position += (glm::normalize(velocity) * MAX_SPEED) *
                (float)GameObject::globals->DeltaTime;
  }

  if (position.x > 1280) { dead = true; }
  if (position.y > 1000) { dead = true; }
  if (position.x < 0) { dead = true; }
  if (position.y < -280) { dead = true; }
  if (dead) { position = vec2(640, 360); }
}
void Player::Draw() {
  if (!dead)
    GPU_BlitRotate(image, nullptr, globals->backbuffer, position.x, position.y,
                   rotation);
}
