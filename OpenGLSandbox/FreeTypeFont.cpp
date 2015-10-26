#include "FreeTypeFont.h"

inline int next_p2(int n){int res = 1; while(res < n)res <<= 1; return res;} 

FreeTypeFont::FreeTypeFont() : m_vao(0), m_vbo(0)
{

}
bool FreeTypeFont::loadFont(std::string file, int pxSize){
	bool bError = FT_Init_FreeType(&ftLib); 
    
   bError = FT_New_Face(ftLib, file.c_str(), 0, &ftFace); 
   if(bError)return false; 
   FT_Set_Pixel_Sizes(ftFace, pxSize, pxSize); 
   m_loadedPixelSize = pxSize; 

   glGenVertexArrays(1, &m_vao); 
   glBindVertexArray(m_vao); 
   
   
   glGenBuffers(1, &m_vbo); //vboData.createVBO(); 
   glBindBuffer(GL_ARRAY_BUFFER, m_vbo);  // vboData.bindVBO(); 
 


   for(int i=0;i<128;i++){
	   createChar(i); 
   }
   m_loaded = true; 

   FT_Done_Face(ftFace); 
   FT_Done_FreeType(ftLib); 
    
   //vboData.uploadDataToGPU(GL_STATIC_DRAW); 
   //Quad texture
   glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), charTexCoord, GL_STATIC_DRAW);

   glEnableVertexAttribArray(0); 
   glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2)*2, 0); 
   glEnableVertexAttribArray(1); 
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2)*2, (void*)(sizeof(glm::vec2))); 
   return true; 
}

void FreeTypeFont::createChar(int index)
{
	FT_Load_Glyph(ftFace, FT_Get_Char_Index(ftFace, index), FT_LOAD_DEFAULT); 

   FT_Render_Glyph(ftFace->glyph, FT_RENDER_MODE_NORMAL); 
   FT_Bitmap* pBitmap = &ftFace->glyph->bitmap; 

   int iW = pBitmap->width, iH = pBitmap->rows; 
   int iTW = next_p2(iW), iTH = next_p2(iH); 

   GLubyte* bData = new GLubyte[iTW*iTH]; 
   // Copy glyph data and add dark pixels elsewhere
   for(int ch=0; ch<iTH;ch++){
	   for(int cw=0; cw<iTW;cw++){
		bData[ch*iTW+cw] = (ch >= iH || cw >= iW) ? 0 : pBitmap->buffer[(iH-ch-1)*iW+cw]; 
	   }
	   }
   // And create a texture from it

   charTextures[index].createFromData(bData, iTW, iTH, 16, GL_DEPTH_COMPONENT/*, false*/); 
   charTextures[index].setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR); 

   charTextures[index].setSamplerParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
   charTextures[index].setSamplerParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
   charTextures[index].setSamplerParameter(GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE); 

   // Calculate glyph data
   advX[index] = ftFace->glyph->advance.x>>6; 
   bearingX[index] = ftFace->glyph->metrics.horiBearingX>>6; 
   charWidth[index] = ftFace->glyph->metrics.width>>6; 

   advY[index] = (ftFace->glyph->metrics.height - ftFace->glyph->metrics.horiBearingY)>>6; 
   bearingY[index] = ftFace->glyph->metrics.horiBearingY>>6; 
   charHeight[index] = ftFace->glyph->metrics.height>>6; 

   m_newLine = max(m_newLine, int(ftFace->glyph->metrics.height>>6)); 

   // Rendering data, texture coordinates are always the same, so now we waste a little memory
   glm::vec2 vQuad[] = 
   { 
      glm::vec2(0.0f, float(-advY[index]+iTH)), 
      glm::vec2(0.0f, float(-advY[index])), 
      glm::vec2(float(iTW), float(-advY[index]+iTH)), 
      glm::vec2(float(iTW), float(-advY[index])) 
   }; 
   glm::vec2 vTexQuad[] = {glm::vec2(0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 0.0f)};

   // Add this char to VBO
   for(int i=0;i<4;i++) 
   { 
      vboData.addData(&vQuad[i], sizeof(glm::vec2)); 
      vboData.addData(&vTexQuad[i], sizeof(glm::vec2)); 
   } 
   delete[] bData; 
}



