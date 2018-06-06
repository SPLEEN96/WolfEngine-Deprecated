#pragma once
#include "DataTypes\DynamicBuffer.h"

class Camera;
class BaseLight;

struct RenderingEngineData {
friend class RenderingEngine;
public:
	void LinkCamera(Camera* camera) {
		CameraHandle = camera;
	}
	void LinkLight(BaseLight* light) {
		LightsHandle.PushBack(light);
	}
private:
	Camera *CameraHandle;
	DynamicBuffer<BaseLight*> LightsHandle;
};