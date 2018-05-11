#include "textbox.hpp"

Textbox::Textbox(string startText, bool highlighted) {
  SDL_Color cursorColor = {255, 0, 0, 255};

  txt = startText;

  text        = new Text(txt);
  txtpanel    = new Panel();
  cursorpanel = new Panel(cursorColor);

  SetHighlighted(highlighted);
}

Textbox::~Textbox() {
  delete text;
  delete txtpanel;
  delete cursorpanel;
}

void Textbox::SetHighlighted(bool highlighted) {
  this->highlighted = highlighted;
  if (highlighted) {
    SDL_StartTextInput();
  } else {
    SDL_StopTextInput();
  }
}

void Textbox::Input(SDL_Event event) {
  if (!highlighted) return;
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_BACKSPACE) {
      if (txt.size()) {
        txt.pop_back();
        text->SetText(txt);
      }
    }
  }

  if (event.type == SDL_TEXTINPUT) {
    if (txt.size() < 15) txt.append(event.text.text);
    text->SetText(txt);
  }
}

void Textbox::Draw() {
  txtpanel->size     = size;
  txtpanel->position = position;
  txtpanel->position.y -= 4;
  text->position = position;
  txtpanel->Draw();
  text->Draw();
  if (highlighted) {
    cursorpanel->size.x   = 3;
    cursorpanel->size.y   = txtpanel->size.y;
    cursorpanel->position = txtpanel->position;
    cursorpanel->position.x += text->size.x / 2;
    cursorpanel->Draw();
  }
}
