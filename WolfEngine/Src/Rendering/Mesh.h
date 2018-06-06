#pragma once 
#include <map>

#include "..\Core\ResourceManagement\DataTypes\MeshData.h"

#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"
#include "..\Core\Logger.h"

/* Only one instance per EntityRenderer */
class Mesh {
public:
	Mesh(){
		m_data = new MeshData();
	}
	Mesh(const MeshData &data) {
		m_data = new MeshData();
		m_data->VAO(data.VAO());
		m_data->VBO(data.VBO());
		m_data->EBO(data.EBO());
		m_data->Length(data.Length());
	}
	~Mesh() {
		if (m_data != NULL) {
			delete(m_data);
			m_data = NULL;
		}
	}


	void GenData(Vertex vertices[], u32 vertices_len, u32 indices[], u32 indices_len, u32 normalize = GL_FALSE) {
		m_data->Length(indices_len);
		glBindVertexArray(m_data->VAO());

		glBindBuffer(GL_ARRAY_BUFFER, m_data->VBO());
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices_len, &vertices[0], GL_STATIC_DRAW);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data->EBO());
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32)*indices_len, &indices[0], GL_STATIC_DRAW);

		/* coordinates */
		glVertexAttribPointer(0, 3, GL_FLOAT, normalize, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(0);
		/* normal vecs */
		glVertexAttribPointer(1, 3, GL_FLOAT, normalize, sizeof(Vertex), (void*)(offsetof(Vertex,Normal)));
		glEnableVertexAttribArray(1);
		/* tex coordinates */
		glVertexAttribPointer(2, 2, GL_FLOAT, normalize, sizeof(Vertex), (void*)(offsetof(Vertex, TexCoordinates)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	void Draw() {
	   	glBindVertexArray(m_data->VAO());
	    glDrawElements(GL_TRIANGLES, m_data->Length(), GL_UNSIGNED_INT, 0);
	   	glBindVertexArray(0);
	}

	MeshData* GetData() const{
		return m_data;
	}

private:
	MeshData *m_data;
};