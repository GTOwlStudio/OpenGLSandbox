#include "Mesh.h"

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset)((char*)NULL + (offset))
#endif

/*
Mesh::Mesh(std::string filename)
{
	loadFromFile(filename);
}*/

Mesh::Mesh(std::string filename) : m_vao(0), m_vbo(0),
m_shader("shaders/phong.vert", "shaders/phong.frag"),
m_verticesBytesSize(0), m_indicesBytesSize(0), m_normalsBytesSize(0)
{
	loadFromFile(filename);
	for (size_t i = 0; i < m_vertices.size(); i++)
	{
		m_normals.push_back(glm::vec3());
	}
	printf("reserve %i\n", m_normals.size());
	computeNormals();
	m_verticesBytesSize = sizeof(glm::vec3)*m_vertices.size();
	m_indicesBytesSize = sizeof(unsigned int)*m_indices.size();
	m_normalsBytesSize = sizeof(glm::vec3)*m_normals.size();
//	m_normals[0] = glm::vec3(0.666f, 0.666f, 0.666f);
}



Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_ibo);
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}

void Mesh::load() {
	
	if (glIsVertexArray(m_vao)) { glDeleteVertexArrays(1, &m_vao); }

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	
	if (glIsBuffer(m_ibo)) { glDeleteBuffers(1, &m_ibo); }

	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesBytesSize, m_indices.data(), GL_STATIC_DRAW);

	if (glIsBuffer(m_vbo)) { glDeleteBuffers(1, &m_vbo); }
	
	Util::conceptor("%i %i\n", m_verticesBytesSize,m_verticesBytesSize + m_normalsBytesSize);
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	Util::conceptor("vboId %i\n", m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_verticesBytesSize + m_normalsBytesSize, m_vertices.data(), GL_STATIC_DRAW);
	if (m_normalsBytesSize!=0) {
		glBufferSubData(GL_ARRAY_BUFFER, m_verticesBytesSize, m_normalsBytesSize, m_normals.data());
	}
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	if (m_normalsBytesSize!=0) {
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_verticesBytesSize));
		//glVertexAttribDivisor(3, 3);
		glEnableVertexAttribArray(3);
	}

	glBindVertexArray(0);

	m_shader.load();
}

void Mesh::render(glm::mat4 & matrix)
{

	glUseProgram(m_shader.getProgramID());

	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "matrix"), 1, GL_FALSE, glm::value_ptr(matrix));

		glBindVertexArray(m_vao);
		glDrawElements(GL_TRIANGLES,m_indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

	glUseProgram(0);
}

void Mesh::render(glm::mat4 & matrix, glm::mat4 & world)
{

	glUseProgram(m_shader.getProgramID());

	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "matrix"), 1, GL_FALSE, glm::value_ptr(matrix));
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "world"), 1, GL_FALSE, glm::value_ptr(world));

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glUseProgram(0);

}


void Mesh::loadFromFile(std::string filename)
{

	FILE* file;
	fopen_s(&file, filename.c_str(), "r");
	if (file==NULL) {
		printf("Impossible to open the file !\n");
		fclose(file);
		return;
	}
	bool isNormal = false;
	while (1) {
		char lineHeader[128];

		int res = fscanf_s(file, "%s", lineHeader, sizeof(lineHeader));
		if (res==EOF) {
			break; //EOF end of File
		}
		if (strcmp(lineHeader, "v")==0) {
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			m_vertices.push_back(vertex);
		}
		if (strcmp(lineHeader, "vn")==0) {
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			//m_normals.push_back(normal);
			isNormal = true;
		}
		if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3];
			if (isNormal) {
				//std::string normal1, normal2, normal3;
				unsigned int normalIndex;
				int matches = fscanf_s(file, "%d//%d %d//%d %d//%d", &vertexIndex[0],&normalIndex, &vertexIndex[1], &normalIndex, &vertexIndex[2], &normalIndex);
			}
			else {
				
				int matches = fscanf_s(file, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
				if (matches != 3) {
					Util::error("File can't be read by our simple parser");
					return;
				}
			}
			m_indices.push_back(vertexIndex[0]);
			m_indices.push_back(vertexIndex[1]);
			m_indices.push_back(vertexIndex[2]);
		}
	}

	printf("debug %i %i\n", m_vertices.size(), m_indices.size());
	for (unsigned int i = 0; i < m_indices.size();i++) {
		m_indices[i] = m_indices[i] - 1;
		//printf("%i->%i\n", i, m_indices[i]);
	}
	fclose(file);

}

void Mesh::computeNormals() {

	for (unsigned int i = 0; i < m_indices.size(); i += 3) {
		unsigned int Index0 = m_indices[i];
		unsigned int Index1 = m_indices[i + 1];
		unsigned int Index2 = m_indices[i + 2];

		glm::vec3 v1 = m_vertices[Index1] - m_vertices[Index0];
		glm::vec3 v2 = m_vertices[Index2] - m_vertices[Index0];
		glm::vec3 Normal = glm::cross(v1, v2);
		Normal = glm::normalize(Normal);

		m_normals[Index0] += Normal;
		m_normals[Index1] += Normal;
		m_normals[Index2] += Normal;

		/*m_normals.push_back(Normal);
		m_normals.push_back(Normal);
		m_normals.push_back(Normal);*/

	}
		for (unsigned int i = 0; i < m_vertices.size(); i++)
		{
			m_normals[i] = glm::normalize(m_normals[i]);
		}
		

		printf("Normals Computed %i\n", m_normals.size());
}