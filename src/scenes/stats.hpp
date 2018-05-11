#ifndef STATS_H
#define STATS_H
#include "../gameobjects/graph.hpp"
#include "../gameobjects/panel.hpp"
#include "../gameobjects/text.hpp"
#include "../includes.hpp"
#include "../scene.hpp"

/** This is the stats class*/
class Stats : public Scene {
 public:
  /** This is the stats constructor*/
  Stats();
  /** This is the stats destructor*/
  virtual ~Stats();
  /** This is the draw function for stats*/
  void Draw();
  /** This is the update function for stats*/
  void Update();

 private:
  /** The last measured cycles*/
  uint64 lastCycles;
  /** The amount of seconds floored*/
  uint lastSecond;
  /** The amount of frames counted*/
  uint frames;
  /** Defines the size of the stats text*/
  double textHeight;
  /** Sets the position of the stats table*/
  void setPositions();

  enum statsObjects { PANEL = 0, FPS = 1, CYCLES = 2, GRAPH = 3 };
};

#endif  // STATS_H
