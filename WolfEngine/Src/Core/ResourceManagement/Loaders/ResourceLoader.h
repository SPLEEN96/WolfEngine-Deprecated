#pragma once
#include <stdio.h>

#include "..\..\Logger.h"

#define PROJECT_DIR "C:\\Users\\SPLEEN\\Home\\PROJECTS\\RENDERING\\WolfEngine\\WolfEngine\\"

/* Abstract Base Class with utils function for i/o reading */
struct  ResourceLoader {
protected:
    /* Concatenate the directory path, the filename and the file extension into one char buffer */
	char* GetFullPath(const char dir_path[], const char filename[], const char file_extension[]) {
		const u32 fullpath_len = strlen(dir_path) + strlen(filename) + strlen(file_extension) + 1;
		char *fullpath = (char*)malloc(fullpath_len * sizeof(char));

		strcpy(fullpath, dir_path);
		strcat(fullpath, filename);
		strcat(fullpath, file_extension);

		return fullpath;
	}
	/* Concatenate the directory path, the filename and the file extension into one char buffer */
	char* GetFullPath(const char dir_path[], const char filename[]) {
		const u32 fullpath_len = strlen(dir_path) + strlen(filename) + 1;
		char *fullpath = (char*)malloc((fullpath_len * sizeof(char)));

		strcpy(fullpath, dir_path);
		strcat(fullpath, filename);

		return fullpath;
	}

	/* Get the length of a file for reading */
	u32 GetFileLen(FILE *filep) const {
		fseek(filep, 0L, SEEK_END);
		return ftell(filep);
	}

	/* Put the content of a file into a char buffer */
	char* ReadFromFile(FILE *filep, const u32 &file_len) const {
		char* buffer = (char*)malloc(file_len * sizeof(char));
		int curr_char;                          /* curr_char is an int instead of a char because EOF is a negative number and char may be unsigned */
		u32 index = 0;

		fseek(filep, 0, SEEK_SET);              /* Set the cursor at the begining of the file */
		while ((curr_char = getc(filep)) != EOF) {
			buffer[index] = curr_char;
			index++;
		}
		buffer[index] = '\n';
		buffer[index + 1] = '\0';
		return buffer;
	}
};