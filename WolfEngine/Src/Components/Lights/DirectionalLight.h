#pragma once

#include "BaseLight.h"

#include "..\Rendering\ForwardDirectional.h"

#include "..\Core\ResourceManagement\RenderingEngineData.h"

class DirectionalLight :public BaseLight {
private:
	DirectionalLight() {
		m_light_type = LIGHT_DIRECTIONAL;

	}
public:
	DirectionalLight(RenderingEngineData* rdata, Vector3f color, float intensity, Vector3f target) 
		:BaseLight(color, intensity) {
		m_light_type = LIGHT_DIRECTIONAL;

		m_target = target;
		m_shader = &ForwardDirectional::GetInstance();

		rdata->LinkLight(this);
	}

	void SetTarget(Vector3f target) {
		m_target = target;
	}
	Vector3f GetDirection() {
		return m_direction;
	}

	void Update(float dTime) {
		m_direction = m_target - GetPosition();
	}

	Shader* GetShader() {
		((ForwardDirectional*)m_shader)->SetLight(this, m_direction);
		return m_shader;
	}

private:
	Vector3f m_direction, m_target;
};