#pragma once
#include <glad\glad.h>

#include "Shader.h"

/* Temporary until the Shader class becomes generic. */
class ForwardAmbient :public Shader {
private:
	ForwardAmbient() : Shader() {
		Init("ForwardAmbient");

		m_ambient = Vector3f(0.33f);
	}
public:
	static ForwardAmbient& GetInstance() {
		static ForwardAmbient shader_instance;
		return shader_instance;
	}

	void SetCamera(Camera* camera) {
		m_camera = camera;
	}
	void SetAmbient(Vector3f ambient) {
		m_ambient = ambient;
	}


	virtual void UpdateUniforms(Transform *transform, Material *material) {
		if (material->Texture != NULL) {
			material->Texture->Bind(0);
			SetInt("tex_sampler", 0);
			SetInt("use_tex", 1);
		}
		else {
			SetInt("use_tex", 0);
		}

		SetVector3f("ambient", 1, m_ambient);
		SetVector3f("material.ambient", 1, material->Ambient);

		Matrix4f model = transform->GetTransformMatrix();
		Matrix4f view = m_camera->GetViewMatrix();
		Matrix4f projection = m_camera->GetProjectionMatrix();

		SetCoordinates(model, view, projection);
	}
private:
	Camera *m_camera;
	Vector3f m_ambient;
};