#pragma once

//get offscreen

enum GOS_TARGET {
	
	GOS_DEPTHBUFFER

};

class GOS
{
public:
	GOS(GOS_TARGET target);
	~GOS();
	void load();
	void render();
	
private:
	

};

