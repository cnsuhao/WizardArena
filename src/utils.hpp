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
  Point-rectangle intersection, that checks if a point intersects with a
  rectangle.
  @param point is a point placed on the screen.
  @param size describes the size of the rectangle that is made.
  @param center describes the center coordinates of the rectangle.
 */
bool PointRectIntersect(vec2 point, vec2 size, vec2 center);

#endif  // UTILS_H
