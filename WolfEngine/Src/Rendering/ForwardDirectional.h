#pragma once
#include "Shader.h"

#include "..\Components\Lights\BaseLight.h"

/* Temporary until the Shader class becomes generic. */
class ForwardDirectional:public Shader {
private:
	ForwardDirectional() : Shader() {
		Init("ForwardDirectional");

		m_lightdir = Vector3f(0.f);
	}
public:
	static ForwardDirectional& GetInstance() {
		static ForwardDirectional shader_instance;
		return shader_instance;
	}

	void SetCamera(Camera* camera) {
		m_camera = camera;
	}
	void SetLight(BaseLight *light, Vector3f lightdir) {
		m_light = light;
		m_lightdir = lightdir;
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

		SetVector3f("material.ambient", 1, material->Ambient);
		SetVector3f("material.diffuse", 1, material->Diffuse);
		SetVector3f("material.specular", 1, material->Specular);
		SetFloat("material.shininess", material->Shininess);

		SetVector3f("dirlight.direction", 1, m_lightdir);
		SetVector3f("dirlight.diffuse", 1, m_light->GetColor()*m_light->GetIntensity()); /* Multiplied by Intensity to attenuate the light */
		SetVector3f("dirlight.specular", 1, m_light->GetIntensity());

		SetVector3f("view_pos", 1, m_camera->GetPosition());

		Matrix4f model = transform->GetTransformMatrix();
		Matrix4f view = m_camera->GetViewMatrix();
		Matrix4f projection = m_camera->GetProjectionMatrix();

		SetCoordinates(model, view, projection);
	}
private:
	BaseLight *m_light;
	Vector3f m_lightdir;
	Camera *m_camera;
};