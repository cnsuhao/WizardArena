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

GameScene::~GameScene() {
  delete game;
  exit(0);
}

void GameScene::Update() {
  Scene::Update();
  game->Update();
  if (game->Disconnected) {
    Dead = true;
    Messages.push_back("Connect");
    Messages.push_back("Message");
    Messages.push_back("Disconnected");
  }
}

void GameScene::Draw() {
  Scene::Draw();
  for (ubyte i = 0; i < game->Players.size(); i++) { game->Players[i]; }
}
