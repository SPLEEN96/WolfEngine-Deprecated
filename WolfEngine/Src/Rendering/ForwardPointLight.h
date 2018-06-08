#pragma once
#include "Shader.h"

#include "..\Components\Lights\BaseLight.h"

/* Temporary until the Shader class becomes generic. */
class ForwardPointLight :public Shader {
private:
	ForwardPointLight() : Shader() {
		Init("ForwardPointLight");
	}
public:
	static ForwardPointLight& GetInstance() {
		static ForwardPointLight shader_instance;
		return shader_instance;
	}

	void SetCamera(Camera* camera) {
		m_camera = camera;
	}
	void SetLight(BaseLight *light, const float &range, const float &kConstant, const float &kLinear, const float &kQuadratic) {
		m_light = light;
		m_range = range;
		m_kConstant = kConstant;
		m_kLinear = kLinear;
		m_kQuadratic = kQuadratic;
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

		SetFloat("pointlight.range", m_range);
		SetVector3f("pointlight.position", 1, m_light->GetPosition());
		SetFloat("pointlight.kConstant", m_kConstant);
		SetFloat("pointlight.kLinear", m_kLinear);
		SetFloat("pointlight.kQuadratic", m_kQuadratic);
		
   		SetVector3f("pointlight.diffuse", 1, m_light->GetColor()*m_light->GetIntensity()); /* Multiplied by Intensity to attenuate the light */
		SetVector3f("pointlight.specular", 1, m_light->GetIntensity());

		SetVector3f("view_pos", 1, m_camera->GetPosition());

		Matrix4f model = transform->GetTransformMatrix();
		Matrix4f view = m_camera->GetViewMatrix();
		Matrix4f projection = m_camera->GetProjectionMatrix();

		SetCoordinates(model, view, projection);
	}
private:
	BaseLight *m_light;
	float m_range;
	float m_kConstant, m_kLinear, m_kQuadratic;
	Camera *m_camera;
};