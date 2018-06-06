#pragma once

//#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "ResourceLoader.h"

const char IMG_PATH[] = PROJECT_DIR"Resources\\";

struct ImageLoader :public ResourceLoader{
public:
	ImageLoader() :m_width(0), m_height(0) {}

	unsigned char* LoadImg(const char* filename) {
		int nrChannels;
		
		char *fullpath = ResourceLoader::GetFullPath(IMG_PATH, filename);
		
		unsigned char* img_buffer = stbi_load(fullpath, &m_width, &m_height, &nrChannels, 0);
		if (!img_buffer)
			OutputErrorMsg("ImageLoader (file not found)", ERR_NOFILE, fullpath);

		free(fullpath);
		return img_buffer;
	}
	
	int GetImgWidth() {
		return m_width;
	}
	int GetImgHeight() {
		return m_height;
	}
	
	void FreeImgData(unsigned char* img_buffer) {
		stbi_image_free(img_buffer);
	}

private:
	int m_width, m_height;
};