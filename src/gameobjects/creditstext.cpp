#include "creditstext.hpp"
#include <fstream>

CreditsText::CreditsText() {
  std::ifstream creditsFile("Content/Credits.txt");
  string        line;
  uint          counter = 0;
  if (creditsFile.is_open()) {
    while (std::getline(creditsFile, line)) {
      lines.push_back(new Text(line));
      lines[counter]->position.x = globals->vwidth / 2;
      lines[counter]->position.y = 100 + counter * 100;
      counter++;
    }
  }
  creditsFile.close();
}

CreditsText::~CreditsText() {
  for (uint i = 0; i < lines.size(); i++) { delete lines[i]; }
}

void CreditsText::Draw() {
  for (uint i = 0; i < lines.size(); i++) {
    lines[i]->Draw();
    lines[i]->position.y -= 10 * globals->DeltaTime;
  }
}
void CreditsText::Update() {}
