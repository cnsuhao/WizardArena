#include "fireball.hpp"
#include <glm/gtx/vector_angle.hpp>

#define TODEGREES (180.0 / 3.141592653589793238463)
#define LIFETIME 5.0

Fireball::Fireball(int owner, vec2 position, vec2 velocity) {
  this->owner    = owner;
  this->position = position;
  this->velocity = velocity;

  img = GPU_LoadImage("Content/Textures/Fireball.png");
  GPU_SetImageFilter(img, GPU_FILTER_NEAREST);

  birthTime = globals->Time;
  expired   = false;

  shader   = new Shader("Fireball", {"velx", "vely"});
  uniforms = shader->GetUniforms();
}
Fireball::~Fireball() { GPU_FreeImage(img); }

void Fireball::Update() {
  if (globals->Time - birthTime > LIFETIME) { expired = true; }

  // Move
  if (velocity != vec2(0, 0)) {
    position += velocity * (float)GameObject::globals->DeltaTime;
  }
}
void Fireball::Draw() {
  float angle = 0;

  // Compute angle and save it
  if (velocity.x > 0) {
    angle = -glm::angle(vec2(0, 1), glm::normalize(velocity)) * TODEGREES + 180;
  } else {
    angle = glm::angle(vec2(0, 1), glm::normalize(velocity)) * TODEGREES + 180;
  }

  shader->Activate();
  GPU_SetUniformf(uniforms["velx"], velocity.x / 1000);
  GPU_SetUniformf(uniforms["vely"], velocity.y / 1000);
  GPU_BlitTransform(img, nullptr, globals->backbuffer, position.x, position.y,
                    angle, 3.0f, 3.0f);
  shader->Deactivate();
}

bool Fireball::Intersect(vec2 playerPosition) {
  if (glm::distance(position, playerPosition) < 85) {
    expired = true;
    return true;
  }
  return false;
}
