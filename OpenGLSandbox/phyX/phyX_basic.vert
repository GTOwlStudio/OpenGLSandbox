#version 330 core

in vec2 in_Vertex;
in vec3 in_Color;
uniform sampler2D texture0;

out vec3 color;

void main(){
	vec2 tc(0,0),
	vec2 pos;
	pos.x = texture(texture0,tc).r;
	pos.y = texture(texture0,tc).g;
	//gl_Position = vec4(pos, 1.0, 1.0);
	gl_Position = vec4(0.0,0.0, 1.0, 1.0);
	
	color = in_Color;

}