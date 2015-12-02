// Version du GLSL

#version 150 core


// Entrée

in vec4 color;


// Sortie 

out vec4 out_Color;


// Fonction main

void main()
{
    // Couleur finale du pixel

    out_Color = vec4(color);
	//out_Color = vec4(1.0,0.0,1.0,1.0);
}
