#include "gamescene.hpp"
#include <glm/gtx/vector_angle.hpp>

// using glm::gtx::vector_angle::angle;

#define TODEGREES (180.0 / 3.141592653589793238463)
#define W SDL_SCANCODE_W
#define A SDL_SCANCODE_A
#define S SDL_SCANCODE_S
#define D SDL_SCANCODE_D

GameScene::GameScene(Game* game) {
  this->game = game;

  platform = new Image("Content/Textures/Platform.png",
                       GameObject::globals->vwidth / 2.0,
                       GameObject::globals->vheight / 2.0);

  platform->size = vec2(5);

  gameObjects.push_back(new GameBG());
  gameObjects.push_back(platform);

  cam = GPU_GetDefaultCamera();

  player = game->Players[game->GetPlayerIndex()];
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
  cam.x = player->position.x - GameObject::globals->vwidth / 2;
  cam.y = player->position.y - GameObject::globals->vheight / 2;

  // Calculate velocity
  const Uint8* kb  = SDL_GetKeyboardState(NULL);
  player->velocity = vec2(0, 0);
  if (kb[W]) player->velocity.y -= 1;
  if (kb[A]) player->velocity.x -= 1;
  if (kb[S]) player->velocity.y += 1;
  if (kb[D]) player->velocity.x += 1;


  for (ubyte i = 0; i < game->Players.size(); i++) {
    game->Players[i]->Update();
  }
}

void GameScene::Draw() {
  GPU_SetCamera(GameObject::globals->backbuffer, &cam);
  Scene::Draw();
  for (ubyte i = 0; i < game->Players.size(); i++) { game->Players[i]->Draw(); }
  GPU_SetCamera(GameObject::globals->backbuffer, NULL);
}

void GameScene::Input(SDL_Event event) {
  // Call super function
  Scene::Input(event);
  // Set player rotation based on cursor position
  if (event.type == SDL_MOUSEMOTION) {
    vec2 center         = vec2(GameObject::globals->width / 2.0,
                       GameObject::globals->height / 2.0);
    vec2 cursor         = vec2(event.motion.x, event.motion.y);
    vec2 centertocursor = cursor - center;
    // Compute angle and save it
    if (centertocursor.x > 0) {
      player->rotation =
          -glm::angle(vec2(0, 1), glm::normalize(centertocursor)) * TODEGREES +
          180;
    } else {
      player->rotation =
          glm::angle(vec2(0, 1), glm::normalize(centertocursor)) * TODEGREES +
          180;
    }
  }

  // Scroll to zoom
  if (event.type == SDL_MOUSEWHEEL) {
    cam.zoom += event.wheel.y / 15.0;
    cam.zoom = clamp(cam.zoom, 0.3f, 4.0f);
  }
}
