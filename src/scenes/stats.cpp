#include "stats.hpp"

// Get CPU cycles
//  Windows
#ifdef _WIN32
#include <intrin.h>
uint64_t rdtsc() { return __rdtsc(); }
//  Linux/GCC
#else
uint64 rdtsc() {
  unsigned int lo, hi;
  __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
  return ((uint64)hi << 32) | lo;
}
#endif

Stats::Stats() {
  gameObjects.push_back(new Panel());
  gameObjects.push_back(new Text("FPS: ", true));
  gameObjects.push_back(new Text("Cycles: ", true));

  gameObjects[PANEL]->size.x      = 230;
  gameObjects[PANEL]->size.y      = 60;
  gameObjects[PANEL]->position.x  = gameObjects[PANEL]->size.x / 2.0;
  gameObjects[PANEL]->position.y  = gameObjects[PANEL]->size.y / 2.0;
  gameObjects[FPS]->position.x    = gameObjects[FPS]->size.x / 2.0 + 5;
  gameObjects[FPS]->position.y    = gameObjects[FPS]->size.y / 2.0 + 5;
  gameObjects[CYCLES]->position.x = gameObjects[CYCLES]->size.x / 2.0 + 5;
  gameObjects[CYCLES]->position.y =
      gameObjects[CYCLES]->size.y / 2.0 + 10 + gameObjects[FPS]->size.y;

  // Get amount of cycles
  lastCycles = rdtsc();
}

Stats::~Stats() {}

void Stats::Draw() {
  Scene::Draw();
  frames++;
}

void Stats::Update() {
  Scene::Update();
  if ((uint)floor(SDL_GetTicks() / 1000.0) != lastSecond) {
    double            cpufreq = ((double)(rdtsc() - lastCycles)) / 1000000000.0;
    std::stringstream strstream;
    strstream.str("");
    strstream << "CPU freq: " << std::fixed << std::setprecision(2) << cpufreq
              << " GHz";
    ((Text*)gameObjects[FPS])->SetText("FPS: " + std::to_string(frames), true);
    ((Text*)gameObjects[CYCLES])->SetText(strstream.str(), true);
    frames     = 0;
    lastCycles = rdtsc();

    // Set text positions
    gameObjects[FPS]->position.x    = gameObjects[FPS]->size.x / 2.0 + 5;
    gameObjects[FPS]->position.y    = gameObjects[FPS]->size.y / 2.0 + 5;
    gameObjects[CYCLES]->position.x = gameObjects[CYCLES]->size.x / 2.0 + 5;
    gameObjects[CYCLES]->position.y =
        gameObjects[CYCLES]->size.y / 2.0 + 10 + gameObjects[FPS]->size.y;
    lastSecond = (uint)floor(SDL_GetTicks() / 1000.0);
  }
}
