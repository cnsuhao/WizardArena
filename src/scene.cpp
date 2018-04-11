#include "scene.hpp"

Scene::Scene() {
  dead        = false;
  gameObjects = vector<Image*>();
  messages    = vector<string>();
}

Scene::~Scene() {
  for (auto gameObject : gameObjects) { delete gameObject; }
}
