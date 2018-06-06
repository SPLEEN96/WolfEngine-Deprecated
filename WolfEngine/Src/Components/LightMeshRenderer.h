#pragma once

#include "..\Core\Entity.h"
#include "..\Core\Time.h"

#include "..\Rendering\Mesh.h"
#include "..\Rendering\Shader.h"
#include "..\Rendering\ForwardAmbient.h"

#include "Lights\BaseLight.h"

#include "..\Rendering\GeometryData.h"

/* Can't Reuse two same Meshes for one LightMeshRenderer */
class LightMeshRenderer :public EntityComponent {
public:
	LightMeshRenderer(BaseLight *light) {
		m_mesh = new Mesh();
		m_mesh->GenData(TRIANGLE_DATA, 6, TRIANGLE_INDICES, 6);
		m_material = NULL;

		m_light = light;
		m_type = COMP_LMESH_RENDERER;
	}
	~LightMeshRenderer() {
		delete m_material;
		delete m_mesh;
	}
	virtual void Update(float dTime) {
		if (m_material)
			delete(m_material);
		m_material = new Material(m_light->GetColor(), m_light->GetColor(), m_light->GetColor(), 0.f);
		
		m_parent->GetTransform()->Rotate(180.f/**Time::GetTime()*/, Vector3f(0.f, 1.f, 0.f));
		m_parent->GetTransform()->Scale(Vector3f(0.4f));
	}

	void Render(Shader *shader) {
		ForwardAmbient::GetInstance().SetAmbient(0.4f);
		ForwardAmbient::GetInstance().Bind();
		ForwardAmbient::GetInstance().UpdateUniforms(m_parent->GetTransform(), m_material);
		m_mesh->Draw();
	}
private:
	Mesh *m_mesh;
	Material *m_material;
	BaseLight *m_light;
};