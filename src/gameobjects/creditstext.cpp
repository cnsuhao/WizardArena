#include "creditstext.hpp"
#include <fstream>

CreditsText::CreditsText() {
  std::ifstream creditsFile("Content/Credits.txt");
  string        line;
  uint          counter = 0;
  if (creditsFile.is_open()) {
    while (std::getline(creditsFile, line)) {
      if (line[0] == '-') {
        line = line.substr(1, line.size() - 1);
        lines.push_back(new Text(line, {255, 255, 100, 255}));
      } else {
        lines.push_back(new Text(line));
      }
      lines[counter]->position.x = globals->vwidth / 2;
      lines[counter]->position.y = 500 + counter * 80;
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
    lines[i]->position.y -= 40 * globals->DeltaTime;
    // Clean up when out of screen space
    if (lines[i]->position.y <= -200) {
      delete lines[i];
      lines.erase(lines.begin() + i);
    }
  }
}

void CreditsText::Update() {}
