#include "scene.hpp"

Scene::Scene() {
  dead        = false;
  gameObjects = vector<GameObject*>();
  messages    = vector<string>();
}

Scene::~Scene() {
  for (auto gameObject : gameObjects) { delete gameObject; }
}

void Scene::Draw() {
  for (auto gameObject : gameObjects) { gameObject->Draw(); }
}

void Scene::Update() {
  for (auto gameObject : gameObjects) { gameObject->Update(); }
}

void Scene::Input(SDL_Event* event) {
  for (auto gameObject : gameObjects) { gameObject->Input(); }
}
