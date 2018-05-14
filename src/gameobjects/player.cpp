#include "player.hpp"

#define MAX_SPEED 1000.0f

Player::Player(vec2 pos) {
  image       = GPU_LoadImage("Content/Textures/Player.png");
  rotation    = 0;
  position    = pos;
  velocity    = vec2(0);
  dead        = false;
  poweredUp   = false;
  coolingDown = false;

  SDL_Color clr        = {255, 0, 0, 255};
  deathTimer           = new Panel(clr);
  deathTimer->size     = vec2(0, 20);
  deathTimer->position = position + vec2(0, 50);
}

Player::~Player() {
  GPU_FreeImage(image);
  delete deathTimer;
}

void Player::Update() {
  if (velocity != vec2(0, 0)) {
    // Normalize and set speed to move player.
    position += (glm::normalize(velocity) * MAX_SPEED) *
                (float)GameObject::globals->DeltaTime;
  }

  if (position.x > 1280 || position.y > 1000 || position.x < 0 ||
      position.y < -280) {
    voidTime += globals->DeltaTime;
  } else {
    voidTime -= globals->DeltaTime;
    if (voidTime < 0) voidTime = 0;
  }

  if (voidTime > VOIDDEATHTIME) dead = true;
  if (dead) { position = vec2(640, 360); }

  // Set timer position and size
  deathTimer->size     = vec2((VOIDDEATHTIME - voidTime) * 300, 20);
  deathTimer->position = position + vec2(0, 100);

  // Check for cooldown
  if (coolingDown) {
    if (globals->Time - actionTime > COOLDOWNTIME) coolingDown = false;
  }
}

void Player::Draw() {
  if (!dead)
    GPU_BlitRotate(image, nullptr, globals->backbuffer, position.x, position.y,
                   rotation);

  if (voidTime > 0 && !dead) deathTimer->Draw();
}

void Player::Cooldown() {
  actionTime  = globals->Time;
  coolingDown = true;
}
