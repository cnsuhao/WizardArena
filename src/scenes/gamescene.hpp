#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "../game.hpp"
#include "../gameobjects/gamebg.hpp"
#include "../gameobjects/image.hpp"
#include "../scene.hpp"
#include "../utils.hpp"

class GameScene : public Scene {
 public:
  GameScene(Game* game);
  ~GameScene();
  void Update();
  void Draw();
  void Input(SDL_Event event);

  vector<GameObject*> ActiveObjects;
  vector<string>      ActionStack;

 private:
  Game*   game;
  Image*  platform;
  Player* player;

  double lastActionTime;  // Time of last action for cooldown purposes

  GPU_Camera cam;
};

#endif  // GAMESCENE_H
