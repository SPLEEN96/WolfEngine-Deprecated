#pragma once

#include "..\..\Core\Entity.h"
#include "..\..\Core\Window.h"

class MouseHandler :public EntityComponent {
protected:
	MouseHandler(){}
public:
	virtual void Input(float dTime, KeyboardState* curr_keyboard_state, MouseState* curr_mouse_state) {}
private:
};