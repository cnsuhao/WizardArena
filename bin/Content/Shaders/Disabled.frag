#version 400

uniform float time;

uniform sampler2D tex;

in vec4 color;
in vec4 texcoords;

out vec4 outcolor;

float luminance(vec3 incolor) {
  return (incolor.x + incolor.y + incolor.z) / 3.0;
}

void main(void) {
  outcolor = texture(tex, texcoords.xy);
  outcolor.xyz /= 4.0;
  outcolor.xyz = vec3((luminance(outcolor.xyz)));
}
