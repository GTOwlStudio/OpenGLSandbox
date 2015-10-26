#include "FontAtlas.h"


FontAtlas::FontAtlas(std::string fontfile, int fontHeight) : m_texID(0),
	m_fontFile(fontfile), m_font_height(fontHeight), m_width(512), m_height(0)/*,  
	m_shader("shaders/texture3D.vert", "shaders/texture3D.frag")*/
{
	if (FT_Init_FreeType(&m_ft)){
		std::cout << "Could not init freetype library\n";
		return;
	}

	if (FT_New_Face(m_ft, m_fontFile.c_str(), 0, &m_face)){
		std::cout << "Could not open font " << m_fontFile << std::endl;
		return;
	}
	FT_Set_Pixel_Sizes(m_face, 0, m_font_height);
	m_glypSlot = m_face->glyph;

	int last_w = 0; //last w value
	int last_h = 0; //last h value

	for (int i = 32;i<128;i++){
		if (FT_Load_Char(m_face, i, FT_LOAD_RENDER)){
			fprintf(stderr, "Loading character %c failed!\n", i);
			continue;
		}

		last_w+=m_glypSlot->bitmap.width;
		if (last_w>=512){
			last_w=0;
			last_h+=m_font_height;
		}
		last_h=std::max(last_h, m_glypSlot->bitmap.rows);
		//std::printf("last_w=%i last_h=%i rows=%i\n", last_w, last_h, m_glypSlot->bitmap.rows);
		//std::cout << last_w << "|" << last_h <<std::endl;

	}
	m_width=std::max(m_width, last_w);
	m_height+=last_h;

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &m_texID);
	glBindTexture(GL_TEXTURE_2D, m_texID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	std::printf("Texture size = (%i,%i)\n", m_width, m_height);

	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, m_width, m_height,0, GL_RED, GL_UNSIGNED_BYTE,0);
	//glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, 512, 48, 0, GL_RED, GL_UNSIGNED_BYTE,0);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	/* Linear filtering usually looks best for text */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//std::cout << last_w << "|" << last_h <<std::endl;
	std::printf("last (%i,%i)\n", last_w, last_h );
	int last_x = 0;
	int last_y = 0;
	//int tmp;
	std::printf("GlyphSlot Buffer size (%i, %i)\n", m_glypSlot->bitmap.width, m_glypSlot->bitmap.rows);
	
	for (int i=32;i<128;i++){
		if (FT_Load_Char(m_face, i, FT_LOAD_RENDER)){std::cout << "Failed To loadchar" << i << std::endl;}
		//if (FT_Load_Char(m_face, i, FT_LOAD_MONOCHROME)){std::cout << "Failed To loadchar" << i << std::endl;}
		//std::printf("%i char %c size (%i,%i)\n",i, i, m_glypSlot->bitmap.width, m_glypSlot->bitmap.rows);
		//tmp =last_x, +m_glypSlot->bitmap.width+1;
		//std::cout << tmp << std::endl;
		if (last_x+m_glypSlot->bitmap.width>= 512){
			last_x=0;
			last_y+=m_font_height;
		}

		/*if (last_y!=0&&last_x==0){
			printf("i=%i -> %c\n",i,i);
		}*/
		/*if (i==79){
			printf("%i %c x=%i y=%i\n", i,i, last_x,last_y);
		}*/
		//printf("%i %c x=%i y=%i\n", i,i, last_x,last_y);
		glTexSubImage2D(GL_TEXTURE_2D, 0, last_x, last_y, m_glypSlot->bitmap.width, m_glypSlot->bitmap.rows, GL_RED,
			GL_UNSIGNED_BYTE, m_glypSlot->bitmap.buffer);
		//std::printf("last_x=%i last_y=%i\n", last_x, last_y);
		last_x += m_glypSlot->bitmap.width;
		
		/*m_charInfo[i].ax = m_glypSlot->advance.x >> 6;
		m_charInfo[i].ay = m_glypSlot->advance.y >> 6;*/

		m_charInfo[i].ax = m_glypSlot->advance.x >> 6;
		m_charInfo[i].ay = m_glypSlot->advance.y >> 6;
		//printf("ax=%f ay=%f\n", m_charInfo[i].ax, m_charInfo[i].ay);

		m_charInfo[i].bw = m_glypSlot->bitmap.width;
		m_charInfo[i].bh = m_glypSlot->bitmap.rows;

		m_charInfo[i].bl = m_glypSlot->bitmap_left;
		m_charInfo[i].bt = m_glypSlot->bitmap_top;

		m_charInfo[i].tx = (float)last_x;
		m_charInfo[i].ty = (float)last_y;

	}


	//for (int i=32;i<128;i++){
	//	if (FT_Load_Char(m_face, i, FT_LOAD_RENDER)){std::cout << "Failed To loadchar" << i << std::endl;}
	//	//if (FT_Load_Char(m_face, i, FT_LOAD_MONOCHROME)){std::cout << "Failed To loadchar" << i << std::endl;}
	//	//std::printf("char %c size (%i,%i)\n",i, m_glypSlot->bitmap.width, m_glypSlot->bitmap.rows);
	//	//tmp =last_x, +m_glypSlot->bitmap.width+1;
	//	//std::cout << tmp << std::endl;

	//	

	//	if (last_x>= 512){
	//		last_x=0;
	//		last_y+=24;
	//	}
	//	bool reversedLetter =true;
	//	if (reversedLetter){
	//	unsigned char *reversedBitmap = new unsigned char[m_glypSlot->bitmap.width* m_glypSlot->bitmap.rows];
	//	//printf("m_glypSlot->bitmap.rows=%i\n", m_glypSlot->bitmap.rows);
	//	//printf("bitmap Size = %i\n",m_glypSlot->bitmap.width* m_glypSlot->bitmap.rows);
	//	for (int h=0;h<m_glypSlot->bitmap.rows;h++){
	//		//printf("While h=%i",h);
	//		for (int w=0;w<m_glypSlot->bitmap.width;w++){
	//			reversedBitmap[((m_glypSlot->bitmap.rows-h-1)*m_glypSlot->bitmap.width)+w] = m_glypSlot->bitmap.buffer[h*m_glypSlot->bitmap.width+w];
	//		}
	//	}
	//	
	//	//unsigned int bitmapSize = m_glypSlot->bitmap.
	//	//printf("bitmap(width=%i rows=%i npix=%i pixmode=%i)\n",m_glypSlot->bitmap.width, m_glypSlot->bitmap.rows,m_glypSlot->bitmap.width* m_glypSlot->bitmap.rows, m_glypSlot->bitmap.pixel_mode);
	//	
	//	glTexSubImage2D(GL_TEXTURE_2D, 0, last_x, last_y, m_glypSlot->bitmap.width, m_glypSlot->bitmap.rows, GL_RED,
	//		GL_UNSIGNED_BYTE,reversedBitmap);
	//	delete[] reversedBitmap;
	//	}
	//	else{
	//	glTexSubImage2D(GL_TEXTURE_2D, 0, last_x, last_y, m_glypSlot->bitmap.width, m_glypSlot->bitmap.rows, GL_RED,
	//	GL_UNSIGNED_BYTE, m_glypSlot->bitmap.buffer);
	//	}
	//	//std::printf("last_x=%i last_y=%i\n", last_x, last_y);
	//	last_x += m_glypSlot->bitmap.width;
	//	
	//	/*m_charInfo[i].ax = m_glypSlot->advance.x >> 6;
	//	m_charInfo[i].ay = m_glypSlot->advance.y >> 6;*/

	//	m_charInfo[i].ax = m_glypSlot->advance.x >> 6;
	//	m_charInfo[i].ay = m_glypSlot->advance.y >> 6;
	//	//printf("ax=%f ay=%f\n", m_charInfo[i].ax, m_charInfo[i].ay);

	//	m_charInfo[i].bw = m_glypSlot->bitmap.width;
	//	m_charInfo[i].bh = m_glypSlot->bitmap.rows;

	//	m_charInfo[i].bl = m_glypSlot->bitmap_left;
	//	m_charInfo[i].bt = m_glypSlot->bitmap_top;

	//	m_charInfo[i].tx = (float)last_x/last_w;

	//}
	//std::cout << "last x" << last_x << std::endl;
	printf("m_width=%i m_height=%i\n", m_width, m_height);
}

std::array<struct character_info, 128>const& FontAtlas::getCharInfo() const{
	return m_charInfo;
}

int FontAtlas::getAtlasWidth() const{
	return m_width;
}

int FontAtlas::getAtlasHeight() const{
	return m_height;
}

GLuint FontAtlas::getTexID() const{
	return m_texID;
}

float FontAtlas::getATextWidth(std::string const& text){
	float size = 0.0;
	for (unsigned int i=0;i<text.length();i++){
		//size +=m_charInfo[text[i]].bw+(m_charInfo[text[i]].ax-m_charInfo[text[i]].bt);
		size += m_charInfo[text[i]].ax;
		//printf("%i \t%c\t %f\n", text[i], text[i], size);
	}
	//printf("size=%f\n",size);
	return size;
}


float FontAtlas::getATextHeight(std::string const& text){
	float size = 0;
	int nr = 1;
	for (unsigned int i=0;i<text.length();i++){
		if (text[i]=='\n'){
			nr+=1;
		}
		size = std::max(size, m_charInfo[text[i]].bh);
	}
	return size*nr;
}

int FontAtlas::getFontHeight() const{
	return m_font_height;
}

///*void FontAtlas::renderText(const char *text, float x, float y, float sx, float sy, glm::mat4 &projection, glm::mat4 &modelview){
//	//Warning
//	struct point {
//    GLfloat x;
//    GLfloat y;
//    GLfloat s;
//    GLfloat t;
//	} ;
//	/*int tmp = 6*std::strlen(text);
//	int const coords_length = tmp;*/
//	//int coord_length = 6*std::strlen(text);
//	point *coords = new point[6*std::strlen(text)];
//	//std::vector<point> coords(6*std::strlen(text));
//	//glm::vec4 coords[6*std::strlen(text)];
//	
//  int n = 0;
//
//  for(const char *p = text; *p; p++) { 
//	  float x2 =  x + m_charInfo[*p].bl * sx;
//    float y2 = -y -  m_charInfo[*p].bt * sy;
//    float w = m_charInfo[*p].bw * sx;
//    float h = m_charInfo[*p].bh * sy;
//
//    /* Advance the cursor to the start of the next character */
//    x += m_charInfo[*p].ax * sx;
//    y += m_charInfo[*p].ay * sy;
//
//    /* Skip glyphs that have no pixels */
//    if(!w || !h)
//      continue;
//
//    coords[n++] = (point){x2,     -y2    , c[*p].tx,                                            0};
//    coords[n++] = (point){x2 + w, -y2    , c[*p].tx + c[*p].bw / atlas_width,   0};
//    coords[n++] = (point){x2,     -y2 - h, c[*p].tx,                                          c[*p].bh / atlas_height}; //remember: each glyph occupies a different amount of vertical space
//    coords[n++] = (point){x2 + w, -y2    , c[*p].tx + c[*p].bw / atlas_width,   0};
//    coords[n++] = (point){x2,     -y2 - h, c[*p].tx,                                          c[*p].bh / atlas_height};
//    coords[n++] = (point){x2 + w, -y2 - h, c[*p].tx + c[*p].bw / atlas_width, c[*p].bh / atlas_height};
//  }
//
//  glBufferData(GL_ARRAY_BUFFER, sizeof coords, &coords, GL_DYNAMIC_DRAW);
//  glDrawArrays(GL_TRIANGLES, 0, n);
//
//  delete[] coords;
//}

/*bool FontAtlas::init(){
	
	return false;
}*/


FontAtlas::~FontAtlas()
{
}
