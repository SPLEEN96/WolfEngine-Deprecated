#pragma once

#include "BaseLight.h"

#include "..\Rendering\ForwardPointLight.h"

#include "..\Core\ResourceManagement\RenderingEngineData.h"

enum POINT_RANGE {
	RANGE_7,
	RANGE_20,
	RANGE_32,
	RANGE_50,
	RANGE_100,
	RANGE_600
};
const float POINT_RANGEVAL[]{
	7,
	20,
	32,
	50,
	100,
	600
};
const Vector3f POINT_kCONST[]{
	Vector3f(1.0f, 0.7f, 1.8f),
	Vector3f(1.0f, 0.22f, 0.20f),
	Vector3f(1.0f, 0.14f, 0.07f),
	Vector3f(1.0f, 0.09f, 0.032f),
	Vector3f(1.0f, 0.045f, 0.0075f),
	Vector3f(1.0f, 0.007f, 0.0002f)
};


class PointLight :public BaseLight {
private:
	PointLight() {}
public:
	PointLight(RenderingEngineData* rdata, Vector3f color, float intensity, const POINT_RANGE &range)
		:BaseLight(color, intensity) {
		m_light_type = LIGHT_POINT;

		m_range = POINT_RANGEVAL[range];

		m_kConstant = POINT_kCONST[range].X();
		m_kLinear = POINT_kCONST[range].Y();
		m_kQuadratic = POINT_kCONST[range].Z();
	
		m_shader = &ForwardPointLight::GetInstance();
		
		rdata->LinkLight(this);
	}

	void SetRange(const POINT_RANGE &range) {
		m_range = POINT_RANGEVAL[range];
		m_kConstant = POINT_kCONST[range].X();
		m_kLinear = POINT_kCONST[range].Y();
		m_kQuadratic = POINT_kCONST[range].Z();
	}

	Shader* GetShader() {
		((ForwardPointLight*)m_shader)->SetLight(this, m_range, m_kConstant, m_kLinear, m_kQuadratic);
		return m_shader;
	}

private:
	float m_range;
	float m_kConstant, m_kLinear, m_kQuadratic;
};