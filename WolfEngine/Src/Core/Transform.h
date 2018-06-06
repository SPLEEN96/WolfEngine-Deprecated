#pragma once

#include "Math\MathLib.h"

class Transform {
public:
	Transform() {
		m_translate = Matrix4f();
		m_scale = Matrix4f();
		m_rotate = Matrix4f();
		m_position = Vector3f();
		m_curr_angle = 0.f;

		m_prev_scale = Matrix4f();
		m_prev_rotate = Matrix4f();
		m_prev_rotate = Matrix4f();
		m_parent = NULL;
	}

	void SetParent(Transform *parent) {
		m_parent = parent;
	}

	/* Called in Entity.Update() */
	void Update() {
		m_prev_translate = m_translate;
		m_prev_rotate = m_translate;
		m_prev_scale = m_scale;
	}

	/* Get the combinaison of the translation,rotation and scale matrix for the shader model matrix */
	Matrix4f GetTransformMatrix() {
		Matrix4f transform_mat = Matrix4f();
		Matrix4f parent_mat = Matrix4f();

		/* To avoid meaningless updates */
		if (m_parent != NULL && m_parent->HasChanged())
			parent_mat = m_parent->GetTransformMatrix();

		transform_mat.SetGlm(parent_mat.GetGlm() * m_translate.GetGlm() * m_rotate.GetGlm() * m_scale.GetGlm());
 		return transform_mat;
	}

	float GetCurrAngle() {
		return m_curr_angle;
	}
	Vector3f GetScale() {
		return Vector3f(m_scale.GetData()[0], m_scale.GetData()[5], m_scale.GetData()[10]);
	}
	Vector3f GetPosition() {
		return m_position;
	}
	
	void SetPosition(const Vector3f &new_pos) {
		Vector3f translate_vec = Vector3f();
		translate_vec.X(new_pos.X() - m_position.X());
		translate_vec.Y(new_pos.Y() - m_position.Y());
		translate_vec.Z(new_pos.Z() - m_position.Z());
		
		m_position = new_pos;
		m_translate = MLib::Translate(m_translate, translate_vec);
	}


	float GetDistanceFrom(const Vector3f &obj_pos) {
		return MLib::Distance(m_position, obj_pos);
	}

	void Translate(const Vector3f &axes) {
		m_translate = Matrix4f();

		m_position = m_position + axes;
		m_translate = MLib::Translate(m_translate, axes);
	}

	void Scale(const Vector3f &axes) {
		m_scale = Matrix4f();
		m_scale = MLib::Scale(m_scale, axes);
	}

	void Rotate(const float &angle, const Vector3f &axes) {
		m_curr_angle = angle;
		m_rotate = Matrix4f();
		m_rotate = MLib::Rotate(m_rotate, angle, axes);
	}

	
private:
	bool HasChanged() {
		if (m_parent != NULL && m_parent->HasChanged())
			return true;

		if (m_translate != m_prev_translate)
			return true;
		if (m_rotate != m_prev_rotate)
			return true;
		if (m_scale != m_prev_scale)
			return true;

		return false;
	}

	Transform *m_parent;
	Matrix4f m_translate, m_scale, m_rotate;
	Matrix4f m_prev_translate, m_prev_scale, m_prev_rotate;
	Vector3f m_position;
	float m_curr_angle;
};