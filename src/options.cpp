#include "options.hpp"
#include <fstream>

void ReadOptions(Globals* globals) {
  std::ifstream optionsFile("Content/options.txt");
  string        line;
  if (optionsFile.is_open()) {
    while (!optionsFile.eof()) {
      std::getline(optionsFile, line);
      if (line.substr(0, 3) == "Mus")
        globals->options.MusicVolume =
            std::stod(line.substr(6, line.size() - 6));  // Remove Music=
      if (line.substr(0, 3) == "Sou")
        globals->options.SoundVolume =
            std::stod(line.substr(6, line.size() - 6));  // Remove Sound=
      if (line.substr(0, 3) == "SSC")
        globals->options.SSCAAmount =
            std::stod(line.substr(5, line.size() - 5));  // Remove SSCA=
    }
  }
  optionsFile.close();
}

void SaveOptions(Globals* globals) {
  std::ofstream optionsFile("Content/options.txt");
  string        str = "Music=";
  str += std::to_string(globals->options.MusicVolume) + "\n";
  str += "Sound=" + std::to_string(globals->options.SoundVolume) + "\n";
  str += "SSCA=" + std::to_string(globals->options.SSCAAmount) + "\n";
  optionsFile << str;
  optionsFile.close();
}
