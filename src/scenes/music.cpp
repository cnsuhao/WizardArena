#include "music.hpp"

bool finishedFading;

void musicFinished() { finishedFading = true; }

void Music::Init() {
  Mix_Init(MIX_INIT_OGG);
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
    printf("Mix_OpenAudio: %s\n", Mix_GetError());
    GameObject::globals->gameState = QUIT;
  }
}

Music::Music() {
  MenuMusic  = Mix_LoadMUS("Content/Music/Menu.ogg");
  LobbyMusic = Mix_LoadMUS("Content/Music/DarkFuture.ogg");
  GameMusic  = Mix_LoadMUS("Content/Music/HolyWar.ogg");
  Mix_PlayMusic(MenuMusic, -1);
  currentTrack   = 0;
  finishedFading = false;
  Mix_HookMusicFinished(musicFinished);
}

Music::~Music() {
  Mix_FreeMusic(MenuMusic);
  Mix_FreeMusic(GameMusic);
  Mix_CloseAudio();
  Mix_Quit();
}

void Music::Update() {
  if ((int)GameObject::globals->gameState != currentTrack) {
    Mix_FadeOutMusic(1000);
    currentTrack = (int)GameObject::globals->gameState;
  }
  if (finishedFading) {
    if (currentTrack == 0) {
      Mix_FadeInMusic(MenuMusic, -1, 1000);
    } else if (currentTrack == 1) {
      Mix_FadeInMusic(LobbyMusic, -1, 1000);
    } else if (currentTrack == 2) {
      Mix_FadeInMusic(GameMusic, -1, 1000);
    }
    finishedFading = false;
  }
}
