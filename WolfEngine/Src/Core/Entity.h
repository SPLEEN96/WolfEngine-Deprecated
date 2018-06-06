#pragma once

#include "..\Components\EntityComponent.h"

#include "ResourceManagement\DataTypes\DynamicBuffer.h"

class Entity {
	Entity() {}
public:
	Entity(const char name[], bool isStatic=false) {
		m_transform = new Transform();
		m_children = new DynamicBuffer<Entity*>();
		m_components = new DynamicBuffer<EntityComponent*>();

		m_name = (char*)malloc(20 * sizeof(char));
		strncpy(m_name, name, 19);
		m_name[19] = '\0';

		m_isStatic = isStatic;
	}
	~Entity() {
		for (u32 i = 0; i < m_children->Length(); i++) {
			delete m_children[0][i];
		}

		for (u32 i = 0; i < m_components->Length(); i++) {
			delete m_components[0][i];
		}
		
		m_children->Clear();
		m_components->Clear();
		delete(m_children);
		delete(m_components);
		delete m_transform;
		free(m_name);
	}

	void AddChild(Entity *child) {
		child->GetTransform()->SetParent(m_transform);
		m_children->PushBack(child);
	}


	void AddComponent(EntityComponent* component) {
		component->SetParent(this);

		/* The input components needs to be updated first */
		if (component->GetType() == COMP_INPUT)
			m_components->PushFront(component);
		else
			m_components->PushBack(component);
	}

	void Input(float dTime, KeyboardState* curr_keyboard_state, MouseState* curr_mouse_state) {
		/* Input Componenents */
		for (u32 i = 0; i < m_components->Length(); i++)
			m_components[0][i]->Input(dTime, curr_keyboard_state, curr_mouse_state);
		/* Input Children Entities */
		for (u32 i = 0; i < m_children->Length(); i++)
			m_children[0][i]->Input(dTime, curr_keyboard_state, curr_mouse_state);
	}
	void Update(float dTime) {
		if (!m_isStatic) {
			/* Update Components */
			for (u32 i = 0; i < m_components->Length(); i++)
				m_components[0][i]->Update(dTime);
			/* Update Children Entities */
			for (u32 i = 0; i < m_children->Length(); i++)
				m_children[0][i]->Update(dTime);
		}
	}

	void Render(Shader* shader, Vector3f camera_pos) {
		if (m_transform->GetDistanceFrom(camera_pos) < 32.f) {
			/* Render Components */
			for (u32 i = 0; i < m_components->Length(); i++)
				m_components[0][i]->Render(shader);
			/* Render Children Entities */
			for (u32 i = 0; i < m_children->Length(); i++)
				m_children[0][i]->Render(shader, camera_pos);
		}
	}


	const char* GetName() {
		return m_name;
	}
	Transform* GetTransform() {
		return m_transform;
	}
	
	u32 NumberOfChildren() {
		return m_children->Length();
	}
	Entity* GetChild(u32 index){
		if (index >= 0 && index < m_children->Length())
			return m_children[0][index];
		else
			return NULL;
	}
	u32 NumberOfComponents() {
		return m_components->Length();
	}
	EntityComponent* GetComponent(u32 index) {
		if (index >= 0 && index < m_components->Length())
			return m_components[0][index];
		else
			return NULL;
	}

private:
	Transform *m_transform;
	DynamicBuffer<Entity*> *m_children;
	DynamicBuffer<EntityComponent*> *m_components;
	char* m_name;
	bool m_isStatic;
};