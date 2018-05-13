#ifndef MUSIC_H
#define MUSIC_H
#include "../scene.hpp"

class Music : public Scene {
 public:
  Music();
  virtual ~Music();

  void Update();

  // Init SDL_Mixer
  static void Init();

  // Remove content from draw and input
  void Input(SDL_Event scene){};
  void Draw(){};

 private:
  Mix_Music* GameMusic;
  Mix_Music* LobbyMusic;
  Mix_Music* MenuMusic;
  int        currentTrack;
};

#endif
