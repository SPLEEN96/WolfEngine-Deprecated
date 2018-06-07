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

class PointLight;
struct PointLightConstantValues {
	friend class PointLight;
private:
	/* Constants used calculate the Inverse Square Law in the shaders */
	/* Values taken from wiki.ogre3d.org/-Point+Light+Attenuation */
	const Vector3f kCONST[6]{
		Vector3f(1.0f, 0.7f, 1.8f),
		Vector3f(1.0f, 0.22f, 0.20f),
		Vector3f(1.0f, 0.14f, 0.07f),
		Vector3f(1.0f, 0.09f, 0.032f),
		Vector3f(1.0f, 0.045f, 0.0075f),
		Vector3f(1.0f, 0.007f, 0.0002f)
	};
	/* Possible range values for a PointLight (used in the gui) */
	const u16 RANGE[6]{
		7,
		20,
		32,
		50,
		100,
		600
	};
};





class PointLight :public BaseLight {
private:
	PointLight() {}
public:
	PointLight(RenderingEngineData* rdata, Vector3f color, float intensity = 1.f, const POINT_RANGE &range = RANGE_7)
		:BaseLight(color, intensity) {
		m_light_type = LIGHT_POINT;

		m_range = m_values.RANGE[range];

		m_kConstant = m_values.kCONST[range].X();
		m_kLinear = m_values.kCONST[range].Y();
		m_kQuadratic = m_values.kCONST[range].Z();
	
		m_shader = &ForwardPointLight::GetInstance();
		
		rdata->LinkLight(this);
	}

	void SetRange(const POINT_RANGE &range) {
		m_range = m_values.RANGE[range];
		m_kConstant = m_values.kCONST[range].X();
		m_kLinear = m_values.kCONST[range].Y();
		m_kQuadratic = m_values.kCONST[range].Z();
	}

	Shader* GetShader() {
		((ForwardPointLight*)m_shader)->SetLight(this, m_range, m_kConstant, m_kLinear, m_kQuadratic);
		return m_shader;
	}

private:
	float m_range;
	float m_kConstant, m_kLinear, m_kQuadratic;
	PointLightConstantValues m_values;
};