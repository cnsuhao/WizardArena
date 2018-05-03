#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "includes.hpp"

/** This is a enumeration that describes the game state.*/
enum GameState { MENU = 0, GAME = 1, QUIT = 2 };

/** This is the structure of the game that holds the the global variabels. */
struct Globals {
  /** Describes the current game state. */
  byte gameState = MENU;
  /** The defult width and height of the game window. */
  uint width = 1280, height = 720;
  /** Width and height of the viewport coordinate system */
  const uint vwidth = 1280, vheight = 720;
  /** This is a pointer referring to the window. */
  GPU_Target* window;
  /** Game font */
  TTF_Font* font;
  /** Smaller font */
  TTF_Font* smallFont;
  /** Delta time */
  double DeltaTime = 0.016;
};

#endif  // GLOBALS_HPP
