#pragma once
#include <vector>
#include <cmath>

#include <glad\glad.h>

#include "..\Components\MeshRenderer.h"
#include "..\Components\LightMeshRenderer.h"
#include "..\Components\Lights\DirectionalLight.h"
#include "..\Components\Lights\PointLight.h"
#include "..\Components\Input\KeyboardMovement.h"
#include "..\Components\Input\MousePicker.h"

#include "..\Core\Math\Matrix.h"
#include "..\Core\Math\Vector.h"
#include "..\Core\Scene.h"
#include "..\Core\Time.h"
#include "..\Core\Transform.h"





class TestScene :public Scene {
public:
	TestScene() :Scene() {}
	~TestScene();

	void Init(ResourceFactory* rfactory_handle);
	virtual void Input(float dTime, KeyboardState* curr_keyboard_state, MouseState* curr_mouse_state);
	void Update(float dTime);

private:
};