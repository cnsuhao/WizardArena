#include "scene.hpp"

Scene::Scene() {
  dead        = false;
  gameObjects = vector<GameObject*>();
  messages    = vector<string>();
}
// Draw gameObject
void Scene::Draw() {
  for (auto gameObject : gameObjects) { gameObject->Draw(); }
}

void Scene::Update() {
  for (auto gameObject : gameObjects) { gameObject->Update(); }
}

// Free scene memory
Scene::~Scene() {
  for (auto gameObject : gameObjects) { delete gameObject; }
}
