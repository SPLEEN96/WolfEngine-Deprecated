#pragma once

#include "Entity.h"

#include "..\Rendering\RenderingEngine.h"

#include "ResourceManagement\ResourceFactory.h"

class Scene {
public:
	Scene() :m_screen_width(0), m_screen_height(0) {
		m_root_entity = new Entity("ROOT", false);
	}
	~Scene() {
		delete m_root_entity;
	}

	virtual void Init(ResourceFactory* rfactory_handle){}
	virtual void Input(float dTime, KeyboardState* curr_keyboard_state, MouseState* curr_mouse_state) {
		m_root_entity->Input(dTime, curr_keyboard_state, curr_mouse_state);
	}
	virtual void Update(float dTime) {
		m_root_entity->Update(dTime);
	}

	Entity* GetRootEntity() {
		return m_root_entity;
	}


	void SetScreenRatio(float screen_width, float screen_height) {
		m_screen_width = screen_width;
		m_screen_height = screen_height;
	}
	float GetScreenRatio() {
		return (m_screen_width / m_screen_height);
	}

protected:
	Entity *m_root_entity;
	float m_screen_width, m_screen_height;
};