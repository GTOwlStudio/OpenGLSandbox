#version 330 compatibility

layout(points) in;
layout(line_strip, max_vertices=11) out;

const float PI = 3.1415926;

void main(){
	for(int i=0;i<=10;i++){
		float ang = PI *2.0 /10.0 *i;
		vec4 offset = vec4(cos(ang)*0.2, -sin(ang)*0.34, 0.0, 0.0);
		gl_Position = gl_in[0].gl_Position+offset/4.0;
		EmitVertex();
	}
	EndPrimitive();
}