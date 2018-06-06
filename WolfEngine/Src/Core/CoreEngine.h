#pragma once
#define DEBUG_MODE

#include "Time.h"
#include "Logger.h"
#include "Window.h"
#include "ResourceManagement\ResourceFactory.h"

#include "..\Rendering\RenderingEngine.h"
#include "..\TestScene\TestScene.h"

class CoreEngine {
private:
	CoreEngine() : m_win_handle(NULL), m_width(0), m_height(0), m_framerate(0), m_SEC_PER_FRAME(0), m_isRunning(false), m_isInit(false) {}
	~CoreEngine() {
		/* see CleanUp() func */
	}

	CoreEngine(CoreEngine const&) {}					/* Don't want the compiler to generate copy constructor. */
	void operator=(CoreEngine const&) {}				/* Don't want the compiler to generate copy assignment operator. */

public:
	static CoreEngine& GetInstance() {
		static CoreEngine engine_instance;
		return engine_instance;
	}
	
	void Init(u16 width, u16 height, u16 framerate) {
		if (!m_isInit) {
			m_isInit = true;
			m_width = width;
			m_height = height;
			m_framerate = framerate;
			m_SEC_PER_FRAME = 1.f / (float)m_framerate;
			return;
		}
		OutputErrorMsg("CoreEngine", ERR_INIT, "The engine is already initialized.");
	}
	void CreateEngineWindow(const char *win_title, Scene *curr_scene) {
		if (m_isInit) {
			if (m_win_handle == NULL) {
				m_win_handle = new Window(m_width, m_height, win_title);
				m_win_handle->SwapBuffers();

				m_scene_handle = curr_scene;
				m_scene_handle->SetScreenRatio(m_width, m_height);
				m_scene_handle->Init(&m_rfactory);


				RenderingEngine::GetInstance().InitGL(m_width, m_height);
				m_gui_handle = new GUImanager();
				m_gui_handle->Init(m_win_handle, m_scene_handle->GetRootEntity());
			}
			return;
		}
		OutputErrorMsg("CoreEngine", ERR_NOINIT, "The engine needs to be initialized before creating a Window.");
	}


	void Start() {
		m_isRunning = true;
		Run();
	}
	void Stop() {
		m_isRunning = false;
		CleanUp();
	}
	void CleanUp() {
		delete m_scene_handle;
		if (CoreEngine::GetInstance().m_win_handle != NULL) {
			CoreEngine::GetInstance().m_win_handle->Dispose();
			delete CoreEngine::GetInstance().m_win_handle;
		}
		m_gui_handle->CleanUp();
		delete m_gui_handle;
	}
private:
	void Run() {
		float currframe_time =0.f;
		float lastframe_time =0.f;
		float dTime = 0.f;
		u16 frames = 0;
		float elapsed_time =0.f; /* in secs */

		while (m_isRunning) {
			if (m_win_handle->WindowShouldClose())
				m_isRunning = false;

			dTime =Time::GetDelta(lastframe_time, currframe_time);
			if (dTime > 1)dTime = 0;
			elapsed_time += dTime;

			ProcessInput(dTime);
			Update(dTime);
			Render();

			Time::Sleep((currframe_time + m_SEC_PER_FRAME) - Time::GetTime());
			frames++;
			if (elapsed_time >= 1.f) {
				OutputMsgStr("FPS", frames);
				elapsed_time = 0;
				frames = 0;
			}

			GLenum err;
			while ((err = glGetError()) != GL_NO_ERROR) {
				OutputMsgStr("GL_ERR", err);
			}
		}
		Stop();
	}

	void ProcessInput(float dTime) {
		m_win_handle->PollEvents();
		if (m_scene_handle->GetRootEntity() != NULL)
			m_scene_handle->Input(dTime, m_win_handle->GetKeyboardEvents(),m_win_handle->GetMouseEvents());
	}
	void Update(float dTime) {
		if (m_scene_handle->GetRootEntity() != NULL)
			m_scene_handle->Update(dTime);
	}
	void Render() {
		if (m_scene_handle->GetRootEntity() != NULL)
			RenderingEngine::GetInstance().Render(m_scene_handle->GetRootEntity());
		m_gui_handle->Render(m_scene_handle->GetRootEntity(), &m_rfactory);
		m_win_handle->SwapBuffers();
	}

	ResourceFactory m_rfactory;
	Scene *m_scene_handle;
	Window *m_win_handle;
	GUImanager *m_gui_handle;
	u16 m_width, m_height;
   	u16 m_framerate;
	float m_SEC_PER_FRAME;
	bool m_isRunning;
	bool m_isInit;
};
