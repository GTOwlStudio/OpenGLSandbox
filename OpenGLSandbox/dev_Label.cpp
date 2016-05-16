#include "dev_Label.h"
#ifndef BUFFER_OFFSET
	#define BUFFER_OFFSET(offset)((char*)NULL + (offset))
#endif

dev_Label::dev_Label(std::string text, FontAtlas &atlas, glm::vec4 xysxsy, float depth, float r, float g, float b) : 
	m_text(text), 
	m_textSize(m_text.length()), m_vaoID(0), m_vboID(0), m_iboID(0), 
	m_shader("shaders/font_dev.vert", "shaders/font_dev.frag"), m_x(xysxsy.x),
	m_y(xysxsy.y), m_depth(depth)
	//,m_maxWidth(0)
{

	m_coordsBytesSize = sizeof(float)*m_textSize*12;
	m_colorsBytesSize = sizeof(float)*m_textSize*12;
	m_texCoordsBytesSize = sizeof(float)*m_textSize*8;
	m_indicesBytesSize = sizeof(unsigned int)*m_textSize*6;

	printf("Theorical Size = %i\n", (m_coordsBytesSize+m_colorsBytesSize+m_texCoordsBytesSize)/sizeof(float));

	
	m_color = new float[m_textSize * 12];
	m_color[0] = r;
	m_color[1] = g;
	m_color[2] = b;
	for (int i = 3; i < m_textSize*12;i+=3) {
		m_color[i] = m_color[0];
		m_color[i+1] = m_color[1];
		m_color[i+2] = m_color[2];
	}
	m_fontatlas = &atlas;
	m_coord = new glm::vec4[m_textSize*6];
	// m_coords = new float[m_textSize*18]; //3 float for one vertices, 1 quad is 2 triangle, 1 triangle is 3 vertices, so m_coordSize * (3*2) * 3 = m_coordSize*18
	//m_texCoords = new float[m_textSize*12];
	m_coords = new float[m_textSize * 12]; //3 float for one vertices, 1 quad is 2 triangle, 1 triangle is 3 vertices, so m_coordSize * (3*2) * 3 = m_coordSize*18
	m_texCoords = new float[m_textSize * 12];
	m_indices = new unsigned int[m_textSize*6];
	m_indices[0] = 0;
	m_indices[1] = 1;
	m_indices[2] = 3;
	m_indices[3] = 3;
	m_indices[4] = 1;
	m_indices[5] = 2;
	for (int i = 6; i < m_textSize * 6;i+=6) {
		m_indices[i] = m_indices[i-6]+4;
		m_indices[i + 1] = m_indices[i-5]+4;
		m_indices[i + 2] = m_indices[i-4]+4;
		m_indices[i + 3] = m_indices[i-3]+4;
		m_indices[i + 4] = m_indices[i-2]+4;
		m_indices[i + 5] = m_indices[i-1]+4;
	}

	float dev_w = (float)m_fontatlas->getAtlasWidth();
	float dev_h = (float)m_fontatlas->getAtlasHeight();

	float sx = 1.0;
		//xysxsy.z;
	float sy = 1.0;
	//xysxsy.w;
	
	Util::dev("m_text.c_str() = %s\n", m_text.c_str());
	float x3 = m_x;
	float y3 = m_y-m_fontatlas->getFontHeight();
	float ax,ay,bw,w,h,bh,tx,ty,bx,by;
	int coordOffset = 0;
	int texCoordOffset = 0;
	for (const char *p = m_text.c_str(); *p ;p++){

	/*	float x2 = m_x+m_fontatlas->getCharInfo()[*p].bl*sx;
		float y2 = -m_y - m_fontatlas->getCharInfo()[*p].bt*sy;*/
		float w = m_fontatlas->getCharInfo()[*p].bw*sx;
		float h = m_fontatlas->getCharInfo()[*p].bh*sy;
		//std::printf(" x2=%i y2=%i w=%i h=%i\n",x2, y2, w, h);
		//m_x += m_fontatlas->getCharInfo()[*p].ax * sx;
		m_y += m_fontatlas->getCharInfo()[*p].ay *sy;
		
		
		
		ax = m_fontatlas->getCharInfo()[*p].ax;
		ay = m_fontatlas->getCharInfo()[*p].ay;
		bw = m_fontatlas->getCharInfo()[*p].bw;
		bh = m_fontatlas->getCharInfo()[*p].bh;
		w = m_fontatlas->getCharInfo()[*p].w;
		h = m_fontatlas->getCharInfo()[*p].h;
		tx = m_fontatlas->getCharInfo()[*p].tx;
		ty = m_fontatlas->getCharInfo()[*p].ty;
		bx = m_fontatlas->getCharInfo()[*p].bx;
		by = m_fontatlas->getCharInfo()[*p].by;

		// Counter Clock Coord Definition
		/*float tmpCoord[18] = {x3+bl,		y3+ay+bt+bh, depth,
								x3+bl,		y3+ay+bt, depth,
								x3+bl+bw,	y3+ay+bt, depth,
								x3+bl,		y3+ay+bt+bh, depth,
								x3+bl+bw,	y3+ay+bt, depth,
								x3+bl+bw,	y3+ay+bt+bh, depth};*/
		//Clock Coord Definition
		/*float tmpCoord[18] = { x3 + bl,			y3 + ay + bt + bh, depth, //1
								x3 + bl + bw,	y3 + ay + bt + bh, depth,//6
								x3 + bl,		y3 + ay + bt, depth,//2
								x3 + bl,		y3 + ay + bt, depth,//2
								x3 + bl + bw,	y3 + ay + bt + bh, depth,//6
								x3 + bl + bw,	y3 + ay + bt, depth,//5
								 };*/

		float tmpCoords[18] = { x3 + bx,		y3 + by, m_depth,
			x3 + bx,		y3 - (h - by), m_depth,
			x3 + bx + w,	y3 - (h - by), m_depth,
			x3 + bx,		y3 + by, m_depth,
			x3 + bx + w,	y3 - (h - by), m_depth,
			x3 + bx + w,	y3 + by, m_depth };

		/*Counter Clock Coord Definition
		float tmpTexCoords[18] = {(tx-bw)/dev_w,ty/dev_h, (tx-bw)/dev_w,(ty+bh)/dev_h, (tx)/dev_w,(ty+bh)/dev_h,	
				(tx-bw)/dev_w,ty/dev_h, tx/dev_w,(ty+bh)/dev_h, tx/dev_w,ty/dev_h};*/
		/*float tmpTexCoords[18] = { (tx - bw) / dev_w,	ty / dev_h, 
			(tx - bw) / dev_w,			(ty + bh) / dev_h,
			(tx) / dev_w,				(ty + bh) / dev_h,
			(tx - bw) / dev_w,			ty / dev_h,
			tx / dev_w,					(ty + bh) / dev_h, 
			tx / dev_w,					ty / dev_h };*/
		//Clock Tex Coord Definition
		/*float tmpTexCoords[18] = { (tx - bw) / dev_w,	ty / dev_h,//1
			tx / dev_w,					ty / dev_h, //6
			(tx - bw) / dev_w,			(ty + bh) / dev_h,//2
			(tx - bw) / dev_w,			(ty + bh) / dev_h,//2
			tx / dev_w,					ty / dev_h, //6
			(tx) / dev_w,				(ty + bh) / dev_h,//3
		};*/

		float tmpTexCoords[8] = { (tx - bw) / dev_w,	ty / dev_h,//1
			tx / dev_w,					ty / dev_h, //6
			(tx) / dev_w,				(ty + bh) / dev_h,//3
			(tx - bw) / dev_w,			(ty + bh) / dev_h//2			
		};

		/*float tmpTexCoords[8] = { (tx - bw) / dev_w,	ty / dev_h,//1
			tx / dev_w,					ty / dev_h, //6
			(tx) / dev_w,				(ty + bh) / dev_h,//3
			(tx - bw) / dev_w,			(ty + bh) / dev_h//2			
		};*/

		/*for (int i =0;i<18;i++){
			m_coords[i+coordOffset] = tmpCoord[i];
		}
		coordOffset+=18;*/

		for (int i = 0; i<12; i++) {
			m_coords[i + coordOffset] = tmpCoords[i];
		}
		coordOffset += 12;
		
		for (int i=0;i<8;i++){
			m_texCoords[i+texCoordOffset] = tmpTexCoords[i];
		}
		texCoordOffset+=8;
	//	FileUtil::stringToFile(FileUtil::arrayToString(m_coords, 18, 3), "dev_test/quad_coords.txt");
	//	FileUtil::stringToFile(FileUtil::arrayToString(m_texCoords, 18, 3), "dev_test/quad_texcoords.txt");
		
		x3 += ax;
	}

}

dev_Label::dev_Label(std::string text, FontAtlas &atlas, float x, float y, float depth, float r, float g, float b) : 
	m_text(text), 
	m_textSize(m_text.length()), m_vaoID(0), m_vboID(0), 
	m_shader("shaders/font_dev.vert", "shaders/font_dev.frag"), m_x(x),
	m_y(y), m_depth(depth)
	//,m_maxWidth(0)
{
	m_shader.load();
	m_coordsBytesSize = sizeof(float)*m_textSize*18;
	m_colorsBytesSize = sizeof(float)*m_textSize * 18;
	m_texCoordsBytesSize = sizeof(float)*m_textSize*18;

	
	m_color = new float[m_textSize*18];
	m_color[0] = r;
	m_color[1] = g;
	m_color[2] = b;
	for (int i = 3; i < m_textSize*18; i += 3) {
		m_color[i] = m_color[0];
		m_color[i + 1] = m_color[1];
		m_color[i + 2] = m_color[2];
	}
	m_fontatlas = &atlas;
	m_coord = new glm::vec4[m_textSize*6];
	m_coords = new float[m_textSize*18]; //3 float for one vertices, 1 quad is 2 triangle, 1 triangle is 3 vertices, so m_coordSize * (3*2) * 3 = m_coordSize*18
	m_texCoords = new float[m_textSize*12];

	float dev_w = (float)m_fontatlas->getAtlasWidth();
	float dev_h = (float)m_fontatlas->getAtlasHeight();

	float x3 = m_x;
	float y3 = m_y-m_fontatlas->getFontHeight();
	float ax,ay,bw,bh,w,h,tx,ty, bx, by;
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

		/*float x2 = m_x+m_fontatlas->getCharInfo()[*p].bl;
		float y2 = -m_y - m_fontatlas->getCharInfo()[*p].bt;*/
		/*float w = m_fontatlas->getCharInfo()[*p].bw;
		float h = m_fontatlas->getCharInfo()[*p].bh;*/
		//std::printf(" x2=%i y2=%i w=%i h=%i\n",x2, y2, w, h);
		m_x += m_fontatlas->getCharInfo()[*p].ax;
		m_y += m_fontatlas->getCharInfo()[*p].ay;
		
		
		
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

		float tmpCoords[18] = { x3 + bx,		y3 + by, m_depth,
			x3 + bx,		y3 - (h - by), m_depth,
			x3 + bx + w,	y3 - (h - by), m_depth,
			x3 + bx,		y3 + by, m_depth,
			x3 + bx + w,	y3 - (h - by), m_depth,
			x3 + bx + w,	y3 + by, m_depth };

		float tmpTexCoords[18] = {(tx-bw)/dev_w,ty/dev_h, (tx-bw)/dev_w,(ty+bh)/dev_h, (tx)/dev_w,(ty+bh)/dev_h,	
				(tx-bw)/dev_w,ty/dev_h, tx/dev_w,(ty+bh)/dev_h, tx/dev_w,ty/dev_h};

		for (int i =0;i<18;i++){
			m_coords[i+coordOffset] = tmpCoords[i];
		}
		coordOffset+=18;

		/*for (int i = 0; i<12; i++) {
			m_coords[i + coordOffset] = tmpCoord[i];
		}
		coordOffset += 12;*/

		for (int i=0;i<12;i++){
			m_texCoords[i+texCoordOffset] = tmpTexCoords[i];
		}
		texCoordOffset+=12;

		
		x3 += ax;
	}
	//printf("dev_v=%f\n", dev_v);

}
dev_Label & dev_Label::operator=(dev_Label const & labelToCopy)
{
	/*if (this != &labelToCopy) {
		m_text = labelToCopy.m_text;
		m_
	}*/
	return *this;
}

void dev_Label::update(){

}

//void gui_Label::load(){
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

void dev_Label::load(){
	m_shader.load();

	if (glIsVertexArray(m_vaoID) == GL_TRUE) {	glDeleteVertexArrays(1, &m_vaoID);}
	glGenVertexArrays(1, &m_vaoID);
	glBindVertexArray(m_vaoID);
		
		if (glIsBuffer(m_iboID) == GL_TRUE) { glDeleteBuffers(1, &m_iboID); }
		glGenBuffers(1, &m_iboID);
		Util::dev("(dev_Label) m_iboID=%i\n", m_iboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_indicesBytesSize, m_indices,GL_STATIC_DRAW);


		if (glIsBuffer(m_vboID)==GL_TRUE){ glDeleteBuffers(1, &m_vboID);}
		glGenBuffers(1, &m_vboID);
		glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
			glBufferData(GL_ARRAY_BUFFER, m_coordsBytesSize+m_texCoordsBytesSize+m_colorsBytesSize, 0, GL_STATIC_DRAW);
			glBufferSubData(GL_ARRAY_BUFFER, 0, m_coordsBytesSize, m_coords);
			glBufferSubData(GL_ARRAY_BUFFER, m_coordsBytesSize, m_texCoordsBytesSize, m_texCoords);
			glBufferSubData(GL_ARRAY_BUFFER, m_coordsBytesSize+m_texCoordsBytesSize, m_colorsBytesSize, m_color);


		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,BUFFER_OFFSET(0));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0,BUFFER_OFFSET(m_coordsBytesSize+m_texCoordsBytesSize));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_coordsBytesSize));
		glEnableVertexAttribArray(2);

	glBindVertexArray(0);

}

dev_Label::~dev_Label()
{
	m_fontatlas = 0;
	glDeleteBuffers(1, &m_vboID);
	glDeleteBuffers(1, &m_iboID);
	glDeleteVertexArrays(1, &m_vaoID);
	//delete m_fontatlas;

	delete[] m_coord;
	delete[] m_coords;
	delete[] m_color;
	delete[] m_texCoords;
	delete[] m_indices;
}

//void gui_Label::render(glm::mat4 &projection, glm::mat4 &modelview){
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

void dev_Label::render(glm::mat4 &projection, glm::mat4 &modelview){
	
	glUseProgram(m_shader.getProgramID());
	   glBindVertexArray(m_vaoID);

            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(modelview));

            glBindTexture(GL_TEXTURE_2D,  m_fontatlas->getTexID());

			//glDrawArrays(GL_TRIANGLES, 0, (m_textSize)*6);
			glDrawElements(GL_TRIANGLES, m_textSize*6, GL_UNSIGNED_INT, (void*)0);

			glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);
	glUseProgram(0);

}

void dev_Label::setText(std::string text)
{

	m_text = text;
	m_textSize = m_text.size();
	m_coordsBytesSize = sizeof(float)*m_textSize * 18;
	m_colorsBytesSize = sizeof(float)*m_textSize * 18;
	m_texCoordsBytesSize = sizeof(float)*m_textSize * 18;
	printf("Theorical Size = %i\n", (m_coordsBytesSize + m_colorsBytesSize + m_texCoordsBytesSize) / sizeof(float));

	float r = m_color[0];
	float g = m_color[1];
	float b = m_color[2];
	delete[] m_coord;
	delete[] m_coords;
	delete[] m_color;
	delete[] m_texCoords;
	m_color = new float[m_textSize * 18];
	m_color[0] = r;
	m_color[1] = g;
	m_color[2] = b;
	for (int i = 3; i < m_textSize * 18; i += 3) {
		m_color[i] = m_color[0];
		m_color[i + 1] = m_color[1];
		m_color[i + 2] = m_color[2];
	}
	//m_fontatlas = &atlas;
	m_coord = new glm::vec4[m_textSize * 6];
	m_coords = new float[m_textSize * 18]; //3 float for one vertices, 1 quad is 2 triangle, 1 triangle is 3 vertices, so m_coordSize * (3*2) * 3 = m_coordSize*18
	m_texCoords = new float[m_textSize * 12];

	float dev_w = (float)m_fontatlas->getAtlasWidth();
	float dev_h = (float)m_fontatlas->getAtlasHeight();

	float sx = 1.0f;// xysxsy.z;
	float sy = 1.0f;// xysxsy.w;

	Util::dev("m_text.c_str() = %s\n", m_text.c_str());
	float x3 = m_x;
	float y3 = m_y - m_fontatlas->getFontHeight();
	float ax, ay, bw, bh,w,h, tx, ty, bx, by;
	bh = 0;
	int coordOffset = 0;
	int texCoordOffset = 0;
	for (const char *p = m_text.c_str(); *p; p++) {

		/*float x2 = m_x + m_fontatlas->getCharInfo()[*p].bl*sx;
		float y2 = -m_y - m_fontatlas->getCharInfo()[*p].bt*sy;*/
		float w = m_fontatlas->getCharInfo()[*p].bw*sx;
		float h = m_fontatlas->getCharInfo()[*p].bh*sy;
		//std::printf(" x2=%i y2=%i w=%i h=%i\n",x2, y2, w, h);
		//m_x += m_fontatlas->getCharInfo()[*p].ax * sx;
		m_y += m_fontatlas->getCharInfo()[*p].ay *sy;



		ax = m_fontatlas->getCharInfo()[*p].ax;
		ay = m_fontatlas->getCharInfo()[*p].ay;
		bw = m_fontatlas->getCharInfo()[*p].bw;
		w = m_fontatlas->getCharInfo()[*p].w;
		h = m_fontatlas->getCharInfo()[*p].h;
		
		tx = m_fontatlas->getCharInfo()[*p].tx;
		ty = m_fontatlas->getCharInfo()[*p].ty;

		bx = m_fontatlas->getCharInfo()[*p].bx;
		by = m_fontatlas->getCharInfo()[*p].by;

		float tmpCoords[18] = { x3 + bx,		y3 + by, m_depth,
			x3 + bx,		y3 - (h - by), m_depth,
			x3 + bx + w,	y3 - (h - by), m_depth,
			x3 + bx,		y3 + by, m_depth,
			x3 + bx + w,	y3 - (h - by), m_depth,
			x3 + bx + w,	y3 + by, m_depth };

		float tmpTexCoords[18] = { (tx - bw) / dev_w,ty / dev_h, (tx - bw) / dev_w,(ty + bh) / dev_h, (tx) / dev_w,(ty + bh) / dev_h,
			(tx - bw) / dev_w,ty / dev_h, tx / dev_w,(ty + bh) / dev_h, tx / dev_w,ty / dev_h };


		for (int i = 0; i<18; i++) {
			m_coords[i + coordOffset] = tmpCoords[i];
		}
		coordOffset += 18;

		for (int i = 0; i<12; i++) {
			m_texCoords[i + texCoordOffset] = tmpTexCoords[i];
		}
		texCoordOffset += 12;
		//	FileUtil::stringToFile(FileUtil::arrayToString(m_coords, 18, 3), "dev_test/quad_coords.txt");
		//	FileUtil::stringToFile(FileUtil::arrayToString(m_texCoords, 18, 3), "dev_test/quad_texcoords.txt");

		x3 += ax;
	}
	load();
}

void dev_Label::updateVBO(void* datas, unsigned int bytesSize, unsigned int offset){
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

void dev_Label::setPosition(float x, float y){
	/*printf("m_x=%f m_y=%f\n", m_x, m_y);
	printf("x=%f, y=%f\n", x-m_x, y-m_y);*/
	move(x-m_x,y-m_y);
	m_x=x;m_y=y;
}

void dev_Label::setBounds(float w, float h){
	Util::error("Dont use set bounds on gui_Label, not supported yet");
}

void dev_Label::move(float relX, float relY){
	
		for (int i = 0; i < 18 * m_textSize; i += 2) {
			m_coords[i] += relX;
			i++;
			m_coords[i] += relY;
		}
		if (glIsBuffer(m_vboID)) {
			updateVBO(m_coords, m_coordsBytesSize, 0);
		}
		m_x += relX;
		m_y += relY;
}

FontAtlas* dev_Label::getFont() const{
	return m_fontatlas;
}

std::string dev_Label::getText() const
{
	return m_text;
}

void dev_Label::setShaderSource(std::string vert, std::string frag){
	m_shader.setSourceFile(vert, frag);
}