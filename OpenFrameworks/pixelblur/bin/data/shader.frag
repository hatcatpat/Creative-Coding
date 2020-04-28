#version 120


uniform float width = 400.0;
uniform float height = 400.0;
uniform vec4 randNum = vec4(0.0);
uniform int t = 0;

void main()
{
  vec2 pos = gl_FragCoord.xy;
  pos /= vec2(width,height);
  pos -= vec2(0.5,0.5);

	vec4 col = gl_Color;
  float theta = atan(pos.y/pos.x);
  float r = sqrt(pos.x*pos.x + pos.y*pos.y);

	gl_FragColor = col;
}
