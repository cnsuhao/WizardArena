#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP
#include "globals.hpp"
#include "scenes/connect.hpp"
#include "scenes/credits.hpp"
#include "scenes/mainmenu.hpp"
#include "scenes/options.hpp"
#include "shader.hpp"

/**
 *  Class to handle and manage multiple scenes. It keeps a stack of scenes,
 *  wherein the primary scene is the scene at the bottom of the stack.
 */
class SceneManager {
 public:
  /** Constructor that only initializes the vector of scene pointers. */
  SceneManager();
  /** Constructor that initializes the vector of scene pointers and pushes a
     primary scene to the vector.
      @param PrimaryScene Scene pointer to push to the stack.
      @see Scene
   */
  explicit SceneManager(Scene* PrimaryScene);
  /** Destructor that deletes all scenes.
      @see Scene
  */
  ~SceneManager();
  /** Changes the primary and bottom scene.
      @param scene The scene pointer which should be at the bottom of the stack.
      @see Scene
   */
  void ChangePrimaryScene(Scene* scene);

  /** Adds a scene on top.
      @param scene A scene pointer to push to the stack.
   */
  void AddScene(Scene* scene);

  /** Calls tick functions of all handled scenes. */
  void Tick();

  /** Calls input functions of all handled scenes.
      @param event The event to pass to each scene.
   */
  void Input(SDL_Event event);

 private:
  /** Calls draw functions of all handled scenes. */
  void Draw();
  /** Calls update functions of all handled scenes. */
  void Update();

  // Variables
  vector<Scene*> scenes;  ///< Stack that holds pointers to all handled scenes.

  Shader*           SSCA;  ///< Screen space chromatic aberration pass shader
  map<string, uint> SSCAUniforms;
};

#endif /* SCENEMANAGER_HPP */
