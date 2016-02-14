#version 330 core

in vec2 in_Vertex;
in vec2 in_TexCoord0;

out vec2 texCoord;

void main(){
	//vec2 pos = vec2(0.5,0.5);
	gl_Position = vec4(in_Vertex,1.0,1.0);
	texCoord = in_TexCoord0;	
}


