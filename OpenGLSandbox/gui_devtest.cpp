#include "gui_devtest.h"
#ifndef BUFFER_OFFSET
	#define BUFFER_OFFSET(offset)((char*)NULL + (offset))
#endif

gui_devtest::gui_devtest(std::string text, FontAtlas &atlas, glm::vec4 xysxsy, float depth, float r, float g, float b) : 
	m_text(text), 
	m_textSize(m_text.length()), m_vaoID(0), m_vboID(0), 
	m_shader("shaders/font_dev.vert", "shaders/font_dev.frag"), m_x(xysxsy.x),
	m_y(xysxsy.y), m_depth(depth)
{
	m_shader.load();
	m_coordsBytesSize = sizeof(float)*m_textSize*18;
	m_texCoordsBytesSize = sizeof(float)*m_textSize*18;

	

	m_color[0] = r;
	m_color[1] = g;
	m_color[2] = b;
	m_fontatlas = &atlas;
	m_coord = new glm::vec4[m_textSize*6];
	m_coords = new float[m_textSize*18]; //3 float for one vertices, 1 quad is 2 triangle, 1 triangle is 3 vertices, so m_coordSize * (3*2) * 3 = m_coordSize*18
	m_texCoords = new float[m_textSize*12];

	/*dev_vertSize = sizeof(float)*18;
	float tmpdev_vert[18] = {50.0,14.0,0.0,	50.0,32.0,0.0,	64.0,32.0,0.0,
					50.0,14.0,0.0,	64.0,32.0,0.0,	64.0,14.0,0.0};
	dev_texSize = sizeof(float)*12;*/
/*	float tmpdev_tex[12] = {0.0,1.0, 1.0,1.0, 0.0,0.0, 
								0.0,0.0, 1.0,1.0, 1.0, 0.0};*/
	float dev_w = (float)m_fontatlas->getAtlasWidth();
	float dev_h = (float)m_fontatlas->getAtlasHeight();
	/*float tmpdev_tex[12] = {53.0/dev_w,42.0/dev_h,	53.0/dev_w,24.0/dev_h,	65.0/dev_w,24.0/dev_h, 
								53.0/dev_w,42.0/dev_h,	65.0/dev_w,24.0/dev_h, 65.0/dev_w,42.0/dev_h};*/
	/*float tmpdev_tex[12] = {52.0/dev_w,24.0/dev_h,	52.0/dev_w,42.0/dev_h,	66.0/dev_w,42.0/dev_h, 
								52.0/dev_w,24.0/dev_h,	66.0/dev_w,42.0/dev_h, 66.0/dev_w,24.0/dev_h};
	for (int i =0;i<18;i++){
		dev_vert[i] = tmpdev_vert[i];
	}
	for (int i =0;i<12;i++){
		dev_tex[i] = tmpdev_tex[i];
	}*/

	float sx = xysxsy.z;
	float sy = xysxsy.w;
	

	/**int n = 0;
	int o = 0;*/

	//int atlas_width = m_fontatlas->getAtlasWidth();
	//int atlas_height = m_fontatlas->getAtlasHeight();
	//std::printf("m_text.c_str() = %s\n", m_text.c_str());

	float x3 = m_x;
	float y3 = m_y-m_fontatlas->getFontHeight();
	float ax,ay,bw,bh,w,h,tx,ty,bx,by;
	bh = 0;
	int coordOffset = 0;
	int texCoordOffset = 0;
//	float dev_size = 0;
//	float dev_v = 0;
	//int dev_size = 0;
	for (const char *p = m_text.c_str(); *p ;p++){
		//std::printf("p=%c\n", p);
		//cn = n+32;
		//std::cout << "cn=" << cn << std::endl;
		//std::printf("p=%c", *p);
		//std::printf(" m_fontatlas->getCharInfo()[*p]=%i",*p);

/*		float x2 = m_x+m_fontatlas->getCharInfo()[*p].bl*sx;
		float y2 = -m_y - m_fontatlas->getCharInfo()[*p].bt*sy;*/
		/*float w = m_fontatlas->getCharInfo()[*p].bw*sx;
		float h = m_fontatlas->getCharInfo()[*p].bh*sy;*/
		//std::printf(" x2=%i y2=%i w=%i h=%i\n",x2, y2, w, h);
		//m_x += m_fontatlas->getCharInfo()[*p].ax * sx;
		m_y += m_fontatlas->getCharInfo()[*p].ay *sy;
		
		
		
		ax = m_fontatlas->getCharInfo()[*p].ax;
		ay = m_fontatlas->getCharInfo()[*p].ay;
		bw = m_fontatlas->getCharInfo()[*p].bw;
		//bh = m_fontatlas->getCharInfo()[*p].bh;
		w = m_fontatlas->getCharInfo()[*p].w;
		h = m_fontatlas->getCharInfo()[*p].h;
		tx = m_fontatlas->getCharInfo()[*p].tx;
		ty = m_fontatlas->getCharInfo()[*p].ty;
		bx = m_fontatlas->getCharInfo()[*p].bx;
		by = m_fontatlas->getCharInfo()[*p].by;

		/*float charInfoValues[6] = {ax, ay,bw,bh,bl,bt};
		std::string charInfoValuesNames[6] = {"ax","ay","bw","bh","bl", "bt"};
		for (int i = 0;i<6;i++){
			std::cout << charInfoValuesNames[i];
			std::printf("=%f\n", charInfoValues[i]);
		}
		*/
		//std::cout << " ax=" <<ax;

		//if (!w||!h){continue;}
		//std::cout << " ns="<<n;//<< std::endl;
		//PROBLEM
		//printf("x2=%f  -y2=%f\n", x2, -y2);
		//std::printf("\nx2=%f y2=%f w=%f h=%f\n",x2, y2, w, h);
		/*m_coord[n++] = glm::vec4(x2,	-y2,	m_fontatlas->getCharInfo()[*p].tx,
			0);
		m_coord[n++] = glm::vec4(x2+w,	-y2,	m_fontatlas->getCharInfo()[*p].tx + m_fontatlas->getCharInfo()[*p].bw/atlas_width,
			0);
		m_coord[n++] = glm::vec4(x2,	-y2 - h,m_fontatlas->getCharInfo()[*p].tx, 
			m_fontatlas->getCharInfo()[*p].bh / atlas_height);
		m_coord[n++] = glm::vec4(x2+w,	-y2,	m_fontatlas->getCharInfo()[*p].tx+m_fontatlas->getCharInfo()[*p].bw / atlas_width,
			0);
		m_coord[n++] = glm::vec4(x2,	-y2 - h,m_fontatlas->getCharInfo()[*p].tx, 
			m_fontatlas->getCharInfo()[*p].bh/atlas_height);
		m_coord[n++] = glm::vec4(x2+w,	-y2 - h,m_fontatlas->getCharInfo()[*p].tx+m_fontatlas->getCharInfo()[*p].bw/atlas_width, 
			m_fontatlas->getCharInfo()[*p].bh/atlas_height);*/
	

		//printf("tx=%f =%f\n", tx, ty);
		//printf("ax=%f ay=%f bt=%f bh=%f bl=%f bw=%f\n", ax, ay,bt,bh,bl,bw);
		//printf("y3+(ay-bt-bh)=%f\n",y3+(ay+bt+bh));
		//bh = 18;
	/*	if (std::max(bh, m_fontatlas->getCharInfo()[*p].bh)==bh){
			//printf("%i MAX is bh=%i\n",m_fontatlas->getCharInfo()[*p].bh, bh);
		}*/
		//printf("m_textSize=%i", m_textSize);
		//bh = std::max(bh, m_fontatlas->getCharInfo()[*p].bh);
		/*float tmpCoord[18] = {x3+bl, y3+(ay-bt-bh), depth,
								x3+bl,y3+(ay-bt), depth,
								x3+bl+bw,y3+(ay-bt), depth,
								x3+bl, y3+(ay-bt-bh), depth,
								x3+bl+bw,y3+(ay-bt), depth,
								x3+bl+bw,y3+(ay-bt-bh), depth};*/
		float tmpCoord[18] = { x3 + bx,		y3 + by, depth,
			x3 + bx,		y3 - (h - by), depth,
			x3 + bx + w,	y3 - (h - by), depth,
			x3 + bx,		y3 + by, depth,
			x3 + bx + w,	y3 - (h - by), depth,
			x3 + bx + w,	y3 + by, depth };
		//dev_size += bw+bl;
		//The Old Good one below
		/*float tmpCoord[18] = {x3+bl, y3+(ay+bt+bh), depth,
								x3+bl,y3+(ay+bt), depth,
								x3+bl+bw,y3+(ay+bt), depth,
								x3+bl, y3+(ay+bt+bh), depth,
								x3+bl+bw,y3+(ay+bt), depth,
								x3+bl+bw,y3+(ay+bt+bh), depth};*/
		//dev_size+=bw;

		float tmpTexCoords[18] = {(tx-bw)/dev_w,ty/dev_h, (tx-bw)/dev_w,(ty+bh)/dev_h, (tx)/dev_w,(ty+bh)/dev_h,	
				(tx-bw)/dev_w,ty/dev_h, tx/dev_w,(ty+bh)/dev_h, tx/dev_w,ty/dev_h};


		for (int i =0;i<18;i++){
			m_coords[i+coordOffset] = tmpCoord[i];
			//std::printf(" m_tmpCoord[%i] = %f\n", i, tmpCoord[i]);
			//std::printf(" m_coords[%i] = %f\n", i+coordOffset, m_coords[i+coordOffset]);
			//std::cout << tmpCoord<< std::endl;
		}
		coordOffset+=18;

		for (int i=0;i<12;i++){
			m_texCoords[i+texCoordOffset] = tmpTexCoords[i];
			//printf("m_texCoord[%i]=%f\n", i+texCoordOffset, m_texCoords[i+texCoordOffset]);
		}
		texCoordOffset+=12;

		/*m_coords[o++] = x2;
		m_coords[o++] = y2;
		m_coords[o++] = depth;
		m_coords[o++] = x2;
		m_coords[o++] = x2+h;
		m_coords[o++] = depth;
		m_coords[o++] = w+h;
		m_coords[o++] = x2+h;
		m_coords[o++] = depth;*/
		
		//std::printf(" ne=%i\n", n);
		//printf("dev_size=%i\n", dev_size);
		//dev_size = x3;
		
		
		x3 += ax;
		//dev_v += x3-dev_size;
		//printf("dx->%f\n", x3-dev_size);
		//printf("dev_size=%f\n", dev_size);
	}
	//printf("dev_v=%f\n", dev_v);

}

gui_devtest::gui_devtest(std::string text, FontAtlas &atlas, float x, float y, float depth, float r, float g, float b) : 
	m_text(text), 
	m_textSize(m_text.length()), m_vaoID(0), m_vboID(0), 
	m_shader("shaders/font_dev.vert", "shaders/font_dev.frag"), m_x(x),
	m_y(y), m_depth(depth)
{
	m_shader.load();
	m_coordsBytesSize = sizeof(float)*m_textSize*18;
	m_texCoordsBytesSize = sizeof(float)*m_textSize*18;

	

	m_color[0] = r;
	m_color[1] = g;
	m_color[2] = b;
	m_fontatlas = &atlas;
	m_coord = new glm::vec4[m_textSize*6];
	m_coords = new float[m_textSize*18]; //3 float for one vertices, 1 quad is 2 triangle, 1 triangle is 3 vertices, so m_coordSize * (3*2) * 3 = m_coordSize*18
	m_texCoords = new float[m_textSize*12];

	/*dev_vertSize = sizeof(float)*18;
	float tmpdev_vert[18] = {50.0,14.0,0.0,	50.0,32.0,0.0,	64.0,32.0,0.0,
					50.0,14.0,0.0,	64.0,32.0,0.0,	64.0,14.0,0.0};
	dev_texSize = sizeof(float)*12;*/
/*	float tmpdev_tex[12] = {0.0,1.0, 1.0,1.0, 0.0,0.0, 
								0.0,0.0, 1.0,1.0, 1.0, 0.0};*/
	float dev_w = (float)m_fontatlas->getAtlasWidth();
	float dev_h = (float)m_fontatlas->getAtlasHeight();
	/*float tmpdev_tex[12] = {53.0/dev_w,42.0/dev_h,	53.0/dev_w,24.0/dev_h,	65.0/dev_w,24.0/dev_h, 
								53.0/dev_w,42.0/dev_h,	65.0/dev_w,24.0/dev_h, 65.0/dev_w,42.0/dev_h};*/
	/*float tmpdev_tex[12] = {52.0/dev_w,24.0/dev_h,	52.0/dev_w,42.0/dev_h,	66.0/dev_w,42.0/dev_h, 
								52.0/dev_w,24.0/dev_h,	66.0/dev_w,42.0/dev_h, 66.0/dev_w,24.0/dev_h};
	for (int i =0;i<18;i++){
		dev_vert[i] = tmpdev_vert[i];
	}
	for (int i =0;i<12;i++){
		dev_tex[i] = tmpdev_tex[i];
	}*/
	

	/**int n = 0;
	int o = 0;*/

	//int atlas_width = m_fontatlas->getAtlasWidth();
	//int atlas_height = m_fontatlas->getAtlasHeight();
	//std::printf("m_text.c_str() = %s\n", m_text.c_str());

	float x3 = m_x;
	float y3 = m_y-m_fontatlas->getFontHeight();
	float ax,ay,bw,bh,w,h,tx,ty,bx,by;
	bh = 0;
	int coordOffset = 0;
	int texCoordOffset = 0;
//	float dev_size = 0;
//	float dev_v = 0;
	bool dev_v=false;
	for (const char *p = m_text.c_str(); *p ;p++){
		//std::printf("p=%c\n", p);
		//cn = n+32;
		//std::cout << "cn=" << cn << std::endl;
		//std::printf("p=%c", *p);
		//std::printf(" m_fontatlas->getCharInfo()[*p]=%i",*p);

	/*	float w = m_fontatlas->getCharInfo()[*p].bw;
		float h = m_fontatlas->getCharInfo()[*p].bh;*/
		//std::printf(" x2=%i y2=%i w=%i h=%i\n",x2, y2, w, h);
		m_x += m_fontatlas->getCharInfo()[*p].ax;
		m_y += m_fontatlas->getCharInfo()[*p].ay;
		
		
		
		ax = (float)m_fontatlas->getCharInfo()[*p].ax;
		ay = (float)m_fontatlas->getCharInfo()[*p].ay;
		bw = (float)m_fontatlas->getCharInfo()[*p].bw;
		bh = m_fontatlas->getCharInfo()[*p].bh;
		w = (float)m_fontatlas->getCharInfo()[*p].w;
		h = (float)m_fontatlas->getCharInfo()[*p].h;
		tx = (float)m_fontatlas->getCharInfo()[*p].tx;
		ty = (float)m_fontatlas->getCharInfo()[*p].ty;
		bx = (float)m_fontatlas->getCharInfo()[*p].bx;
		by = (float)m_fontatlas->getCharInfo()[*p].by;


		/*float charInfoValues[6] = {ax, ay,bw,bh,bl,bt};
		std::string charInfoValuesNames[6] = {"ax","ay","bw","bh","bl", "bt"};
		for (int i = 0;i<6;i++){
			std::cout << charInfoValuesNames[i];
			std::printf("=%f\n", charInfoValues[i]);
		}
		*/
		//std::cout << " ax=" <<ax;

		//if (!w||!h){continue;}
		//std::cout << " ns="<<n;//<< std::endl;
		//PROBLEM
		//printf("x2=%f  -y2=%f\n", x2, -y2);
		//std::printf("\nx2=%f y2=%f w=%f h=%f\n",x2, y2, w, h);
		/*m_coord[n++] = glm::vec4(x2,	-y2,	m_fontatlas->getCharInfo()[*p].tx,
			0);
		m_coord[n++] = glm::vec4(x2+w,	-y2,	m_fontatlas->getCharInfo()[*p].tx + m_fontatlas->getCharInfo()[*p].bw/atlas_width,
			0);
		m_coord[n++] = glm::vec4(x2,	-y2 - h,m_fontatlas->getCharInfo()[*p].tx, 
			m_fontatlas->getCharInfo()[*p].bh / atlas_height);
		m_coord[n++] = glm::vec4(x2+w,	-y2,	m_fontatlas->getCharInfo()[*p].tx+m_fontatlas->getCharInfo()[*p].bw / atlas_width,
			0);
		m_coord[n++] = glm::vec4(x2,	-y2 - h,m_fontatlas->getCharInfo()[*p].tx, 
			m_fontatlas->getCharInfo()[*p].bh/atlas_height);
		m_coord[n++] = glm::vec4(x2+w,	-y2 - h,m_fontatlas->getCharInfo()[*p].tx+m_fontatlas->getCharInfo()[*p].bw/atlas_width, 
			m_fontatlas->getCharInfo()[*p].bh/atlas_height);*/
	

		//printf("tx=%f ty=%f\n", tx, ty);
		//printf("ax=%f ay=%f bt=%f bh=%f bl=%f bw=%f\n", ax, ay,bt,bh,bl,bw);
		//printf("y3+(ay-bt-bh)=%f\n",y3+(ay+bt+bh));
		//bh = 18;
	/*	if (std::max(bh, m_fontatlas->getCharInfo()[*p].bh)==bh){
			//printf("%i MAX is bh=%i\n",m_fontatlas->getCharInfo()[*p].bh, bh);
		}*/
		bh=(float)m_fontatlas->getFontHeight();
		//printf("m_textSize=%i", m_textSize);
		//bh = std::max(bh, m_fontatlas->getCharInfo()[*p].bh);
		/*float tmpCoord[18] = {x3+bl, y3+(ay-bt-bh), depth,
								x3+bl,y3+(ay-bt), depth,
								x3+bl+bw,y3+(ay-bt), depth,
								x3+bl, y3+(ay-bt-bh), depth,
								x3+bl+bw,y3+(ay-bt), depth,
								x3+bl+bw,y3+(ay-bt-bh), depth};*/
		float tmpCoord[18] = { x3 + bx,		y3 + by, depth,
			x3 + bx,		y3 - (h - by), depth,
			x3 + bx + w,	y3 - (h - by), depth,
			x3 + bx,		y3 + by, depth,
			x3 + bx + w,	y3 - (h - by), depth,
			x3 + bx + w,	y3 + by, depth };
		//printf("bw=%f\n", bw);
		//dev_size += bw+bl;
		//The Old Good one below
		/*float tmpCoord[18] = {x3+bl, y3+(ay+bt+bh), depth,
								x3+bl,y3+(ay+bt), depth,
								x3+bl+bw,y3+(ay+bt), depth,
								x3+bl, y3+(ay+bt+bh), depth,
								x3+bl+bw,y3+(ay+bt), depth,
								x3+bl+bw,y3+(ay+bt+bh), depth};*/
		//dev_size+=bw;

		/*float tmpTexCoords[18] = {(tx-bw)/dev_w,ty/dev_h, (tx-bw)/dev_w,(ty+bh)/dev_h, (tx)/dev_w,(ty+bh)/dev_h,	
				(tx-bw)/dev_w,ty/dev_h, tx/dev_w,(ty+bh)/dev_h, tx/dev_w,ty/dev_h};*/
		//printf();
		float tmpTexCoords[18] = {(tx-bw)/dev_w,ty/dev_h,	(tx-bw)/dev_w,(ty+bh)/dev_h,	(tx)/dev_w,(ty+bh)/dev_h,	
								(tx-bw)/dev_w,ty/dev_h,		tx/dev_w,(ty+bh)/dev_h,			tx/dev_w,ty/dev_h};

		
		float fftcoord[18]; //For File TexCoords
		for (int i=0;i<18;i++){
			if (i%2){
				fftcoord[i] = tmpTexCoords[i]*dev_h;	
				
				//printf("%i\n", i);
			}
			else{
					fftcoord[i] = tmpTexCoords[i]*dev_w;	
			}
			
		}

		//FileUtil::arrayToFile("dev_test/quad_coords.txt", tmpCoord, 0, 3, 6, MODE_OVERRIDE);
		FileUtil::stringToFile(FileUtil::arrayToString(tmpCoord, 18, 3), "dev_test/quad_coords.txt");
		FileUtil::stringToFile(FileUtil::arrayToString(tmpTexCoords, 12, 2), "dev_test/quad_texcoords.txt");
		//printf("float=%lf\n", 0.00000005);
		for (int i =0;i<18;i++){
			m_coords[i+coordOffset] = tmpCoord[i];
			//std::printf(" m_tmpCoord[%i] = %d\n", i, tmpCoord[i]);
			//std::printf(" m_coords[%i] = %f\n", i+coordOffset, m_coords[i+coordOffset]);
			//std::cout << tmpCoord<< std::endl;
		}
		coordOffset+=18;

		for (int i=0;i<12;i++){
			m_texCoords[i+texCoordOffset] = tmpTexCoords[i];
			
			/*if (dev_v){
				printf("m_texCoord[%i]=%lf\n", i+texCoordOffset, m_texCoords[i+texCoordOffset]*dev_h);
			}else{
				printf("m_texCoord[%i]=%lf\n", i+texCoordOffset, m_texCoords[i+texCoordOffset]*dev_w);
			}
			dev_v = !dev_v;*/
		}
		texCoordOffset+=12;

		/*m_coords[o++] = x2;
		m_coords[o++] = y2;
		m_coords[o++] = depth;
		m_coords[o++] = x2;
		m_coords[o++] = x2+h;
		m_coords[o++] = depth;
		m_coords[o++] = w+h;
		m_coords[o++] = x2+h;
		m_coords[o++] = depth;*/
		
		//std::printf(" ne=%i\n", n);
		//printf("dev_size=%i\n", dev_size);
		//dev_size = x3;
		
		
		x3 += ax;
		//dev_v += x3-dev_size;
		//printf("dx->%f\n", x3-dev_size);
		//printf("dev_size=%f\n", dev_size);
	}
	//printf("dev_v=%f\n", dev_v);

}

void gui_devtest::update(){

}

//void gui_devtest::load(){
//	
//	std::cout << "Slow method use for debugging when its fixes take it off\n the function is FileUtil::arrayToFile located in load() of gui_Label.cpp" << std::endl;
//	FileUtil::arrayToFile("dev_test/label_coord.txt", m_coords, 0, m_coordSize*6, 3, MODE_OVERRIDE);
//	/*if (glIsBuffer(m_vboID)==GL_FALSE){
//		glDeleteBuffers(1, &m_vboID);
//	}
//	glGenBuffers(1, &m_vboID);
//	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
//		//glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float)*m_coordSize, m_coord, GL_STATIC_DRAW);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*m_coordSize*18, m_coords, GL_STATIC_DRAW);
//	//glBufferData(GL_ARRAY_BUFFER, sizeof(float)*18, 0, GL_STATIC_DRAW);
//	//	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*18, testArray);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	if (glIsVertexArray(m_vaoID)!=GL_FALSE){
//		glDeleteVertexArrays(1, &m_vaoID);
//	}
//	glGenVertexArrays(1, &m_vaoID);
//	glBindVertexArray(m_vaoID);
//		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
//		glVertexAttribPointer(0, 3,GL_FLOAT, GL_FALSE, 0, 0);
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);*/
//
//	float testArray[18] = {50.0,14.0,0.0,	50.0,32.0,0.0,	64.0,32.0,0.0,
//					50.0,14.0,0.0,	64.0,32.0,0.0,	64.0,14.0,0.0};
//
//	float testTexCoord[12] = {0.0,1.0, 1.0,1.0, 0.0,0.0, 
//								0.0,0.0, 1.0,1.0, 1.0, 0.0};
//	FileUtil::arrayToFile("dev_test/label_coord.txt", testArray, 0, 6, 3, MODE_OVERRIDE);
//	int vSize = sizeof(float)*18;
//	int texSize = sizeof(float)*12;
//	if (glIsBuffer(m_vboID)==GL_TRUE){
//		std::cout << "glIsBuffer() = GL_TRUE vboID = " << m_vboID << std::endl;
//		glDeleteBuffers(1, &m_vboID);
//	}
//
//	glGenBuffers(1, &m_vboID);
//
//	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
//		glBufferData(GL_ARRAY_BUFFER, vSize+texSize, 0, GL_STATIC_DRAW);
//		glBufferSubData(GL_ARRAY_BUFFER, 0, vSize, testArray);
//		glBufferSubData(GL_ARRAY_BUFFER, vSize, texSize, testTexCoord);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	if (glIsVertexArray(m_vaoID)==GL_TRUE){
//		std::cout << "glIsVertexArray() = GL_TRUE vaoID = " << m_vaoID << std::endl;
//		glDeleteVertexArrays(1, &m_vaoID);
//	}
//
//	glGenVertexArrays(1, &m_vaoID);
//
//	glBindVertexArray(m_vaoID);
//		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
//		
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,BUFFER_OFFSET(0));
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vSize));
//		glEnableVertexAttribArray(2);
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//}

void gui_devtest::load(){

	if (glIsBuffer(m_vboID)==GL_TRUE){
		std::cout << "glIsBuffer() = GL_TRUE vboID = " << m_vboID << std::endl;

		glDeleteBuffers(1, &m_vboID);
	}

	

	glGenBuffers(1, &m_vboID);
	//printf("dev_vertSize=%i dev_texSize=%i", dev_vertSize, dev_texSize);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	
	/*glBufferData(GL_ARRAY_BUFFER, m_coordsBytesSize+ dev_texSize, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_coordsBytesSize, m_coords);
	glBufferSubData(GL_ARRAY_BUFFER, m_coordsBytesSize, dev_texSize, dev_tex);*/
	glBufferData(GL_ARRAY_BUFFER, m_coordsBytesSize+m_texCoordsBytesSize, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_coordsBytesSize, m_coords);
	glBufferSubData(GL_ARRAY_BUFFER, m_coordsBytesSize, m_texCoordsBytesSize, m_texCoords);
	/*glBufferData(GL_ARRAY_BUFFER, m_coordsBytesSize, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_coordsBytesSize, m_coords);
	//glBufferSubData(GL_ARRAY_BUFFER, dev_vertSize, dev_texSize, dev_tex);*/
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (glIsVertexArray(m_vaoID)==GL_TRUE){
		std::cout << "glIsVertexArray() = GL_TRUE vaoID = " << m_vaoID << std::endl;
		glDeleteVertexArrays(1, &m_vaoID);
	}

	glGenVertexArrays(1, &m_vaoID);

	glBindVertexArray(m_vaoID);
		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,BUFFER_OFFSET(0));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_coordsBytesSize));
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

gui_devtest::~gui_devtest()
{
	m_fontatlas = 0;
	glDeleteBuffers(1, &m_vboID);
	glDeleteVertexArrays(1, &m_vaoID);
	//delete m_fontatlas;

	delete[] m_coord;
	delete[] m_coords;
	delete[] m_texCoords;
}

//void gui_devtest::render(glm::mat4 &projection, glm::mat4 &modelview){
//
//	/*glUseProgram(m_shader.getProgramID());
//		glBindVertexArray(m_vaoID);
//			glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//			glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(modelview));
//
//			glBindTexture(GL_TEXTURE_2D, m_fontatlas->getTexID());
//			glDrawArrays(GL_TRIANGLES, 0, m_coordSize*6);
//			//glDrawArrays(GL_TRIANGLES, 0, 6);
//			glBindTexture(GL_TEXTURE_2D, 0);
//			
//		glBindVertexArray(0);
//	glUseProgram(0);*/
//
//	/*glUseProgram(m_shader.getProgramID());
//		glBindVertexArray(m_vaoID);
//			glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//			glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(modelview));
//
//			glBindTexture(GL_TEXTURE_2D, m_fontatlas->getTexID());
//			glDrawArrays(GL_TRIANGLES, 0, m_coordSize*6);
//			//glDrawArrays(GL_TRIANGLES, 0, 6);
//			glBindTexture(GL_TEXTURE_2D, 0);
//			
//		glBindVertexArray(0);
//	glUseProgram(0);*/
//	glUseProgram(m_shader.getProgramID());
//	   glBindVertexArray(m_vaoID);
//
//            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(modelview));
//
//            glBindTexture(GL_TEXTURE_2D, m_fontatlas->getTexID());
//
//            glDrawArrays(GL_TRIANGLES, 0, 6);
//
//			glBindTexture(GL_TEXTURE_2D, 0);
//        glBindVertexArray(0);
//	glUseProgram(0);
//
//}

void gui_devtest::render(glm::mat4 &projection, glm::mat4 &modelview){
	
	glUseProgram(m_shader.getProgramID());
	   glBindVertexArray(m_vaoID);

            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(modelview));

            glBindTexture(GL_TEXTURE_2D,  m_fontatlas->getTexID());

			glDrawArrays(GL_TRIANGLES, 0, m_textSize*6);

			glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);
	glUseProgram(0);

}

void gui_devtest::updateVBO(void* datas, unsigned int bytesSize, unsigned int offset){
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	void *VBOAddress = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	if (VBOAddress==NULL){
		std::cout << "ERROR : while VBO recuperation" << std::endl;
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		return;
	}

	memcpy((char*)VBOAddress + offset, datas,bytesSize);

	glUnmapBuffer(GL_ARRAY_BUFFER);
	VBOAddress = 0;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void gui_devtest::setPosition(float x, float y){
	/*printf("m_x=%f m_y=%f\n", m_x, m_y);
	printf("x=%f, y=%f\n", x-m_x, y-m_y);*/
	move(x-m_x,y-m_y);
	m_x=x;m_y=y;
}

void gui_devtest::move(float relX, float relY){
	for (int i=0;i<18*m_textSize;i+=2){
		m_coords[i] += relX;
		i++;
		m_coords[i] += relY;
	}
	updateVBO(m_coords, m_coordsBytesSize, 0);
}

FontAtlas* gui_devtest::getFont() const{
	return m_fontatlas;
}