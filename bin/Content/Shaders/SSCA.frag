#version 400

//uniform float time;
//uniform float camvec[2];

uniform float SSCAAmount;

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

void main(void)
{
  vec2 center = -vec2(0.5, 0.5);
  //vec2 c = vec2(pow((texcoords.xy + center).x*2, 2), pow((texcoords.xy + center).y*2, 2));
  vec2 c = vec2(texcoords.xy + center);
  outcolor = vec4(texture(tex, texcoords.xy+SSCAAmount*(c/400.0)).x,
                  texture(tex, texcoords.xy).y,
                  texture(tex, texcoords.xy-SSCAAmount*(c/400.0)).z, 1.0);
  // outcolor = texture(tex, texcoords.xy);
}


