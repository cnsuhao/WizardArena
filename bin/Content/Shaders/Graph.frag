#version 400

uniform float DeltaTime;
uniform float UpdateTime;
uniform float DrawTime;
uniform float GraphMax;

uniform sampler2D tex;

in vec4 color;
in vec4 texcoords;

out vec4 outcolor;

float dist(float val1, float val2) { return abs(val1 - val2); }

bool inRange(float distance, float radius) {
  if (distance <= radius) return true;
  return false;
}

void main(void) {
  if (texcoords.x < 1.0 - ((1.0 / 270.0) * 2)) {
    outcolor = texture(tex, texcoords.xy + vec2((1.0 / 270.0), 0));
    //    if (outcolor.xyz == vec3(0, 0, 0)) { outcolor = vec4(0, 0, 0, 0); }
  } else {
    outcolor = vec4(0, 0, 0, 1);

    if (inRange(dist((1.0 - texcoords.y) * GraphMax, DeltaTime * 1000.0), 0.5))
      outcolor += vec4(1, 0, 0, 1);
    if (inRange(dist((1.0 - texcoords.y) * GraphMax, UpdateTime), 0.5))
      outcolor += vec4(0, 1, 0, 1);
    if (inRange(dist((1.0 - texcoords.y) * GraphMax, DrawTime), 0.5))
      outcolor += vec4(0, 0, 1, 1);
    if (inRange(dist((1.0 - texcoords.y) * GraphMax, GraphMax), 0.5))
      outcolor += vec4(1, 1, 1, 1);
    /*    if (inRange(dist((1.0 - texcoords.y) * GraphMax, 0), 0.5))
      outcolor = vec4(1, 1, 1, 1);
    */
    // Draw 60fps line
    if (outcolor.xyz == vec3(0, 0, 0)) {
      if (inRange(dist((1.0 - texcoords.y) * GraphMax, 16.66), 0.25)) {
        outcolor += vec4(1, 1, 1, 1);
      }
    }

    /*
    if ((1.0 - texcoords.y) * GraphMax < DeltaTime * 1000.0)
      outcolor = vec4(1, 0, 0, 1);*/
  }
}
