#include "scene.hpp"

Scene::Scene() {
  Dead        = false;
  Messages    = vector<string>();
  gameObjects = vector<GameObject*>();
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
