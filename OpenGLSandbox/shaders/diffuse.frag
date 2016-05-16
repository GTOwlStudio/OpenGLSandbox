#version 330
//TODO deal with uniform at the begining of the main() func
in vec3 Normal0;                                                                   

out vec4 FragColor;                                                                 

struct DirectionalLight                                                             
{                                                                                   
    vec3 Color;                                                                     
    float AmbientIntensity;                                                         
    float DiffuseIntensity;                                                         
    vec3 Direction;                                                                 
};                                                                                  

void main(){
	DirectionalLight gDirectionalLight;
	gDirectionalLight.Color = vec3(1.0, 1.0, 1.0);
	gDirectionalLight.AmbientIntensity = 0.8f;
	gDirectionalLight.DiffuseIntensity = 0.75f;
	gDirectionalLight.Direction = vec3(1.0, 0.0, 0.0);

	vec4 AmbientColor = vec4(gDirectionalLight.Color * gDirectionalLight.AmbientIntensity, 1.0f);                

	float DiffuseFactor = dot(normalize(Normal0), -gDirectionalLight.Direction);    

	vec4 DiffuseColor;                                                              

	if (DiffuseFactor > 0) {                                                        
        DiffuseColor = vec4(gDirectionalLight.Color, 1.0f) *                        
                       gDirectionalLight.DiffuseIntensity *                         
                       DiffuseFactor;                                               
    }                                                                               
    else {                                                                          
        DiffuseColor = vec4(0, 0, 0, 0);                                            
    }                                                                               
  
	FragColor =  vec4(gDirectionalLight.Color,1.0)*(AmbientColor + DiffuseColor);     
}