#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "../game.hpp"
#include "../gameobjects/gamebg.hpp"
#include "../gameobjects/image.hpp"
#include "../scene.hpp"

class GameScene : public Scene {
 public:
  GameScene(Game* game);
  ~GameScene();
  void Update();
  void Draw();

 private:
  Game*  game;
  Image* platform;
};

#endif  // GAMESCENE_H
