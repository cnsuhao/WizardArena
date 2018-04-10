#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP
#include "includes.hpp"

typedef int Scene;

class SceneManager {
 public:
  SceneManager();
  virtual ~SceneManager();
  void ChangePrimaryScene(Scene* Scene);
  void AddScene(Scene* Scene);

 private:
  vector<Scene*> scenes;
};

#endif /* SCENEMANAGER_HPP */
