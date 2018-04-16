#include "scenemanager.hpp"

SceneManager::SceneManager() {
  // Initialize vector
  scenes = vector<Scene*>();
}

SceneManager::SceneManager(Scene* PrimaryScene) {
  // Initialize vector and add the primary scene
  scenes = vector<Scene*>();
  scenes.push_back(PrimaryScene);
}

SceneManager::~SceneManager() {
  // Delete all scenes
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

void SceneManager::Tick() {
  Update();
  Draw();
}

void SceneManager::Input(SDL_Event event) {
  for (auto scene : scenes) { scene->Input(event); }
}

void SceneManager::Draw() {
  for (auto scene : scenes) { scene->Draw(); }
}

void SceneManager::Update() {
  for (auto scene : scenes) { scene->Update(); }
}

void SceneManager::Input(SDL_Event* event) {
  for (auto scene : scenes) { scene->Input(event); }
}
