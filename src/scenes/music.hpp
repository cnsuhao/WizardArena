#ifndef MUSIC_H
#define MUSIC_H
#include "../scene.hpp"

class Music : public Scene {
 public:
  Music();
  virtual ~Music();

  void Update();

  // Remove content from draw and input
  void Input(SDL_Event scene){};
  void Draw(){};

 private:
  Mix_Music* GameMusic;
  Mix_Music* MenuMusic;
};

#endif
