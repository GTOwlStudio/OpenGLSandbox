#version 330 core

in vec3 in_Vertex;
in vec3 in_Normal;

uniform mat4 matrix;
uniform mat4 world;

out vec3 Normal0;

void main(){

	gl_Position = matrix * vec4(in_Vertex, 1.0);
	Normal0 = (world* vec4(in_Normal, 0.0)).xyz;
	
}