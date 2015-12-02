#version 330 core

layout(triangles) in;
layout(line_strip, max_vertices=300) out;

void main(){
	for (float t=0.0f;t<1;t+=0.01){
		gl_Position = (pow(1-t, 2)*gl_in[0].gl_Position) + (2*t*(1-t)*gl_in[1].gl_Position) + (pow(t, 2)*gl_in[2].gl_Position);
		EmitVertex();
	}
	/*for (int i=0;i<150;i++){
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}*/
	EndPrimitive();
}