#pragma once

#include "..\Core\Transform.h"

#include "..\Rendering\Material.h"

enum COMPONENT_TYPE {
	COMP_NULL,
	COMP_TRANSFORM,
	COMP_MESH_RENDERER,
	COMP_LMESH_RENDERER,
	COMP_LIGHT,
	COMP_CAMERA,
	COMP_INPUT
};
static const char* COMPONENT_TYPE_STR[]{
	"NULL",
	"Transform",
	"Mesh Renderer",
	"LightMesh Renderer",
	"Light",
	"Camera",
	"Input Handler"
};
class Entity;
class Shader;
struct KeyboardState;
struct MouseState;
class EntityComponent {
public:
	EntityComponent() {
		m_type = COMP_NULL;
	}
	virtual ~EntityComponent() {}
	virtual void Input(float dTime, KeyboardState* curr_keyboard_state, MouseState* curr_mouse_state) {}
	virtual void Update(float dTime) {}
	virtual void Render(Shader *shader) {}

	Entity* GetParent() {
		return m_parent;
	}
	void SetParent(Entity *parent) {
		m_parent = parent;
	}


	COMPONENT_TYPE GetType() const{
		return m_type;
	}
	const char* GetTypeStr() const {
		return COMPONENT_TYPE_STR[m_type];
	}

protected:
	COMPONENT_TYPE m_type;
	Entity *m_parent;
};