#include "text.hpp"

Text::Text(string text) {
  SDL_Color    col = {255, 255, 255, 255};
  SDL_Surface* textsurf =
      TTF_RenderText_Blended(globals->font, text.c_str(), col);
  textimg = GPU_CopyImageFromSurface(textsurf);
  SDL_FreeSurface(textsurf);
}
Text::Text(string text, SDL_Color color) {
  SDL_Surface* textsurf =
      TTF_RenderText_Blended(globals->font, text.c_str(), color);
  textimg = GPU_CopyImageFromSurface(textsurf);
  SDL_FreeSurface(textsurf);
}

Text::~Text() { GPU_FreeImage(textimg); }
void Text::Draw() {
  GPU_Blit(textimg, nullptr, globals->window, position.x, position.y);
}

void Text::SetText(string text) {
  GPU_FreeImage(textimg);
  SDL_Color    col = {255, 255, 255, 255};
  SDL_Surface* textsurf =
      TTF_RenderText_Blended(globals->font, text.c_str(), col);
  textimg = GPU_CopyImageFromSurface(textsurf);
  SDL_FreeSurface(textsurf);
}

void Text::SetText(string text, SDL_Color color) {
  GPU_FreeImage(textimg);
  SDL_Surface* textsurf =
      TTF_RenderText_Blended(globals->font, text.c_str(), color);
  textimg = GPU_CopyImageFromSurface(textsurf);
  SDL_FreeSurface(textsurf);
}
