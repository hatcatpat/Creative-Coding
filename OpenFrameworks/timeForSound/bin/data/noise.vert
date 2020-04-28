#version 120

uniform float timeValX = 1.0;
uniform float timeValY = 1.0;
uniform int width = 400;
uniform int height = 400;
uniform float T = 0;
uniform vec4 random = vec4(1.0);

//generate a random value from four points
vec4 rand(vec2 A,vec2 B,vec2 C,vec2 D){ 

	vec2 s=vec2(12.9898,78.233); 
	vec4 tmp=vec4(dot(A,s),dot(B,s),dot(C,s),dot(D,s)); 

	return fract(sin(tmp) * 43758.5453)* 2.0 - 1.0; 
} 

//this is similar to a perlin noise function
float noise(vec2 coord,float d){ 

	vec2 C[4]; 

	float d1 = 1.0/d;

	C[0]=floor(coord*d)*d1; 

	C[1]=C[0]+vec2(d1,0.0); 

	C[2]=C[0]+vec2(d1,d1); 

	C[3]=C[0]+vec2(0.0,d1);


	vec2 p=fract(coord*d); 

	vec2 q=1.0-p; 

	vec4 w=vec4(q.x*q.y,p.x*q.y,p.x*p.y,q.x*p.y); 

	return dot(vec4(rand(C[0],C[1],C[2],C[3])),w); 
} 

void main(){

	gl_TexCoord[0] = gl_MultiTexCoord0;
	
	//get our current vertex position so we can modify it
	vec4 pos = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
	vec4 col = gl_Color;

  float x = pos.x/width + 0.5;
  float y = pos.y/height + 0.5;

  vec2 v = vec2(T,T*3);

  if (random[0] < x && x < random[0]+abs(random[1])*0.5 ){
    pos.x *= T*y;
  }

  if (random[2] < x && x < random[2]+abs(random[3])*0.5 ){
    pos.x *= T/y;
  }

  if (random[0] < 0.2){
    float p = pos.x;
    float q = pos.y;
    pos.x = q;
    pos.y = p;
  }

  pos = floor(pos/random[1]*8);

	gl_Position = pos;
	gl_FrontColor =  col;	
}
