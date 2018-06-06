#pragma once

#include "..\Core\Entity.h"

#include "..\Rendering\Mesh.h"
#include "..\Rendering\Shader.h"

/* Cant Reuse two same Meshes for one MeshRenderer */
class MeshRenderer :public EntityComponent {
public:
	MeshRenderer(Mesh* mesh) {
		m_mesh = mesh;
		m_material = &MAT_OBSIDIAN;

		m_type = COMP_MESH_RENDERER;
	}
	MeshRenderer(Mesh* mesh, Material *mat) {
		m_mesh = mesh;
		m_material = mat;

		m_type = COMP_MESH_RENDERER;
	}
	~MeshRenderer() {
		if (m_mesh != NULL) {
			delete(m_mesh);
			m_mesh = NULL;
		}
	}


	void Render(Shader *shader) {
		shader->Bind();
		shader->UpdateUniforms(m_parent->GetTransform(), m_material);
		m_mesh->Draw();
		m_material->Texture->Unbind();
	}

	void SetMesh(Mesh* mesh) {
		m_mesh = mesh;
	}
	void SetMaterial(Material *mat) {
		m_material = mat;
	}
private:
	Mesh *m_mesh;
	Material *m_material;
};