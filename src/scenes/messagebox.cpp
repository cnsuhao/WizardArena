#include "messagebox.hpp"

MessageBox::MessageBox(string message, uint time) {
  endTime = SDL_GetTicks() + time;
  gameObjects.push_back(new Panel());
  gameObjects.push_back(new Text(message));

  // Set panel size
  gameObjects[0]->size = gameObjects[1]->size + vec2(40, 13);

  // Set their position
  gameObjects[0]->position.y = 230;
  gameObjects[1]->position.y = 230;
  gameObjects[1]->position.x = gameObjects[0]->position.x;
}

MessageBox::~MessageBox() {}

void MessageBox::Update() {
  if (SDL_GetTicks() >= endTime) Dead = true;
}
