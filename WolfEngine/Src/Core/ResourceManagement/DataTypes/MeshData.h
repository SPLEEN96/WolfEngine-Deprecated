#pragma once

#include <glad\glad.h>

#include "..\..\..\Rendering\Texture.h"

struct MeshData {
public:
	MeshData() {
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);
		m_length = 0;
	}
	MeshData(const MeshData &rhs) {
		m_VAO = rhs.m_VAO;
		m_VBO = rhs.m_VBO;
		m_EBO = rhs.m_EBO;

		m_length = rhs.m_length;
	}
	~MeshData() {
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);

		m_VAO = m_VBO = m_EBO = 0;
	}
	const MeshData operator=(const MeshData &rhs) {
		m_VAO = rhs.m_VAO;
		m_VBO = rhs.m_VBO;
		m_EBO = rhs.m_EBO;

		m_length = rhs.m_length;

	   	return *this;
	}

	GLuint VAO() const{
		return m_VAO;
	}
	void VAO(const GLuint &VAO) {
		m_VAO = VAO;
	}

	GLuint VBO() const{
		return m_VBO;
	}
	void VBO(const GLuint &VBO) {
		m_VBO = VBO;
	}

	GLuint EBO() const{
		return m_EBO;
	}
	void EBO(const GLuint &EBO) {
		m_EBO = EBO;
	}

	u32 Length() const{
		return m_length;
	}
	void Length(u32 length) {
		m_length = length;
	}
private:
	GLuint m_VAO, m_VBO, m_EBO;
	u32 m_length;
};