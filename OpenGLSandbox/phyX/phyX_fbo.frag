#version 330 core

in vec2 texCoord;

uniform sampler2D texture0;

out vec4 out_Color;

void main(){
	//out_Color = vec3(1.0, 0.0, 1.0);
	//gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);
	//out_Color = vec4(1.0, 0.0, 1.0, 1.0);
	//out_Color = texture(texture0, vec2(1.0, 1.0));
	out_Color = texture(texture0, texCoord);//*vec4(1.0,0.0,0.0,1.0);
}