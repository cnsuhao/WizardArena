#include "scene.hpp"

Scene::Scene() {
  dead        = false;
  gameObjects = vector<GameObject*>();
  messages    = vector<string>();
}
// Free scene memory
Scene::~Scene() {
  for (auto gameObject : gameObjects) { delete gameObject; }
}

// Draw game objects
void Scene::Draw() {
  for (auto gameObject : gameObjects) { gameObject->Draw(); }
}

// Update game objects
void Scene::Update() {
  for (auto gameObject : gameObjects) { gameObject->Update(); }
}

void Scene::Input(SDL_Event event) {
  for (auto gameObject : gameObjects) { gameObject->Input(event); }
}
