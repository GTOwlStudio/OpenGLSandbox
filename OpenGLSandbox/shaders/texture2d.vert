#version 330 core

in vec2 in_Vertex;
in vec2 in_TexCoord0;

uniform mat4 matrix;

out vec2 texCoords;

void main(){
	
	gl_Position = matrix * vec4(in_Vertex, 1.0, 1.0);
	texCoords = in_TexCoord0;
}