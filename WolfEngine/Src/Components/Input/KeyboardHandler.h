#pragma once

#include "..\..\Core\Entity.h"
#include "..\..\Core\Window.h"

class KeyboardHandler : public EntityComponent {
protected:
	KeyboardHandler() {
		m_type = COMP_INPUT;
	}
public:
	virtual ~KeyboardHandler() {}

	virtual void Input(float dTime, KeyboardState* curr_keyboard_state, MouseState* curr_mouse_state) {}
	void Update(float dTime) {}

private:
};