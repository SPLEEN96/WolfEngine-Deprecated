#pragma once
#include <glad\glad.h>

#include "..\Core\ResourceManagement\Loaders\ImageLoader.h"

/* Still not (really) implemented */
class Texture {
public:
	Texture(const char* filename) {
		ImageLoader imgloader;
		unsigned char* img_buffer = imgloader.LoadImg(filename);

		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgloader.GetImgWidth(), imgloader.GetImgHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, img_buffer);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		imgloader.FreeImgData(img_buffer);
	}
	Texture(const Texture &rhs) {
		this->m_texture = rhs.m_texture;
		this->type = rhs.type;
	}
	~Texture() {}
	const Texture operator=(const Texture &rhs) {
		this->m_texture = rhs.m_texture;
		this->type = rhs.type;
	}

	void Bind(int sampler_index) {
		glActiveTexture(GL_TEXTURE0 + sampler_index);
		glBindTexture(GL_TEXTURE_2D, m_texture);
	}
	void Unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

private:
	GLuint m_texture;
	const char* type;
};