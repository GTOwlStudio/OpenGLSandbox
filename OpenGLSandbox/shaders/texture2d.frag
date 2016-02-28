#version 330 core

in vec2 texCoords;
uniform sampler2D texture0;

out vec4 out_Color;

void main(){
	
	out_Color = texture(texture0, texCoords);
	
}