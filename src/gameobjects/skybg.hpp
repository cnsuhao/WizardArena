#ifndef SKYBG_H
#define SKYBG_H
#include "../gameobject.hpp"

class SkyBG : public GameObject {
 public:
  SkyBG();
  virtual ~SkyBG();
  // Draw GameObject
  void Draw() override;
  // Update GameObject
  void Update() override;

 private:
  GPU_Image* sky;
  GPU_Rect   rects[2];
};

#endif /* SKYBG_H */
