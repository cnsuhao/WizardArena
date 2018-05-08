#include "utils.hpp"

bool PointRectIntersect(vec2 point, vec2 size, vec2 center) {
  if (center.x + (size.x / 2) > point.x && center.x - (size.x / 2) < point.x &&
      center.y + (size.y / 2) > point.y && center.y - (size.y / 2) < point.y) {
    return true;
  } else {
    return false;
  }
}
