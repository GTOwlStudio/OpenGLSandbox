#version 330 core

in vec3 color;

out vec4 out_Color;

void main(){
	out_Color = vec4(color, 1.0);
	//out_Color = vec4(1.0, 0.0, 1.0, 1.0);
}