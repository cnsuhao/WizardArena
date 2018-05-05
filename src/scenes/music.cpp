#include "music.hpp"

Music::Music() {
  Mix_Init(MIX_INIT_MP3);
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
    printf("Mix_OpenAudio: %s\n", Mix_GetError());
    GameObject::globals->gameState = QUIT;
  }
}

Music::~Music() {
  Mix_FreeMusic(MenuMusic);
  Mix_FreeMusic(GameMusic);
  Mix_CloseAudio();
  Mix_Quit();
}

void Music::Update() {}
