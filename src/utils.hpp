#ifndef UTILS_H
#define UTILS_H

template <class T>
T clamp(T val, T min, T max) {
  if (val <= min)
    return min;
  else if (val >= max)
    return max;
  return val;
}

#endif  // UTILS_H
