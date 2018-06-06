#pragma once

#include "MouseHandler.h"

class MouseMovement :public MouseHandler {
public:
	MouseMovement(const float &screen_width, const float &screen_height) {
		m_last_x_pos = m_last_y_pos = 0.f;
		m_x_offset = m_y_offset = 0.f;
	}
	virtual void Input(float dTime, KeyboardState* curr_keyboard_state, MouseState* curr_mouse_state) {
		static bool first_click = true;
		if (curr_mouse_state->CursorMode == CURSOR_LOOKAT) {
			if (first_click) {
				m_last_x_pos = curr_mouse_state->MousePosition.X;
				m_last_y_pos = curr_mouse_state->MousePosition.Y;
				first_click = false;
			}
			m_x_offset = curr_mouse_state->MousePosition.X - m_last_x_pos;
			m_y_offset = m_last_y_pos - curr_mouse_state->MousePosition.Y; /* Reversed because of glfw y coordinate range from top to bottom */
			m_x_offset *= m_SENSITIVITY;
			m_y_offset *= m_SENSITIVITY;

			m_last_x_pos = curr_mouse_state->MousePosition.X;
			m_last_y_pos = curr_mouse_state->MousePosition.Y;
		}
		else{
			first_click = true;
			m_last_x_pos = m_last_y_pos = 0.f;
		}
	}

	virtual void Update(float dTime) {

	}



private:
	const float m_SENSITIVITY = 0.025f;
	float m_last_x_pos, m_last_y_pos;
	float m_x_offset, m_y_offset;
};