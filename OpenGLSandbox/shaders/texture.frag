// Version du GLSL

#version 330 core


// Entrée

in vec2 coordTexture;


// Uniform

uniform sampler2D texture0;


// Sortie 

out vec4 out_Color;


// Fonction main

void main()
{
    // Couleur du pixel
	//vec4 color = vec4(0,1,0,0);
	//float alphacolorvalue = 1.0;
    out_Color = texture(texture0, coordTexture);
	//out_Color = vec4(0,1,1,0);
}
