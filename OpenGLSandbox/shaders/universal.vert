#version 330 core

in vec3 in_Vertex;
in vec3 in_Color;

uniform mat4 projection;

out vec4 color;

void main(){

	gl_Position = projection * vec4(in_Vertex, 1.0);
	color = vec4(in_Color, 1.0);
	
}