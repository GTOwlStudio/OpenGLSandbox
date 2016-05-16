#version 330 core

in vec3 in_Vertex;

uniform mat4 matrix;

void main(){
	
	gl_Position =  matrix * vec4(in_Vertex, 1.0);
	
}