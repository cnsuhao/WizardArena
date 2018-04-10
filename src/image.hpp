#ifndef IMAGE_HPP
#define IMAGE_HPP
#include "includes.hpp"

/*
  Handles images
*/
class Image {
 public:
  // Loads image
  Image(const char* filename) {
    image    = GPU_LoadImage(filename);
    Position = vec2(0, 0);
  }
  // Load with position
  Image(const char* filename, vec2 Position) {
    image          = GPU_LoadImage(filename);
    this->Position = Position;
  }
  // Load with position
  Image(const char* filename, float x, float y) {
    image          = GPU_LoadImage(filename);
    this->Position = vec2(x, y);
  }
  // Destructor
  ~Image() { GPU_FreeImage(image); }

  // Draw
  void Draw(GPU_Target* target) {
    GPU_Blit(image, NULL, target, Position.x, Position.y);
  }

  vec2 Position;  // Image position

 private:
  GPU_Image* image;  // Image pointer
};

#endif  // IMAGE_HPP
