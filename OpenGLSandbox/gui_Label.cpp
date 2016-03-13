#include "gui_Label.h"
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset)((char*)NULL + (offset))
#endif

gui_Label::gui_Label(std::string text, FontAtlas &atlas, glm::vec4 xysxsy, float depth, float r, float g, float b) :
	m_text(text),
	m_textSize(m_text.length()), m_vaoID(0), m_vboID(0),
	m_shader("shaders/font_dev.vert", "shaders/font_dev.frag"), m_x(xysxsy.x),
	m_y(xysxsy.y), m_depth(depth), m_nbreOfParameter(0)
	//,m_maxWidth(0)
{
	//	initParameter(text);
	m_coordsBytesSize = sizeof(float)*m_textSize * 18;
	m_colorsBytesSize = sizeof(float)*m_textSize * 18;
	m_texCoordsBytesSize = sizeof(float)*m_textSize * 12;
	//	printf("Theorical Size = %i\n", (m_coordsBytesSize+m_colorsBytesSize+m_texCoordsBytesSize)/sizeof(float));


	m_color = new float[m_textSize * 18];
	m_color[0] = r;
	m_color[1] = g;
	m_color[2] = b;
	for (int i = 3; i < m_textSize * 18; i += 3) {
		m_color[i] = m_color[0];
		m_color[i + 1] = m_color[1];
		m_color[i + 2] = m_color[2];
	}
	m_fontatlas = &atlas;
	m_coord = new glm::vec4[m_textSize * 6];
	m_coords = new float[m_textSize * 18]; //3 float for one vertices, 1 quad is 2 triangle, 1 triangle is 3 vertices, so m_coordSize * (3*2) * 3 = m_coordSize*18
	m_texCoords = new float[m_textSize * 12];

	float dev_w = (float)m_fontatlas->getAtlasWidth();
	float dev_h = (float)m_fontatlas->getAtlasHeight();

	float sx = 1.0;
	//xysxsy.z;
	float sy = 1.0;
	//xysxsy.w;

	Util::dev("m_text.c_str() = %s\n", m_text.c_str());
	float x3 = m_x;
	float y3 = m_y;/* - m_fontatlas->getFontHeight();*/
	float ax, ay, bw, bh, bl, bt, tx, ty, bx, by, w, h;
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
		bh = m_fontatlas->getCharInfo()[*p].bh;
		/*bl = m_fontatlas->getCharInfo()[*p].bl;
		bt = m_fontatlas->getCharInfo()[*p].bt;*/
		tx = m_fontatlas->getCharInfo()[*p].tx;
		ty = m_fontatlas->getCharInfo()[*p].ty;

		w = m_fontatlas->getCharInfo()[*p].w;
		h = m_fontatlas->getCharInfo()[*p].h;

		bx = m_fontatlas->getCharInfo()[*p].bx;
		by = m_fontatlas->getCharInfo()[*p].by;


		//bh=m_fontatlas->getFontHeight();
		/*float tmpCoord[18] = {x3+bl, y3+ay+bt+bh, depth,
								x3+bl,y3+ay+bt, depth,
								x3+bl+bw,y3+ay+bt, depth,
								x3+bl, y3+ay+bh+bt, depth,
								x3+bl+bw,y3+ay+bt, depth,
								x3+bl+bw,y3+ay+bh+bt, depth};*/

								/*	float tmpCoord[18] = {	x3 + bl,	y3 + ay + (bt-bh), depth,
															x3 + bl,	y3 + ay + bt, depth,
															x3 + bl +bw,y3 + ay + bt, depth,
															x3 + bl,	y3 + ay + (bt - bh) , depth,
															x3 + bl +bw,y3 + ay + bt, depth,
															x3 + bl +bw,y3 + ay + (bt - bh), depth };*/

		float tmpCoord[18] = { x3 + bx,		y3 + by, depth,
							x3 + bx,		y3 - (h-by), depth,
							x3 + bx + w,	y3 - (h-by), depth,
							x3 + bx,		y3 + by, depth,
							x3 + bx + w,	y3 - (h-by), depth,
							x3 + bx + w,	y3 + by, depth };

		/*float tmpCoord[18] = { x3 + bl,	y3 + ay + bt+bh, depth,
			x3 + bl,	y3 + ay + bt , depth,
			x3 + bl + bw,	y3 + ay +bt , depth,
			x3 + bl , y3 + ay + bt+bh,depth,
			x3 + bl + bw, y3 + ay + bt , depth,
			x3 + bl + bw,y3 + ay + bt+bh, depth };*/


		float tmpTexCoords[12] = { (tx - bw) / dev_w,ty / dev_h,
								(tx - bw) / dev_w,	(ty + bh) / dev_h,
								(tx) / dev_w,		(ty + bh) / dev_h,
								(tx - bw) / dev_w,	ty / dev_h,
								tx / dev_w,		(ty + bh) / dev_h,
								tx / dev_w,		ty / dev_h };


		for (int i = 0; i < 18; i++) {
			m_coords[i + coordOffset] = tmpCoord[i];

		}
		coordOffset += 18;

		for (int i = 0; i < 12; i++) {
			m_texCoords[i + texCoordOffset] = tmpTexCoords[i];
			if (m_text == "T") {
				//printf("%f\t", m_texCoords[i + texCoordOffset]);
			}
		}
		if (m_text == "T") {

			Util::green("%f %f %f %f \n", m_texCoords[4], m_texCoords[1], m_texCoords[0], m_texCoords[3]);
			Util::green("x:%f y:%f w:%f h:%f  ", tx, ty, tx - bw, ty + bh);
			Util::green("tw:%f th:%f\n", dev_w, dev_h);
		}
		texCoordOffset += 12;
		//	FileUtil::stringToFile(FileUtil::arrayToString(m_coords, 18, 3), "dev_test/quad_coords.txt");
		//	FileUtil::stringToFile(FileUtil::arrayToString(m_texCoords, 18, 3), "dev_test/quad_texcoords.txt");

		x3 += ax;
	}

}

gui_Label::gui_Label(std::string text, FontAtlas &atlas, float x, float y, float depth, float r, float g, float b) :
	m_text(text),
	m_textSize(m_text.length()), m_vaoID(0), m_vboID(0),
	m_shader("shaders/font_dev.vert", "shaders/font_dev.frag"), m_x(x),
	m_y(y), m_depth(depth), m_nbreOfParameter(0)
	//,m_maxWidth(0)
{
	m_shader.load();
	m_coordsBytesSize = sizeof(float)*m_textSize * 18;
	m_colorsBytesSize = sizeof(float)*m_textSize * 18;
	m_texCoordsBytesSize = sizeof(float)*m_textSize * 18;


	m_color = new float[m_textSize * 18];
	m_color[0] = r;
	m_color[1] = g;
	m_color[2] = b;
	for (int i = 3; i < m_textSize * 18; i += 3) {
		m_color[i] = m_color[0];
		m_color[i + 1] = m_color[1];
		m_color[i + 2] = m_color[2];
	}
	m_fontatlas = &atlas;
	m_coord = new glm::vec4[m_textSize * 6];
	m_coords = new float[m_textSize * 18]; //3 float for one vertices, 1 quad is 2 triangle, 1 triangle is 3 vertices, so m_coordSize * (3*2) * 3 = m_coordSize*18
	m_texCoords = new float[m_textSize * 12];

	float dev_w = (float)m_fontatlas->getAtlasWidth();
	float dev_h = (float)m_fontatlas->getAtlasHeight();

	float x3 = m_x;
	float y3 = m_y;/* -m_fontatlas->getFontHeight();*/
	float ax, ay, bw, bh, w, h, tx, ty, bx, by;
	bh = 0;
	int coordOffset = 0;
	int texCoordOffset = 0;
	//	float dev_size = 0;
	//	float dev_v = 0;
		//int dev_size = 0;
	for (const char *p = m_text.c_str(); *p; p++) {
		//std::printf("p=%c\n", p);
		//cn = n+32;
		//std::cout << "cn=" << cn << std::endl;
		//std::printf("p=%c", *p);
		//std::printf(" m_fontatlas->getCharInfo()[*p]=%i",*p);

	/*	float x2 = m_x + m_fontatlas->getCharInfo()[*p].bl;
		float y2 = -m_y - m_fontatlas->getCharInfo()[*p].bt;*/
		/*float w = m_fontatlas->getCharInfo()[*p].bw;
		float h = m_fontatlas->getCharInfo()[*p].bh;*/
		//std::printf(" x2=%i y2=%i w=%i h=%i\n",x2, y2, w, h);
		m_x += m_fontatlas->getCharInfo()[*p].ax;
		m_y += m_fontatlas->getCharInfo()[*p].ay;



		ax = m_fontatlas->getCharInfo()[*p].ax;
		ay = m_fontatlas->getCharInfo()[*p].ay;
		bw = m_fontatlas->getCharInfo()[*p].bw;
		bh = m_fontatlas->getCharInfo()[*p].bh;
		
		w = m_fontatlas->getCharInfo()[*p].w;
		h = m_fontatlas->getCharInfo()[*p].h;

		bx = m_fontatlas->getCharInfo()[*p].bx;
		by = m_fontatlas->getCharInfo()[*p].by;

		tx = m_fontatlas->getCharInfo()[*p].tx;
		ty = m_fontatlas->getCharInfo()[*p].ty;
		

		float tmpCoord[18] = { x3 + bx,		y3 + by, depth,
			x3 + bx,		y3 - (h - by), depth,
			x3 + bx + w,	y3 - (h - by), depth,
			x3 + bx,		y3 + by, depth,
			x3 + bx + w,	y3 - (h - by), depth,
			x3 + bx + w,	y3 + by, depth };

		float tmpTexCoords[18] = { (tx - bw) / dev_w,ty / dev_h, (tx - bw) / dev_w,(ty + bh) / dev_h, (tx) / dev_w,(ty + bh) / dev_h,
				(tx - bw) / dev_w,ty / dev_h, tx / dev_w,(ty + bh) / dev_h, tx / dev_w,ty / dev_h };

		for (int i = 0; i < 18; i++) {
			m_coords[i + coordOffset] = tmpCoord[i];
		}
		coordOffset += 18;

		for (int i = 0; i < 12; i++) {
			m_texCoords[i + texCoordOffset] = tmpTexCoords[i];
			if (p[0] == 84) {
				printf("T displayed");
			}
		}
		texCoordOffset += 12;


		x3 += ax;
	}
	//printf("dev_v=%f\n", dev_v);

}
gui_Label & gui_Label::operator=(gui_Label const & labelToCopy)
{
	/*if (this != &labelToCopy) {
		m_text = labelToCopy.m_text;
		m_
	}*/
	return *this;
}

void gui_Label::update() {

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

void gui_Label::load() {
	m_shader.load();
	if (glIsBuffer(m_vboID) == GL_TRUE) {
		std::cout << "glIsBuffer() = GL_TRUE vboID = " << m_vboID << std::endl;

		glDeleteBuffers(1, &m_vboID);
	}



	glGenBuffers(1, &m_vboID);
	//printf("VBO size");
	printf("m_vboID = %i\n", m_vboID);
	//printf("dev_vertSize=%i dev_texSize=%i", dev_vertSize, dev_texSize);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	/*glBufferData(GL_ARRAY_BUFFER, m_coordsBytesSize+ dev_texSize, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_coordsBytesSize, m_coords);
	glBufferSubData(GL_ARRAY_BUFFER, m_coordsBytesSize, dev_texSize, dev_tex);*/
	glBufferData(GL_ARRAY_BUFFER, m_coordsBytesSize + m_texCoordsBytesSize + m_colorsBytesSize, 0, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_coordsBytesSize, m_coords);
	glBufferSubData(GL_ARRAY_BUFFER, m_coordsBytesSize, m_texCoordsBytesSize, m_texCoords);
	glBufferSubData(GL_ARRAY_BUFFER, m_coordsBytesSize + m_texCoordsBytesSize, m_colorsBytesSize, m_color);
	/*glBufferData(GL_ARRAY_BUFFER, m_coordsBytesSize, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_coordsBytesSize, m_coords);
	//glBufferSubData(GL_ARRAY_BUFFER, dev_vertSize, dev_texSize, dev_tex);*/
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (glIsVertexArray(m_vaoID) == GL_TRUE) {
		//	std::cout << "glIsVertexArray() = GL_TRUE vaoID = " << m_vaoID << std::endl;
		glDeleteVertexArrays(1, &m_vaoID);
	}

	glGenVertexArrays(1, &m_vaoID);

	glBindVertexArray(m_vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_coordsBytesSize + m_texCoordsBytesSize));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_coordsBytesSize));
	glEnableVertexAttribArray(2);
	/*glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);*/
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

gui_Label::~gui_Label()
{
	m_fontatlas = 0;
	glDeleteBuffers(1, &m_vboID);
	glDeleteVertexArrays(1, &m_vaoID);
	//delete m_fontatlas;

	//delete[] m_locationOfParamater;
	delete[] m_coord;
	delete[] m_coords;
	delete[] m_color;
	delete[] m_texCoords;
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

void gui_Label::render(glm::mat4 &projection, glm::mat4 &modelview) {

	glUseProgram(m_shader.getProgramID());
	glBindVertexArray(m_vaoID);

	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(modelview));

	glBindTexture(GL_TEXTURE_2D, m_fontatlas->getTexID());

	glDrawArrays(GL_TRIANGLES, 0, (m_textSize)* 6);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);

}

void gui_Label::setText(std::string text)
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

	//Util::dev("m_text.c_str() = %s\n", m_text.c_str());
	float x3 = m_x;
	float y3 = m_y;/* -m_fontatlas->getFontHeight();*/
	float ax, ay, bw, bh, w,h, tx, ty, bx, by;
	bh = 0;
	int coordOffset = 0;
	int texCoordOffset = 0;
	for (const char *p = m_text.c_str(); *p; p++) {

		/*float x2 = m_x + m_fontatlas->getCharInfo()[*p].bl*sx;
		float y2 = -m_y - m_fontatlas->getCharInfo()[*p].bt*sy;*/
		/*float w = m_fontatlas->getCharInfo()[*p].bw*sx;
		float h = m_fontatlas->getCharInfo()[*p].bh*sy;*/
		//std::printf(" x2=%i y2=%i w=%i h=%i\n",x2, y2, w, h);
		//m_x += m_fontatlas->getCharInfo()[*p].ax * sx;
		m_y += m_fontatlas->getCharInfo()[*p].ay *sy;



		ax = m_fontatlas->getCharInfo()[*p].ax;
		ay = m_fontatlas->getCharInfo()[*p].ay;
		bw = m_fontatlas->getCharInfo()[*p].bw;
		bh = m_fontatlas->getCharInfo()[*p].bh;

		w = m_fontatlas->getCharInfo()[*p].w;
		h = m_fontatlas->getCharInfo()[*p].h;
		
		bx = m_fontatlas->getCharInfo()[*p].bx;
		by = m_fontatlas->getCharInfo()[*p].by;
		tx = m_fontatlas->getCharInfo()[*p].tx;
		ty = m_fontatlas->getCharInfo()[*p].ty;

		bh = m_fontatlas->getFontHeight();
		float tmpCoord[18] = { x3 + bx,		y3 + by, m_depth,
			x3 + bx,		y3 - (h - by), m_depth,
			x3 + bx + w,	y3 - (h - by), m_depth,
			x3 + bx,		y3 + by, m_depth,
			x3 + bx + w,	y3 - (h - by), m_depth,
			x3 + bx + w,	y3 + by, m_depth };

		float tmpTexCoords[12] = { (tx - bw) / dev_w,	ty / dev_h,
			(tx - bw) / dev_w,	(ty + bh) / dev_h,
			(tx) / dev_w,	(ty + bh) / dev_h,
			(tx - bw) / dev_w,	ty / dev_h,
			tx / dev_w,	(ty + bh) / dev_h,
			tx / dev_w,	ty / dev_h };


		for (int i = 0; i < 18; i++) {
			m_coords[i + coordOffset] = tmpCoord[i];
		}
		coordOffset += 18;

		for (int i = 0; i < 12; i++) {
			m_texCoords[i + texCoordOffset] = tmpTexCoords[i];
		}
		texCoordOffset += 12;
		//	FileUtil::stringToFile(FileUtil::arrayToString(m_coords, 18, 3), "dev_test/quad_coords.txt");
		//	FileUtil::stringToFile(FileUtil::arrayToString(m_texCoords, 18, 3), "dev_test/quad_texcoords.txt");

		x3 += ax;
	}
	load();
}

void gui_Label::replace(size_t first, size_t last, std::string text)
{
	if (last - first < 0) {
		Util::error("replace() function invalid value, condition : last>first");
		return;
	}

	m_text.replace(first, last, text);
	//std::cout << m_text << std::endl;
	//std::cout << m_text << std::endl;
	//Util::dev("%s\n",m_text);
	float ax, ay, bm, w, h, bw, bh, tx, ty, bx, by;
	bh = m_fontatlas->getFontHeight();
	float dev_w = (float)m_fontatlas->getAtlasWidth();
	float dev_h = (float)m_fontatlas->getAtlasHeight();
	float x3 = m_x + (m_coords[first * 18] - m_x);
	//	printf("x3=%f\n",x3);
	float y3 = m_y - m_fontatlas->getFontHeight();
	for (int i = 0; i < last - first; i++) {
		//printf("m_text[%i]=%c\n", i+first, m_text[i+first]);
		//bw = m_fontatlas->getCharInfo()[m_text[i + first]].bw;

		ax = m_fontatlas->getCharInfo()[m_text[i + first]].ax;
		ay = m_fontatlas->getCharInfo()[m_text[i + first]].ay;

		bw = m_fontatlas->getCharInfo()[m_text[i + first]].bw;
		bh = m_fontatlas->getCharInfo()[m_text[i + first]].bh;

		w = m_fontatlas->getCharInfo()[m_text[i + first]].w;
		h = m_fontatlas->getCharInfo()[m_text[i + first]].h;

		bx = m_fontatlas->getCharInfo()[m_text[i + first]].bx;
		by = m_fontatlas->getCharInfo()[m_text[i + first]].by;
		tx = m_fontatlas->getCharInfo()[m_text[i + first]].tx;
		ty = m_fontatlas->getCharInfo()[m_text[i + first]].ty;

		float tmpCoords[18] = { x3 + bx,		y3 + by, m_depth,
			x3 + bx,		y3 - (h - by), m_depth,
			x3 + bx + w,	y3 - (h - by), m_depth,
			x3 + bx,		y3 + by, m_depth,
			x3 + bx + w,	y3 - (h - by), m_depth,
			x3 + bx + w,	y3 + by, m_depth };


		float tmpTexCoords[12] = { (tx - bw) / dev_w,	ty / dev_h,
									(tx - bw) / dev_w,	(ty + bh) / dev_h,
									(tx) / dev_w,	(ty + bh) / dev_h,
									(tx - bw) / dev_w,	ty / dev_h,
									tx / dev_w,	(ty + bh) / dev_h,
									tx / dev_w,	ty / dev_h };
		for (int t = 0; t < 18; t++) {
			m_coords[first + (i * 18) + t] = tmpCoords[t];
			//tmpCoords[t] = 12.0f;
			//printf("%i\n", first + (i * 18) + t);

		}
		for (int t = 0; t < 12; t++) {
			//printf("%i value=%f\n", first + (i * 12) + t, tmpTexCoords[t]);
			m_texCoords[first + (i * 12) + t] = tmpTexCoords[t];
			//tmpTexCoords[t] = 1.0f;
		//	printf("%i\n", first + (i * 12) + t);
		}
		x3 += ax;
		//printf("size=%i offset=%i byteOffset=%i tmpOffset=%i\n", sizeof(float)*12, (m_coordsBytesSize/12) + (((i + first))*(12)) + (((i + first))*(sizeof(float) * 12)), m_coordsBytesSize / (2 * (sizeof(float)))+ i+first,8*6+(i+first)*6);
		updateVBO(tmpTexCoords, sizeof(float) * 12, m_coordsBytesSize + (((i + first))*(sizeof(float) * 12)));
		updateVBO(tmpCoords, sizeof(float) * 18, (((i + first))*(sizeof(float) * 18)));
	}

}

void gui_Label::setParameter(unsigned int parameter, int value)
{
	//m_text.replace(m_parameters[parameter].);
	//m_parameters();
}

void gui_Label::updateVBO(void* datas, unsigned int bytesSize, unsigned int offset) {
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	void *VBOAddress = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	if (VBOAddress == NULL) {
		std::cout << "ERROR : while VBO recuperation" << std::endl;
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		return;
	}

	memcpy((char*)VBOAddress + offset, datas, bytesSize);

	glUnmapBuffer(GL_ARRAY_BUFFER);
	VBOAddress = 0;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void gui_Label::setPosition(float x, float y) {
	/*printf("m_x=%f m_y=%f\n", m_x, m_y);
	printf("x=%f, y=%f\n", x-m_x, y-m_y);*/
	move(x - m_x, y - m_y);
	m_x = x; m_y = y;
}

void gui_Label::setBounds(float w, float h) {
	Util::error("Dont use set bounds on gui_Label, not supported yet");
}

void gui_Label::move(float relX, float relY) {

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

FontAtlas* gui_Label::getFont() const {
	return m_fontatlas;
}

std::string gui_Label::getText() const
{
	return m_text;
}

void gui_Label::setShaderSource(std::string vert, std::string frag) {
	m_shader.setSourceFile(vert, frag);
}

void gui_Label::initParameter(std::string const & input)
{
	std::vector<int> tmp;

	for (int i = 0; i < input.length(); i++) {
		if (input[i] == '%' && input[i + 1] == 'i') {
			m_nbreOfParameter += 1;
			tmp.push_back(i);
			m_parameters.emplace(i, input[i]);//insert(i,input[i]);
		}
	}
	/*delete[] m_locationOfParamater;
	m_locationOfParamater = new int[m_nbreOfParameter];
	for (int i = 0; i <m_nbreOfParameter;i++) {
		m_locationOfParamater[i] = tmp[i];
	}*/

}