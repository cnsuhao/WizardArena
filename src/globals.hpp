#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "includes.hpp"

// Game states enum
enum GameState { MENU = 0, GAME = 1, QUIT = 2 };

// Structure of globals
struct Globals {
  byte gameState = MENU;  // stores data
  // Screen dimensions
  uint width = 1280, height = 720;
};

#endif  // GLOBALS_HPP
