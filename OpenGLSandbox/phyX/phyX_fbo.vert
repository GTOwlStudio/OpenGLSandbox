#version 330 core

//uniform sampler2D tex;
in vec2 in_Vertex;
in vec2 in_TexCoord0;

uniform mat4 projection;
uniform mat4 modelview;

//uniform sampler2D ftex;

out vec2 texCoord;

void main(){
	//sampler2D t = tex;
	gl_Position = vec4(in_Vertex, 1.0, 1.0);
	texCoord = in_TexCoord0;
	//gl_Position = projection * modelview * vec4(1.0, 1.0, 1.0, 1.0);
	
}