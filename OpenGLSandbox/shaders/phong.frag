#version 330
//TODO deal with uniform at the begining of the main() func
in vec3 Normal0;       
in vec3 WorldPos0;                                                             
                                                                                    
out vec4 FragColor;                                                                 
                                                                                    
struct DirectionalLight                                                             
{                                                                                   
    vec3 Color;                                                                     
    float AmbientIntensity;                                                         
    float DiffuseIntensity;                                                         
    vec3 Direction;                                                                 
};                                                                                  
                                                                                                                                    
void main()                                                                         
{     
	//Uniform
	vec3 gEyeWorldPos;
	float gSpecularPower;
	float gMatSpecularIntensity;    
	//********
	DirectionalLight gDirectionalLight;
	gDirectionalLight.Color = vec3(1.0, 1.0, 1.0);
	gDirectionalLight.AmbientIntensity = 0.8f;
	gDirectionalLight.DiffuseIntensity = 0.75f;
	gDirectionalLight.Direction = vec3(1.0, 0.0, 0.0);
	
	vec4 AmbientColor = vec4(gDirectionalLight.Color * gDirectionalLight.AmbientIntensity, 1.0f);                
	vec3 LightDirection = -gDirectionalLight.Direction;
	vec3 Normal = normalize(Normal0);
	
	
	float DiffuseFactor = dot(Normal, LightDirection);
	
	vec4 DiffuseColor = vec4(0,0,0,0);
	vec4 specularColor = vec4(0,0,0,0);
	
	if (DiffuseFactor >0){
		Diffusecolor = vec4(gDirectionalLight.Color * gDirectionalLight.DiffuseIntensity * DiffuseFactor, 1.0f);
		vec3 VertexToEye = normalize(gEyeWorldPos - WorldPos);
		vec3 LightReflect = normalize(reflect(gDirectionalLight.Direction, Normal));
		float SpecularFactor = dot(VertexToEye, LightReflect);
		if (SpecularFactor>0){
			SpecularFactor = pow(SpecularFactor, gSpecularPower);
			SpecularColor = vec4(gDirectionalLight.Color * gMatSpecularIntensity * SpecularFactor, 1.0f);
		}
	}
	
	FragColor = vec4(DirectionalLight.Color, 1.0f) * (AmbientColor + DiffuseColor + SpecularColor);
	
	/*DirectionalLight gDirectionalLight;
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
                                                                                    
    FragColor =  vec4(gDirectionalLight.Color,1.0)*(AmbientColor + DiffuseColor);     */ 
}
