#include "scenemanager.hpp"

SceneManager::SceneManager() {
  // Initialize vector
  scenes = vector<Scene*>();
}

SceneManager::SceneManager(Scene* PrimaryScene) {
  // Initialize vector and add the primary scene
  scenes = vector<Scene*>();
  scenes.push_back(PrimaryScene);
  SSCA         = new Shader("SSCA", {"SSCAAmount"});
  SSCAUniforms = SSCA->GetUniforms();
}

SceneManager::~SceneManager() {
  // Delete all scenes
  for (auto scene : scenes) { delete scene; }
  scenes.clear();

  delete SSCA;
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
  // Update and measure time to update
  auto updatestart = TIME();
  Update();
  GameObject::globals->updateTime = CTOMS((TIME() - updatestart).count());

  // Draw and measure time to draw
  auto drawstart = std::chrono::system_clock::now();
  Draw();
  GameObject::globals->drawTime = CTOMS((TIME() - drawstart).count());

  // Draw backbuffer to screen
  SSCA->Activate();
  GPU_SetUniformf(SSCAUniforms["SSCAAmount"],
                  0.2 * GameObject::globals->options.SSCAAmount);
  GPU_Blit(GameObject::globals->backbufferImage, nullptr,
           GameObject::globals->window, GameObject::globals->width / 2,
           GameObject::globals->height / 2);
  SSCA->Deactivate();
}

void SceneManager::Input(SDL_Event event) {
  for (auto scene : scenes) { scene->Input(event); }
}

void SceneManager::Draw() {
  for (auto scene : scenes) { scene->Draw(); }
}

void SceneManager::Update() {
  for (uint i = 0; i < scenes.size(); i++) {
    scenes[i]->Update();
    vector<string> messages = scenes[i]->Messages;
    if (scenes[i]->Dead) {
      delete scenes[i];
      scenes.erase(scenes.begin() + i);
      i--;
      if (messages.size() > 0) {
        for (uint j = 0; j < messages.size(); j++) {
          if (messages[j] == "Credits") {
            i++;
            scenes.insert(scenes.begin() + i, new Credits());
          } else if (messages[j] == "Main Menu") {
            i++;
            scenes.insert(scenes.begin() + i, new MainMenu());
          } else if (messages[j] == "Options") {
            i++;
            scenes.insert(scenes.begin() + i, new Options());
          } else if (messages[j] == "Connect") {
            i++;
            scenes.insert(scenes.begin() + i, new Connect());
          }
        }
      }
    }
  }
}
