#version 330 core


struct DirectionalLight{
	vec3 Color;
	float AmbientIntensity;
};

in vec3 normal;

out vec4 out_Color;


void main(){
	
	//vec3 material = vec3(1.0, 1.0, 1.0);
	
	DirectionalLight gDirectionalLight;
	gDirectionalLight.Color = vec3(1.0, 1.0, 1.0);
	gDirectionalLight.AmbientIntensity= 1.0;
	
	out_Color = vec4(normal * gDirectionalLight.Color * gDirectionalLight.AmbientIntensity, 1.0);

}