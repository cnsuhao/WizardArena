#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP
#include "includes.hpp"
#include "scene.hpp"

class SceneManager {
 public:
  SceneManager(Scene* PrimaryScene);
  virtual ~SceneManager();
  void ChangePrimaryScene(Scene* scene);
  void AddScene(Scene* scene);
  void Draw();
  void Update();

 private:
  vector<Scene*> scenes;
};

#endif /* SCENEMANAGER_HPP */
