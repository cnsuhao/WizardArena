#ifndef IMAGE_HPP
#define IMAGE_HPP
#include "../gameobject.hpp"
#include "../includes.hpp"

/*
  Handles images
*/
class Image : public GameObject {
 public:
  // Loads image
  Image(const char* filename) {
    image      = GPU_LoadImage(filename);
    this->size = vec2(1);
  }
  // Load with position
  Image(const char* filename, vec2 Position) {
    image          = GPU_LoadImage(filename);
    this->position = Position;
    this->size     = vec2(1);
  }
  // Load with position
  Image(const char* filename, float x, float y) {
    image          = GPU_LoadImage(filename);
    this->position = vec2(x, y);
    this->size     = vec2(1);
  }
  // Destructor
  ~Image() { GPU_FreeImage(image); }

  // Draw
  void Draw() {
    GPU_BlitScale(image, NULL, globals->backbuffer, position.x, position.y,
                  size.x, size.y);
  }

 private:
  GPU_Image* image;  // Image pointer
};

#endif  // IMAGE_HPP
