#version 400

uniform float velx;
uniform float vely;

uniform sampler2D tex;

in vec4 color;
in vec4 texcoords;

out vec4 outcolor;

vec4 blur(vec2 blurVec, int nSamples) {
  vec4 result = texture(tex, texcoords.xy);
  for (int i = 1; i < nSamples; ++i) {
    // get offset in range [-0.5, 0.5]:
    vec2 offset = blurVec * (float(i) / float(nSamples - 1) - 0.5);

    // sample & add to result:
    result += texture(tex, texcoords.xy + offset);
  }

  result /= float(nSamples);
  return result;
}

void main(void) {
  if (velx != 0 || vely != 0) {
    outcolor = blur(vec2(0, 0.15), 15);
    // outcolor += blur(vec2(0.05, 0), 10) / 3.0;
    // mix(blur(vec2(velx, vely), 10), blur(vec2(vely, -velx) / 2.0, 10), 0.9);
  } else {
    // outcolor = texture(tex, texcoords.xy +
    // vec2(0.004*sin(10*time+texcoords.y*100)), 0);
    outcolor = texture(tex, texcoords.xy);
  }
  // outcolor *= sin(time)/2.0 + 0.5;
}
