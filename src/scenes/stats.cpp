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
  gameObjects.push_back(new Text("CPU Freq: ", true));
  gameObjects.push_back(new Text("Delta Time: ", true));

  textHeight                   = gameObjects[FPS]->size.y;
  gameObjects[PANEL]->size.x   = 250;
  gameObjects[PANEL]->size.y   = (1 + textHeight) * gameObjects.size();
  gameObjects[PANEL]->position = gameObjects[PANEL]->size * vec2(0.5);

  setPositions();

  // Get amount of cycles
  lastCycles = rdtsc();
}

Stats::~Stats() {}

void Stats::Draw() {
  Scene::Draw();
  frames++;
  sumDeltaTime += GameObject::globals->DeltaTime;
}

void Stats::Update() {
  Scene::Update();
  if ((uint)floor(SDL_GetTicks() / 1000.0) != lastSecond) {
    std::stringstream strstream;
    // Set FPS Text
    ((Text*)gameObjects[FPS])->SetText("FPS: " + std::to_string(frames), true);

    // Set CPU freq text
    double cpufreq = ((double)(rdtsc() - lastCycles)) / 1000000000.0;

    strstream.str("");
    strstream << "CPU freq: " << std::fixed << std::setprecision(2) << cpufreq
              << " GHz";
    ((Text*)gameObjects[CYCLES])->SetText(strstream.str(), true);

    // Set deltatime text
    strstream.str("");
    strstream << "Delta Time: " << std::fixed << std::setprecision(3)
              << (sumDeltaTime * 1000.0) / ((double)frames) << " ms";
    ((Text*)gameObjects[DELTATIME])->SetText(strstream.str(), true);

    // Reset counters
    frames       = 0;
    lastCycles   = rdtsc();
    sumDeltaTime = 0.0;

    // Set text positions
    setPositions();
    lastSecond = (uint)floor(SDL_GetTicks() / 1000.0);
  }
}

void Stats::setPositions() {
  for (uint i = 1; i < gameObjects.size(); i++) {
    gameObjects[i]->position.x = gameObjects[i]->size.x / 2.0 + 5;
    gameObjects[i]->position.y =
        textHeight / 2.0 + 5 + (5 * (i - 1)) + (textHeight * (i - 1));
  }
}
