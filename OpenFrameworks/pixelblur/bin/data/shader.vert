#version 120

#define PI 3.1415

uniform float mul = 1.0;
uniform float width = 400.0;
uniform float height = 400.0;
uniform vec4 randNum = vec4(0.0);
uniform vec2 squish = vec2(1.0);
uniform float vortexRadius = 200;
uniform int t = 0;

vec4 rand(vec2 A,vec2 B,vec2 C,vec2 D){ 

	vec2 s=vec2(12.9898,78.233); 
	vec4 tmp=vec4(dot(A,s),dot(B,s),dot(C,s),dot(D,s)); 

	return fract(sin(tmp) * 43758.5453)* 2.0 - 1.0; 
}

float t_mod(float sp){
  return mod(t,sp)/sp;
}

float t_sin(float sp, bool bi=false){
  if (bi){
    return sin( radians(t/sp) );
  } else {
    return abs( sin( radians(t/sp) ) );
  }
}

bool between(float value, float lo, float hi){
  if (lo <= value && value <= hi){
    return true;
  } else {
    return false;
  }
}

float lerp(float start, float end, float amt){
  return (1-abs(amt)) * start + abs(amt) * end;
}

float W = 100;

void main(){
	vec4 pos = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;

  vec3 col = vec3(1.0);

  pos *= vec4(mul,mul,1.0,1.0);

  float x = pos.x; float y = pos.y;

  if ( between(y, (height-W/2)*randNum.x, (height-W/2)*randNum.x+W/2)
    || between(y, (height-W/2)*randNum.y, (height-W/2)*randNum.y+W/2)
    || between(x, (width-W)*randNum.x, (width-W)*randNum.x+W)
    || between(x, (width-W)*randNum.y, (width-W)*randNum.y+W)
  ) {} else {

  vec2 c1 = vec2(width, height);
  vec2 c0 = c1 * vec2(-1,1);
  vec2 c2 = c1 * vec2(1,-1);
  vec2 c3 = c1 * vec2(-1,-1);

  vec2 A = vec2(0, height*0.5);
  vec2 B = vec2(width*0.5, 0);
  vec2 C = vec2(0, -height*0.5);
  vec2 D = vec2(-width*0.5, 0);

  if (x < 0 && y > 0){ //top left
    if (x < -y){
      pos.y = lerp(A.y, height,  x/width );
    } else if (x > -y) {
      pos.x = lerp(D.x, -width,  y/height );
    }
  } else if (x > 0 && y > 0){ //top right
    if (x < y){
      pos.y = lerp(A.y, height, x/width );
    } else if (x > y){
      pos.x = lerp(B.x, width, y/height );
    }
  } else if (x > 0 && y < 0){ //bot right
    if (x < -y){
      pos.x = lerp(B.x, width,  y/height );
    } else if (x > -y){
      pos.y = lerp(C.y, -height,  x/width );
    }
  } else { // bot left
    if (x < y){
      pos.x = lerp(D.x, -width, y/height );
    } else if (x > y){
      pos.y = lerp(C.y, -height, x/width );
    }
  }

  }

  float theta = atan(pos.y/pos.x);
  float r = sqrt(pos.x*pos.x + pos.y*pos.y);

  if (r < abs(randNum[2])*width ){
    pos.x *= squish.x;
    pos.y *= squish.y;
  }

  // pos.x *= randNum[3];

	gl_Position = pos;
	gl_FrontColor =  gl_Color * vec4(col,1.0);
}
