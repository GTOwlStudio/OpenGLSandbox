#version 330 core
in vec2 texCoord;
uniform sampler2D texture0;

out vec4 out_Color;

/*
vec3 g(vec3 p){
	g = p/(0.125)
}*/

void main(){
	
	//out_Color = floor(texture(texture0, texCoord)/0.05);
	out_Color = texture(texture0, texCoord)+vec4(+1.0, 0.0, 0.0, 1.0);
	//out_Color = texture(texture0, texCoord)/vec4(2.0, 0.0, 0.0, 1.0);
}

