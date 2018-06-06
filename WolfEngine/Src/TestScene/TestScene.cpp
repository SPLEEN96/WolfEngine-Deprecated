#include "TestScene.h"


#include "..\Core\ResourceManagement\ResourceFactory.h"
//#include "..\Components\Camera.h"

void TestScene::Init(ResourceFactory* rfactory_handle) {

}


void TestScene::Input(float dTime, KeyboardState* curr_keyboard_state, MouseState* curr_mouse_state) {
	m_root_entity->Input(dTime, curr_keyboard_state, curr_mouse_state);
}

void TestScene::Update(float dTime) {
  	m_root_entity->Update(dTime);
}






TestScene::~TestScene() {
	if (m_root_entity != NULL)
		delete m_root_entity;
}