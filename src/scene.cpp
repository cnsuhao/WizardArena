#include "scene.hpp"

Scene::Scene() {
  dead        = false;
  gameObjects = vector<Image*>();
  messages    = vector<string>();
}
// Draw gameObject
void Scene::Draw() {
  for (auto gameObject : gameObjects) { gameObject->Draw(target); }
}

void Scene::Update() {
  // TODO: Update gameobjects
}

// Free scene memory
Scene::~Scene() {
  for (auto gameObject : gameObjects) { delete gameObject; }
}
