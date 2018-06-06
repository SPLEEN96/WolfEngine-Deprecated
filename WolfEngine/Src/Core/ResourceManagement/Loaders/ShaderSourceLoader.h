#pragma once
#include <stdio.h>

#include "ResourceLoader.h"

const char SHADER_PATH[] = PROJECT_DIR"Resources\\Shaders\\";
const char VSHADER_EXTENSION[] = ".vshd";
const char FSHADER_EXTENSION[] = ".fshd";
const char SHADER_INCLUDE_EXTENSION[] = "";


struct  ShaderSourceLoader :public ResourceLoader{
public:
	char* LoadSourceFile(const char filename[], const char file_extension[]) {
		char *fullpath = ResourceLoader::GetFullPath(SHADER_PATH, filename, file_extension);

		char *buffer = NULL;
		FILE *filep;
		filep = fopen(fullpath, "r");
		if (filep) {
			buffer = ResourceLoader::ReadFromFile(filep, ResourceLoader::GetFileLen(filep));
			buffer = ProcessIncludeDirective(buffer, ResourceLoader::GetFileLen(filep));
			fclose(filep);
		}
		else
			OutputErrorMsg("ShaderSourceLoader (file not found)", ERR_NOFILE, fullpath);


		free(fullpath);
		return buffer;
	}

private:
	/* GLSL doesn't support #include so there is a lot of code duplication between shaders. */
	/* The following method prevents this by parsing the shader source code for an #include directive */
	/* and appending the include source code in the shader source code. */
	char* ProcessIncludeDirective(char* shader_source, const u32 shader_len) {
		/* Length of "#include" */
		const u8 INCLUDE_LEN = 9;
		
		/* Get the first line of the shader source code. */
		const u16 FIRSTLINE_LEN = strcspn(shader_source, "\n");
		char *shader_firstline = (char*)malloc(FIRSTLINE_LEN * sizeof(char));
		shader_firstline =strncpy(shader_firstline, shader_source, FIRSTLINE_LEN);
		shader_firstline[FIRSTLINE_LEN - 1] = '\0';

		/* if the first line of the shader is an include */
		if (strncmp(shader_firstline, "#include", INCLUDE_LEN-1) == 0) {
			const char *filename = &shader_firstline[INCLUDE_LEN + 1];
			char *include_source = LoadSourceFile(filename, SHADER_INCLUDE_EXTENSION);
			
			/* Create a new buffer with the size of the shader source code + the size of the include source code... */
			char *buffer;
			buffer = (char*)malloc((strlen(include_source) + shader_len) * sizeof(char));
			/* And append the shader source code to the include source code. */
			strcpy(buffer, (include_source));
			strcat(buffer, (shader_source + FIRSTLINE_LEN)); /* Remove the "#include" in the source code */

			free(shader_firstline);
			free(shader_source);
			free(include_source);
			return buffer;
		}

		free(shader_firstline);
		return shader_source;
	}
};