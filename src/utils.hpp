#ifndef UTILS_H
#define UTILS_H
#include "includes.hpp"

template <class T>
T clamp(T val, T min, T max) {
  if (val <= min)
    return min;
  else if (val >= max)
    return max;
  return val;
}

/**
  Point-rectangle intersection
 */

bool PointRectIntersect(vec2 point, vec2 size, vec2 center) {
  if (center.x + (size.x / 2) > point.x && center.x - (size.x / 2) < point.x &&
      center.y + (size.y / 2) > point.y && center.y - (size.y / 2) < point.y) {
    return true;
  } else {
    return false;
  }
}

#endif  // UTILS_H
