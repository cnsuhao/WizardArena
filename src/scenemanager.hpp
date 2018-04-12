#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP
#include "includes.hpp"
#include "scene.hpp"

/*
   Class to handle and manage multiple scenes
*/
class SceneManager {
 public:
  // Constructor
  SceneManager(Scene* PrimaryScene);
  // Destructor
  virtual ~SceneManager();
  // Change the primary and bottom scene
  void ChangePrimaryScene(Scene* scene);
  // Add a scene on top
  void AddScene(Scene* scene);
  // Draw appropriate scenes
  void Draw();
  // Update the appropriate scenes
  void Update();

 private:
  // Store scenes
  vector<Scene*> scenes;
};

#endif /* SCENEMANAGER_HPP */
