#pragma once
#include <queue>

#include "KeyboardHandler.h"

class KeyboardMovement : public KeyboardHandler {
public:
	KeyboardMovement() :KeyboardHandler() {
		m_x = m_y = m_z = 0.f;
	}
	virtual ~KeyboardMovement() {}

	void Input(float dTime, KeyboardState* curr_keyboard_state, MouseState* curr_mouse_state) {
		if (curr_keyboard_state->KeyCode == KEY_W_DOWN)
			m_z = SPEED;
		if (curr_keyboard_state->KeyCode == KEY_S_DOWN)
			m_z = -SPEED;
		if (curr_keyboard_state->KeyCode == KEY_A_DOWN)
			m_x = SPEED;
		if (curr_keyboard_state->KeyCode == KEY_D_DOWN)
			m_x = -SPEED;
		if (curr_keyboard_state->KeyCode == KEY_SPACE_DOWN)
			m_y = SPEED;
		if (curr_keyboard_state->KeyCode == KEY_X_DOWN)
			m_y = -SPEED;

		if (curr_keyboard_state->KeyCode == KEY_W_UP)
			if (m_z > 0.f)
				m_z = 0.f;
		if (curr_keyboard_state->KeyCode == KEY_S_UP)
			if (m_z < 0.f)
				m_z = 0.f;
		if (curr_keyboard_state->KeyCode == KEY_A_UP)
			if (m_x > 0.f)
				m_x = 0.f;
		if (curr_keyboard_state->KeyCode == KEY_D_UP)
			if (m_x < 0.f)
				m_x = 0.f;
		if (curr_keyboard_state->KeyCode == KEY_SPACE_UP)
			if (m_y > 0.f)
				m_y = 0.f;
		if (curr_keyboard_state->KeyCode == KEY_X_UP)
			if (m_y < 0.f)
				m_y = 0.f;
	}

	void Update(float dTime) {
		Vector3f translate = Vector3f(m_x*dTime, m_y*dTime, m_z*dTime);
		m_parent->GetTransform()->Translate(translate);
	}



private:
	float m_x, m_y, m_z;
	const float SPEED = 3.f;
};