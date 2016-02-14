#version 330 core

in vec2 texCoord;
uniform sampler2D texture0;

out vec4 out_Color;

void main(){
	
	out_Color = texture(texture0, texCoord)+vec4(0.4, 0.0, 0.0, 1.0);
	
}