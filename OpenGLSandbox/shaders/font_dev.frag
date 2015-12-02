// Version du GLSL

#version 330 core


// Entrée

in vec3 color;
in vec2 coordTexture;


// Uniform

uniform sampler2D texture0;


// Sortie 

out vec4 out_Color;


// Fonction main

void main()
{
	//out_Color = vec4(color, 0.5);
	out_Color = vec4(1,1,1, texture2D(texture0, coordTexture).r) * vec4(color,1.0); 
	
}
