#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Vector.h"
#include "Matrix.h"

namespace MLib {
	/* Convert an Angle in Degree to an Agle in Radian */
	static float Radians(const float &angle_in_degree) {
		return (angle_in_degree / 57.295779513f);
	}

	/* ==================================== VECTOR OPERATIONS ====================================*/
	
	/* Return the length of a vector */
	template <typename T, u8 N>
	static T Length(const Vector<T,N>& vec) {
		T length = 0.f;
		for (u8 i = 0; i < N; i++) {
			length += pow(vec[i], 2);
		}
		return sqrt(length);
	}

	/* Return the distance between two vectors */
	template <typename T, u8 N>
	static T Distance(const Vector<T,N>& lhs, const Vector<T,N>& rhs) {
		T distance = 0.f;
		for (u8 i = 0; i < N; i++) {
			distance += pow(lhs[i] - rhs[i], 2);
		}
		return sqrt(distance);
	}

	/* Return a direction vector (with a length of 1) */
	template <typename T, u8 N>
	static Vector<T,N> Normalize(const Vector<T,N>& vec) {
		Vector<T,N> normalized_vec;
		for (u8 i = 0; i < N; i++) {
			normalized_vec[i] = vec[i] / Length(vec);
		}
		return normalized_vec;
	}


	/* Can be used to find a third vector perpendicular to two vectors(lhs and rhs) */
	static Vector3f CrossProduct(const Vector3f& lhs, const Vector3f& rhs) {
		/* (Ax)   (Bx)   (Ay * Bz - Az * By) */
		/* (Ay) X (By) = (Az * Bx - Ax * Bz) */
		/* (Az)   (Bz)   (Ax * By - Ay * Bx) */

		float X = (lhs.Y() * rhs.Z()) - (lhs.Z() * rhs.Y());
		float Y = (lhs.Z() * rhs.X()) - (lhs.X() * rhs.Z());
		float Z = (lhs.X() * rhs.Y()) - (lhs.Y() * rhs.X());

		return Vector3f(X, Y, Z);
	}

	/* =============================== TRANSFORMATIONS ==================================== */

	static Matrix4f Translate(const Matrix4f &matrix, const Vector3f &translatation_axes) {
		glm::vec3 glm_translation = glm::vec3(translatation_axes.X(), translatation_axes.Y(), translatation_axes.Z());
		return Matrix4f(glm::translate(matrix.GetGlm(), glm_translation));
	}

	static Matrix4f Scale(const Matrix4f &matrix, const Vector3f &scale_axes) {
		glm::vec3 glm_scale = glm::vec3(scale_axes.X(), scale_axes.Y(), scale_axes.Z());
		return Matrix4f(glm::scale(matrix.GetGlm(), glm_scale));
	}

	static Matrix4f Rotate(const Matrix4f &matrix, const float &angle, const Vector3f &rotation_axes) {
		glm::vec3 glm_rotation = glm::vec3(rotation_axes.X(), rotation_axes.Y(), rotation_axes.Z());
		return Matrix4f(glm::rotate(matrix.GetGlm(), angle, glm_rotation));
	}


	/* ========================================= OPENGL COORDINATES SYSTEM ==================================== */

	static Matrix4f Perspective(const float &fov, const float &aspect_ratio, const float &znear, const float &zfar) {
		return Matrix4f(glm::perspective(fov, aspect_ratio, znear, zfar));
	}

	static Matrix4f LookAt(const Vector3f &position, const Vector3f &target, const Vector3f &up) {
		glm::vec3 glm_pos = glm::vec3(position.X(), position.Y(), position.Z());
		glm::vec3 glm_target = glm::vec3(target.X(), target.Y(), target.Z());
		glm::vec3 glm_up = glm::vec3(up.X(), up.Y(), up.Z());
		return Matrix4f(glm::lookAt(glm_pos, glm_target, glm_up));
	}
}