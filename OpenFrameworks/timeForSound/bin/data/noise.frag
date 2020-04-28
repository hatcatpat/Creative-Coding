#version 120

uniform int width = 400;
uniform int height = 400;
uniform vec4 random = vec4(0.0);
uniform int blue_mode = 0;

void main(){

  vec2 pos = vec2(0.0);

  if (width < height){
    pos = gl_FragCoord.xy/width;
  } else {
    pos = gl_FragCoord.xy/width;
  }
	float xVal = gl_FragCoord.x;
	float yVal = gl_FragCoord.y;
	
  vec3 col = gl_Color.xyz;

  if (blue_mode == 1){
    col *= vec3(0.0,0.0,1.0);
  }

  gl_FragColor = vec4(col,1.0);
}
