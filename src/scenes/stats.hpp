#ifndef STATS_H
#define STATS_H
#include "../gameobjects/panel.hpp"
#include "../gameobjects/text.hpp"
#include "../includes.hpp"
#include "../scene.hpp"

class Stats : public Scene {
 public:
  Stats();
  virtual ~Stats();
  void Draw();
  void Update();

 private:
  uint64 lastCycles;
  uint   lastSecond;
  uint   frames;
  double sumDeltaTime;
  double textHeight;

  void setPositions();

  enum statsObjects { PANEL = 0, FPS = 1, CYCLES = 2, DELTATIME = 3 };
};

#endif  // STATS_H
