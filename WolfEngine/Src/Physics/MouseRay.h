#pragma once
/* antongerdelan.net/opengl/raycasting.html */

#include "..\Core\Math\Matrix.h"
#include "..\Core\Math\Vector.h"

#include "..\Components\Camera.h"

class MouseHandler;
struct MouseRay {
	friend class MouseHandler;
public:
	MouseRay(Camera* camera) {
		m_camera_handle = camera;
	}

	void Input(const float &x_pos, const float &y_pos) {
		m_projection = m_camera_handle->GetProjectionMatrix();
		m_curr_ray = CalculateMouseRay(x_pos, y_pos);
		m_view = m_camera_handle->GetViewMatrix();
	}

	Vector3f GetCurrentRay() {
		return m_curr_ray;
	}
private:
	Vector3f CalculateMouseRay(const float &x_pos, const float &y_pos) {
		Vector3f normalized_coords = GetNormalizedMouseCoordinates(x_pos, y_pos);
		Vector3f clip_coords = Vector3f(normalized_coords.X(), normalized_coords.Y(), -1);
		Vector3f view_coords = GetViewSpaceMouseCoordinates(clip_coords);
		Vector3f world_ray = GetWorldSpaceMouseCoordinates(view_coords);

		return world_ray;
	}

	Vector3f GetNormalizedMouseCoordinates(const float &x_pos, const float &y_pos) {
		/* Convert coordinates in ViewportSpace (0-screen_width / 0-screen_height) */
		/* to NormalizedSpace (0-1 / 0-1) */
		float x = x_pos / m_camera_handle->GetScreenRatio().X();
		float y = y_pos / m_camera_handle->GetScreenRatio().Y();

		return Vector3f(x, y, 1.f);
	}
	Vector3f GetViewSpaceMouseCoordinates(const Vector3f &clip_coords) {
		/* To get ClipSpace coordinates from the ViewSpace we multiply the current coordinates by the projection matrix. */
		/* So, to get ViewSpace coordinates from the ClipSpace we do the reverse. */
		glm::vec4 view_coords = glm::inverse(m_camera_handle->GetProjectionMatrix().GetGlm())*glm::vec4(clip_coords.X(),clip_coords.Y(),clip_coords.Z(), 1.f);
		return Vector3f(view_coords.x, view_coords.y, view_coords.z);
	}
	Vector3f GetWorldSpaceMouseCoordinates(const Vector3f &view_coords) {
		glm::vec4 world_coords = glm::inverse(m_camera_handle->GetViewMatrix().GetGlm())*glm::vec4(view_coords.X(),view_coords.Y(),view_coords.Z(), 1.f);
		glm::normalize(world_coords);
		return Vector3f(world_coords.x, world_coords.y, world_coords.z);
	}

	Vector3f m_curr_ray;
	Matrix4f m_projection;
	Matrix4f m_view;
	Camera *m_camera_handle;
};