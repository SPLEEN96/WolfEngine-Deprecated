#pragma once

#include "..\Core\ResourceManagement\RenderingEngineData.h"

#include "..\Core\Entity.h"

#include "..\Core\Math\MathLib.h"

/* There is no mouse movement because it would be too tedious */
/* to use the UI in the rendering engine. */
class Camera :public EntityComponent {
private: Camera() {}
public:
	Camera(RenderingEngineData* rdata, Entity* parent,
		const float& screen_width, const float& screen_height, const float &fov = 45.f, 
		const float &zNear = 0.01f, const float &zFar = 300.f, 
		Vector3f target = Vector3f(0.f, 0.f, 1.f)) {
		m_type = COMP_CAMERA;
		m_parent = parent;

		m_world_up = Vector3f(0.f, 1.f, 0.f);

		Vector3f direction = GetPosition() - target;
		m_z_axis = MLib::Normalize(direction); /* Don't need the length of the vector */
	
		
		m_x_axis = MLib::CrossProduct(m_world_up, m_z_axis);
		m_x_axis = MLib::Normalize(m_x_axis);
		

		m_y_axis = MLib::CrossProduct(m_z_axis, m_x_axis);
		m_y_axis = MLib::Normalize(m_y_axis);

		m_front = GetPosition() - m_z_axis;

		m_screen_ratio = Vector3f(screen_width, screen_height, 1.f);
		m_projection = MLib::Perspective(fov, (m_screen_ratio.X() / m_screen_ratio.Y()), zNear, zFar);

		rdata->LinkCamera(this);
	}

	~Camera() {}


	void Update(float dTime) {
		m_front = GetPosition() - m_z_axis;
	}

	Vector3f GetPosition() const {
		return m_parent->GetTransform()->GetPosition();
	}
	Vector3f GetFront() const {
		return m_front;
	}
	Matrix4f GetViewMatrix() const {
		Matrix4f view_matrix = MLib::LookAt(GetPosition(), m_front, m_y_axis);
		return view_matrix;
	}
	Matrix4f GetProjectionMatrix() const {
		return m_projection;
	}

	Vector3f GetScreenRatio() {
		return m_screen_ratio;
	}

	Vector3f GetZ() const {
		return m_z_axis;
	}
	Vector3f GetX() const {
		return m_x_axis;
	}
	Vector3f GetY() const {
		return m_y_axis;
	}


private:
	Vector3f m_screen_ratio;
	Matrix4f m_projection;
	Vector3f m_front;
	Vector3f m_world_up;
	Vector3f m_z_axis, m_x_axis, m_y_axis;
};