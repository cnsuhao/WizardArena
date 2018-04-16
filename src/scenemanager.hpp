#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP
#include "globals.hpp"
#include "scene.hpp"

/*
   Class to handle and manage multiple scenes
*/
class SceneManager {
 public:
  // Constructors
  SceneManager();
  explicit SceneManager(Scene* PrimaryScene);
  // Destructor
  ~SceneManager();
  // Change the primary and bottom scene
  void ChangePrimaryScene(Scene* scene);
  // Add a scene on top
  void AddScene(Scene* scene);
  // Call tick functions
  void Tick();
  // Call appropriate input functions
  void Input(SDL_Event event);

 private:
  // Draw appropriate scenes
  void Draw();
  // Update the appropriate scenes
  void Update();
  // Store scenes
  vector<Scene*> scenes;
};

#endif /* SCENEMANAGER_HPP */
