#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "includes.hpp"

struct OptionVariables {
  double MusicVolume = 1.0;
  double SoundVolume = 1.0;
};

/** This is a enumeration that describes the game state.*/
enum GameState { MENU = 0, LOBBY = 1, GAME = 2, QUIT = 3 };

/** This is the structure of the game that holds the the global variables. */
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
  /** Draw time */
  double drawTime = 0.02;
  /** Update time */
  double updateTime = 0.02;
  /** Application runtime */
  double Time = 0.0;
  /** Options variables */
  OptionVariables options;
};

#endif  // GLOBALS_HPP
