#version 330 core

in vec2 in_Vertex;
in vec2 in_TexCoord0;

out vec2 texCoord;

void main(){

	gl_Position = in_Vertex;
	texCoord = in_TexCoord0;

}
