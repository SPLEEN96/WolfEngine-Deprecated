#pragma once
#include <glad\glad.h>

#include "..\Core\ResourceManagement\RenderingEngineData.h"

#include "GUImanager.h"
#include "ForwardAmbient.h"
#include "ForwardDirectional.h"
#include "ForwardPointLight.h"

#include "..\Core\Logger.h"
#include "..\Core\Scene.h"
#include "..\Core\Time.h"

#include "..\Components\Lights\BaseLight.h"
#include "..\Components\Camera.h"

class RenderingEngine {
private:
	RenderingEngine() {
		m_rdata=new RenderingEngineData();
	}
	RenderingEngine(RenderingEngine const&) {}				 /* Don't want compiler to generate copy constructor */
	void operator=(RenderingEngine const&) {}	   	   		/* Don't want compiler to generate copy assignment operator */
public:
	~RenderingEngine() {
		delete(m_rdata);
	}
	static RenderingEngine& GetInstance() {
		static RenderingEngine engine_instance;
		return engine_instance;
	}
	void InitGL(const float &scr_width, const float &scr_height) {
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		if (m_rdata->CameraHandle == NULL)
			OutputErrorMsg("RenderingEngine", ERR_NOINIT, "There is no camera currently linked to the Rendering Engine.");

		ForwardAmbient::GetInstance().SetCamera(m_rdata->CameraHandle);
		ForwardDirectional::GetInstance().SetCamera(m_rdata->CameraHandle);
		ForwardPointLight::GetInstance().SetCamera(m_rdata->CameraHandle);
	}

	void Render(Entity *root_entity) {
		ClearScreen();
		
		ForwardAmbient::GetInstance().SetAmbient(0.2f);
		root_entity->Render(&ForwardAmbient::GetInstance(), m_rdata->CameraHandle->GetPosition());

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_EQUAL);
		for (u16 i = 0; i < m_rdata->LightsHandle.Length(); i++) {
			root_entity->Render(m_rdata->LightsHandle[i]->GetShader(), m_rdata->CameraHandle->GetPosition());
		}
		glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}


	RenderingEngineData* GetDataHandle() {
		return m_rdata;
	}
	Camera* GetCamera() {
		return m_rdata->CameraHandle;
	}

private:
	void ClearScreen(){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	RenderingEngineData *m_rdata;
};