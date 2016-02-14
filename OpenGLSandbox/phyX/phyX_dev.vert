#version 330 core

//uniform sampler2D tex;
in vec2 in_Vertex;
in vec2 in_TexCoord0;

uniform mat4 projection;
uniform mat4 modelview;
uniform sampler2D texture0;
//uniform sampler2D ftex;

out vec3 color;

/*float u(float x, float z, float Lx, float Dx){
	return x +(Lx*(z-(Dx*floor(z-Dx))));
}

float v(float x, float y, float Ly, float Dx){
	return y+(Ly* floor(x/Dx));
}*/

float u4096_64(float x, float z){
	return x+(64*(z-(4096*floor(x/4096))));
}

float v4096_64(float x, float y){
	return y+(64*floor(x/4096));
}

vec2 util_4096_64(float x, float y, float z){
	return vec2(x+(64*(z-(4096*floor(x/4096)))),y+(64*floor(x/4096)));
}

vec2 util_4096_64(vec3 v){
	return vec2(v.x+(64*(v.z-(4096*floor(v.x/4096)))),v.y+(64*floor(v.x/4096)));
}

vec3 cIdv2_64(int id){
	return vec3(id-(64*floor(id/64)), floor(id/64)-(floor(id/(4096))*64), floor(id/(4096)));
}

void main(){
	bool ok = true;
	//sampler2d t = tex;
	//color = vec3(1.0,0.0,1.0);
	//color = vec3(cIdv2_64(gl_VertexID*16)/64.0);
	vec2 tc = vec2(util_4096_64(cIdv2_64(gl_VertexID)/vec3(64.0,64.0,64.0)));///vec2();
	tc.x /= 64;
	/*if (tc.x==0||tc.y==0){
		//color = vec3(1.0, 0.0,0.0);
	}*/
	vec3 pos;
	pos.x = texture(texture0,tc).r;
	pos.y = texture(texture0,tc).g;
	pos.z = texture(texture0,tc).b;
	color = vec3(pos);
	/*if (pos.x>0.0||tc.x>1.0||tc.x<0.0){
		color = vec3(1.0, 0.0, 1.0);
		pos = vec3(0.5, 0.0, 0.5);
		if (tc.x>1.0){
			pos = vec3(0.6,0.0,0.5);
		}
	}*/

	//gl_position = vec4(pos, 1.0, 1.0);
	gl_Position = projection * modelview * vec4(pos, 1.0);
	//gl_position = projection * modelview * vec4(1.0, 1.0, 1.0, 1.0);
	
}