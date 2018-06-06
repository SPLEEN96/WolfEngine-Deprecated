#pragma once
#include <glad/glad.h>
#include <GLFW\glfw3.h>

#include "Logger.h"
#include "ResourceManagement\DataTypes\Typedefs.h"

#include "Math\Vector.h"

enum CURSOR_MODE {
	CURSOR_NORMAL,
	CURSOR_SELECTION,
	CURSOR_LOOKAT
};

enum KEY_CODE {
	KEY_NULL,
	KEY_SPACE_DOWN,
	KEY_SPACE_UP,
	KEY_X_DOWN,
	KEY_X_UP,
	KEY_W_DOWN,
	KEY_W_UP,
	KEY_A_DOWN,
	KEY_A_UP,
	KEY_D_DOWN,
	KEY_D_UP,
	KEY_S_DOWN,
	KEY_S_UP,
};

struct KeyboardState {
	KEY_CODE KeyCode;
};

struct MouseState {
	Vector2fData MousePosition;
	CURSOR_MODE CursorMode;
};

class Window {
private:
	Window(){}
public:
	Window(const u16 &width, const u16 &height, const char* win_title){
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		m_window = glfwCreateWindow(width, height, win_title, NULL, NULL);
		glfwMakeContextCurrent(m_window);

		glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			OutputErrorMsg("RenderingEngine", ERR_INIT, "Failed to initialize glad.");
		
		m_cursor = NULL;
		m_keyboard_state = new KeyboardState();
		m_mouse_state = new MouseState();
	}
	~Window(){
		Dispose();
		delete(m_keyboard_state);
		delete(m_mouse_state);
	}
	
	bool WindowShouldClose() {
		return glfwWindowShouldClose(m_window);
	}

	void SwapBuffers() {
		glfwSwapBuffers(m_window);
	}
	void PollEvents() {
		glfwPollEvents();
	}

	GLFWwindow* GetHandle() {
		return m_window;
	}

	KeyboardState* GetKeyboardEvents() {
		static bool w_pressed = false;
		static bool a_pressed = false;
		static bool d_pressed = false;
		static bool s_pressed = false;
		static bool space_pressed = false;
		static bool x_pressed = false;
		
		if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(m_window, true);

		if (!w_pressed && glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS) {
			w_pressed = true;
			m_keyboard_state->KeyCode = KEY_W_DOWN;
		}
		if (!a_pressed && glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS) {
			a_pressed = true;
			m_keyboard_state->KeyCode = KEY_A_DOWN;
		}
		if (!d_pressed && glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS) {
			d_pressed = true;
			m_keyboard_state->KeyCode = KEY_D_DOWN;
		}
		if (!s_pressed && glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS) {
			s_pressed = true;
			m_keyboard_state->KeyCode = KEY_S_DOWN;
		}
		if (!space_pressed && glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			space_pressed = true;
			m_keyboard_state->KeyCode = KEY_SPACE_DOWN;
		}
		if (!x_pressed && glfwGetKey(m_window, GLFW_KEY_X) == GLFW_PRESS) {
			x_pressed = true;
			m_keyboard_state->KeyCode = KEY_X_DOWN;
		}



		if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_RELEASE && w_pressed) {
			w_pressed = false;
			m_keyboard_state->KeyCode = KEY_W_UP;
		}
		if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_RELEASE && a_pressed) {
			a_pressed = false;
			m_keyboard_state->KeyCode = KEY_A_UP;
		}
		if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_RELEASE && d_pressed) {
			d_pressed = false;
			m_keyboard_state->KeyCode = KEY_D_UP;
		}
		if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_RELEASE && s_pressed) {
			s_pressed = false;
			m_keyboard_state->KeyCode = KEY_S_UP;
		}
		if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_RELEASE && space_pressed) {
			space_pressed = false;
			m_keyboard_state->KeyCode = KEY_SPACE_UP;
		}
		if (glfwGetKey(m_window, GLFW_KEY_X) == GLFW_RELEASE && x_pressed) {
			x_pressed = false;
			m_keyboard_state->KeyCode = KEY_X_UP;
		}


		return m_keyboard_state;
	}

	MouseState* GetMouseEvents() {
		double mouse_pos[2];
		glfwGetCursorPos(m_window, &mouse_pos[0], &mouse_pos[1]);
		m_mouse_state->MousePosition.X = mouse_pos[0];
		m_mouse_state->MousePosition.Y = mouse_pos[1];
		m_mouse_state->CursorMode = CURSOR_NORMAL;

		if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			m_mouse_state->CursorMode = CURSOR_SELECTION;
		}
		if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
			m_mouse_state->CursorMode = CURSOR_NORMAL;
		}

		if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
			m_mouse_state->CursorMode = CURSOR_LOOKAT;
		}
		if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
			m_mouse_state->CursorMode = CURSOR_NORMAL;
		}

		switch (m_mouse_state->CursorMode) {
		case CURSOR_NORMAL:
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			break;
		case CURSOR_SELECTION:
			break;
		case CURSOR_LOOKAT:
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		default:
			break;
		}

		return m_mouse_state;
	}

	void Dispose() {
		glfwDestroyWindow(m_window);
		m_window = NULL;
	}
private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	GLFWwindow *m_window;
	GLFWcursor *m_cursor;
	KeyboardState *m_keyboard_state;
	MouseState *m_mouse_state;
};

