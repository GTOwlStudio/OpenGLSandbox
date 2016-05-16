#version 330 core

in vec2 texCoords;
uniform sampler2D texture0;

out vec4 out_Color;

void main(){
	float depth = texture(texture0, texCoords).r;
	//depth=10*log(depth)+1;
	out_Color = vec4(depth, depth, depth, 1.);
}