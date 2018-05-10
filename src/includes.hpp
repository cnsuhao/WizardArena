#ifndef INCLUDES_HPP
#define INCLUDES_HPP

// Macros
#ifdef __APPLE__
// microseconds to seconds
#define CountToSeconds(x) static_cast<double>(x) / 1000000.0
#define CountToMilliseconds(x) static_cast<double>(x) / 1000.0
#elif defined(_WIN32)
// 100 nanoseconds to seconds
#define CountToSeconds(x) static_cast<double>(x) / 10000000.0
#define CountToMilliseconds(x) static_cast<double>(x) / 10000.0
#else
// nanoseconds to seconds
#define CountToSeconds(x) static_cast<double>(x) / 1000000000.0
#define CountToMilliseconds(x) static_cast<double>(x) / 1000000.0
#endif

// STL
#include <stdint.h>  // uint64_t
#include <chrono>
#include <iomanip>  // setprecision
#include <map>
#include <sstream>
#include <string>
#include <vector>

// SDL2, SDL_mixer and SDL_gpu
#include <SDL2/SDL_gpu.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

// GLM
#include <glm/glm.hpp>

// Using statements
using glm::vec2;
using std::string;
using std::vector;

// Type definitions
typedef uint8_t  byte;
typedef uint8_t  ubyte;
typedef uint32_t uint;
typedef uint64_t uint64;

#endif  // INCLUDES_HPP
