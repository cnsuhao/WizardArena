#include "gamescene.hpp"

GameScene::GameScene(Game* game) {
  this->game = game;

  platform = new Image("Content/Textures/Platform.png",
                       GameObject::globals->vwidth / 2.0,
                       GameObject::globals->vheight / 2.0);

  platform->size = vec2(3);

  gameObjects.push_back(new GameBG());
  gameObjects.push_back(platform);
}

GameScene::~GameScene() { delete game; }

void GameScene::Update() {
  game->Update();
  if (game->Disconnected) {
    Dead = true;
    Messages.push_back("Connect");
    Messages.push_back("Message");
    Messages.push_back("Disconnected");
  }
}
