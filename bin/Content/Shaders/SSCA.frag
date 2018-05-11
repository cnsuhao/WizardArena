#version 400

// uniform float time;
// uniform float camvec[2];

uniform float SSCAAmount;

uniform sampler2D tex;

in vec4 color;
in vec4 texcoords;

out vec4 outcolor;

void main(void) {
  vec2 center = vec2(0.5, 0.5);
  vec2 c      = vec2(pow((texcoords.xy - center).x * 1.6, 2),
                pow((texcoords.xy - center).y * 2, 2));

  outcolor = vec4(
      texture(tex, texcoords.xy + (SSCAAmount * 4.0) * (c / 400.0)).x,
      texture(tex, texcoords.xy).y,
      texture(tex, texcoords.xy - (SSCAAmount * 4.0) * (c / 400.0)).z, 1.0);
}
