#include "scenemanager.hpp"

SceneManager::SceneManager(Scene* PrimaryScene) {
  scenes = vector<Scene*>();
  scenes.push_back(PrimaryScene);
}

SceneManager::~SceneManager() {
  for (auto scene : scenes) { delete scene; }
  scenes.clear();
}

void SceneManager::ChangePrimaryScene(Scene* scene) {
  if (scenes.size() > 0) {
    delete scenes[0];
    scenes[0] = scene;
  } else {
    scenes.push_back(scene);
  }
}

void SceneManager::AddScene(Scene* scene) { scenes.push_back(scene); }

void SceneManager::Draw() {
  // TODO: Uncomment once implemented
  // for (auto scene : scenes) { scene.Draw(); }
}

void SceneManager::Update() {
  // TODO: Uncomment once implemented
  // for (auto scene : scenes) { scene.Update(); }
}
