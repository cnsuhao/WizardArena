#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "includes.hpp"

/** This is a enumeration that describes the game state.*/
enum GameState { MENU = 0, GAME = 1, QUIT = 2 };

/** This is the structure of the game that holds the the global variabels. */
struct Globals {
  /** Describes the current game state. */
  byte gameState = MENU;
  /** The defult height and width of the game moniter. */
  uint width = 1280, height = 720;
  /** This is a pointer referring to the window. */
  GPU_Target* window;
  // Font
  TTF_Font* font;
};

#endif  // GLOBALS_HPP
