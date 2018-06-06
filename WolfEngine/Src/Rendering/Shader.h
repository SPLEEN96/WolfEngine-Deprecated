#pragma once
#include <glad\glad.h>

#include "..\Core\ResourceManagement\Loaders\ShaderSourceLoader.h"
#include "..\Core\Logger.h"

#include "..\Core\Transform.h"
#include "..\Core\Math\Matrix.h"
#include "..\Core\Math\Vector.h"

#include "..\Components\Camera.h"
#include "..\Rendering\Material.h"

enum SHD_ERROR_TYPE : u16 {
	SSHADER_COMPILE,
	PPROGRAM_LINKING
};

/* TODO:Automatic Uniforms coupling in UpdateUniforms(). */
class Shader {
public:
	Shader() {
		m_vshd = m_fshd = m_program = NULL;
	}
	virtual ~Shader() {
		if (m_program != NULL)
			glDeleteProgram(m_program);

	}

	void Init(const GLchar* shd_filename) {
		ShaderSourceLoader ssloader;
		m_vshd_source = ssloader.LoadSourceFile(shd_filename, VSHADER_EXTENSION);
		m_fshd_source = ssloader.LoadSourceFile(shd_filename, FSHADER_EXTENSION);

		CompileShaders();
		LinkProgram();
	}

	void Bind() {
		if (m_program != NULL)
			glUseProgram(m_program);
		else
			Logger::GetInstance().OutputErrorMsg("Shader", ERR_NOINIT,
				"The shader program is not initialized. Use Shader::Init() first.");
	}

	GLuint GetId() {
		if (m_program != NULL)
			return m_program;
		else
			Logger::GetInstance().OutputErrorMsg("Shader", ERR_NOINIT,
				"The shader program is not initialized. Use Shader::Init() first.");
	}

	/* ============================= UNIFORMS ============================= */
	void SetInt(const char* name, const int &val) {
		glUniform1i(glGetUniformLocation(this->GetId(), name), val);
	}
	void SetFloat(const char* name, const float &val) {
		glUniform1f(glGetUniformLocation(this->GetId(), name), val);
	}
	void SetVector3f(const char* name, u16 count, const Vector3f &vec) {
		glUniform3fv(glGetUniformLocation(this->GetId(), name), count, vec.GetData());
	}
	void SetMatrix4f(const char* name, const Matrix4f &mat) {
		glUniformMatrix4fv(glGetUniformLocation(m_program, name), 1, GL_FALSE, mat.GetData());
	}

	void SetCoordinates(Matrix4f model, Matrix4f view, Matrix4f projection) {
		SetMatrix4f("model", model);
		SetMatrix4f("view", view);
		SetMatrix4f("projection", projection);
	}

	virtual void UpdateUniforms(Transform *transform, Material *material) {}


private:
	void CompileShaders() {
		m_vshd = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(m_vshd, 1, &m_vshd_source, NULL);
		glCompileShader(m_vshd);
		GetErrors(SSHADER_COMPILE, m_vshd);


		m_fshd = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(m_fshd, 1, &m_fshd_source, NULL);
		glCompileShader(m_fshd);
		GetErrors(SSHADER_COMPILE, m_fshd);
	}

	void LinkProgram() {
		m_program = glCreateProgram();
		glAttachShader(m_program, m_vshd);
		glAttachShader(m_program, m_fshd);
		glLinkProgram(m_program);
		GetErrors(PPROGRAM_LINKING, m_program);

		glDeleteShader(m_vshd);
		glDeleteShader(m_fshd);
		free(m_vshd_source);
		free(m_fshd_source);
	}

	void GetErrors(const u16 &error_type, const GLuint &glhandle) {
		GLchar err_log[512] = { "" };
		GLint success = 1;
		if (error_type == SSHADER_COMPILE) {
			glGetShaderiv(glhandle, GL_COMPILE_STATUS, &success);
		    glGetShaderInfoLog(glhandle, 512, NULL, err_log);
			if (!success)
				OutputErrorMsg("Shader", ERR_GLSHDR, err_log);
		}
		if (error_type == PPROGRAM_LINKING) {
			glGetProgramiv(glhandle, GL_LINK_STATUS, &success);
			glGetProgramInfoLog(glhandle, 512, NULL, err_log);
			if (!success)
				Logger::GetInstance().OutputErrorMsg("Shader", ERR_GLSHDR, err_log);
		}
	}



private:
	char *m_vshd_source, *m_fshd_source;
	GLuint m_vshd, m_fshd, m_program;
};