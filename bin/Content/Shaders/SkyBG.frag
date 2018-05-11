#version 400

uniform float time;

uniform sampler2D tex;

in vec4 color;
in vec4 texcoords;

out vec4 outcolor;

/*
vec4 blur(vec2 blurVec, int nSamples) {
  vec4 result = texture(tex, texcoords.xy);
  for (int i = 1; i < nSamples; ++i) {
    // get offset in range [-0.5, 0.5]:
    vec2 offset = blurVec * (float(i) / float(nSamples - 1) - 0.5);

    // sample & add to result:
    result += texture(tex, texcoords.xy + offset + vec2(0.03 * time, 0));
  }

  result /= float(nSamples);
  return result;
}
*/

void main(void) {
  // outcolor = blur(vec2(0.03 * sin(time), 0), 5);
  outcolor = texture(tex, texcoords.xy + vec2(0.02 * time, 0));
}
