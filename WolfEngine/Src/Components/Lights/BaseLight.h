#pragma once

#include "..\Core\Entity.h"

#include "..\Core\Math\Vector.h"

enum LIGHT_TYPES {
	LIGHT_BASIC,
	LIGHT_DIRECTIONAL,
	LIGHT_POINT
};

static const char* LIGHT_TYPES_STR[] = {
	"Basic-Light",
	"Directional-Light",
	"Point-Light"
};

class BaseLight :public EntityComponent {
protected:
	BaseLight() {}
	BaseLight(const Vector3f &color, const float &intensity) { /* Only the derived classes need this constructor */
		m_color = color;
		m_intensity = intensity;

		m_type = COMP_LIGHT;
		m_light_type = LIGHT_BASIC;
	}
public:
	virtual ~BaseLight() {}

	LIGHT_TYPES GetLightType() {
		return m_light_type;
	}
	const char* GetLightTypeStr() {
		return LIGHT_TYPES_STR[m_light_type];
	}

	Vector3f GetColor(){
		return m_color;
	}
    void SetColor(const Vector3f &color) {
		m_color = color;
	}

	float GetIntensity() {
		return m_intensity;
	}
	void SetIntensity(const float &intensity) {
		m_intensity = intensity;
	}

	Vector3f GetPosition() {
		return m_parent->GetTransform()->GetPosition();
	}

	virtual Shader* GetShader() {
		return m_shader;
	}

	Transform* GetTransform() {
		return m_parent->GetTransform();
	}

protected:
	LIGHT_TYPES m_light_type;
	Vector3f m_color;
	float m_intensity;

	Shader *m_shader;
};