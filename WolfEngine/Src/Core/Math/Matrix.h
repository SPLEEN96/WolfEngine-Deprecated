#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "..\ResourceManagement\DataTypes\Typedefs.h"


/* Layer of abstraction between GLM and the rest of the code. */
/* (Eventually I won't use GLM for my maths) */
/* It is a temporary struct. */
struct Matrix4f {
public:
	Matrix4f() {
		m_glm_data = glm::mat4();
		CopyGlmToMat();
	}
	Matrix4f(const Matrix4f &rhs) {
		m_glm_data = rhs.m_glm_data;
		CopyGlmToMat();
	}
	Matrix4f(const glm::mat4 &rhs) {
		m_glm_data = rhs;
		CopyGlmToMat();
	}
	//==================== OPERATORS =========================
	const Matrix4f& operator=(const Matrix4f &rhs) {
		m_glm_data = rhs.m_glm_data;
		CopyGlmToMat();
		return *this;
	}
	const bool operator==(const Matrix4f &rhs) {
		for (u8 i = 0; i < 4; i++) { /* i is row */
			for (u8 j = 0; j < 4; j++) { /* j is column */
				if (m_mat_data[i][j] != rhs.m_mat_data[i][j]) {
					return false;
				}
			}
		}
		return true;
	}
	const bool operator!=(const Matrix4f &rhs) {
		return !(*this == rhs);
	}

	//======================== GETTERS/SETTERS ==========================
	const float* GetData() const {
		return m_mat_data[0];
	}

	glm::mat4 GetGlm() const {
		return m_glm_data;
	}
	void SetGlm(const glm::mat4 &rhs) {
		m_glm_data = rhs;
		CopyGlmToMat();
	}

private:
	glm::mat4 m_glm_data;
	float m_mat_data[4][4];

	void CopyGlmToMat() {
		float *tmp_mat = glm::value_ptr(m_glm_data);

		for (u8 i = 0; i < 4; i++) { /* i is row */
			for (u8 j = 0; j < 4; j++) { /* j is column */
				m_mat_data[i][j] = tmp_mat[(i * 4 + j)];
			}
		}
	}
};