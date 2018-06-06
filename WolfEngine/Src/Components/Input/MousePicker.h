#pragma once
#include <iostream>

#include "MouseHandler.h"
#include "..\..\Physics\MouseRay.h"

class MousePicker :public MouseHandler {
public:
	MousePicker(Camera* camera, Entity* root_entity_handle) {
		m_ray = new MouseRay(camera);
		m_root_entity_handle = root_entity_handle;
	}
	virtual void Input(float dTime, KeyboardState* curr_keyboard_state, MouseState* curr_mouse_state) {
		m_ray->Input(curr_mouse_state->MousePosition.X, curr_mouse_state->MousePosition.Y);
	}
	virtual void Update(float dTime) {
	}
private:
	MouseRay *m_ray;
	Entity *m_root_entity_handle;
};