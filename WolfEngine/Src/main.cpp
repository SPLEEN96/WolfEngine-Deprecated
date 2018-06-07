/* =-=-= PROJECT STARTED 05/17/2018 =-=-= */
/* =-=-=-=-=- RENDERING ENGINE -=-=-=-=-= */
/* =-=-=-=-=-=-=-=-= BY =-=-=-=-=-=-=-=-= */
/* =-=-=-=-=-=- NICOLAS GUAY -=-=-=-=-=-= */

/*  Notes: Since I never built dll before, */
/*     it is an "header-only" Library      */
/* because I didn't want to have a tedious */
/*  build process due to my limited time   */

/* Lib: glad, glfw, glm, stb_image, assimp, imgui */

/* 3 memory leaks */
/* 3 from glfw (368 bytes) */
/* 1 unknown source (284 bytes) */
#define STB_IMAGE_IMPLEMENTATION
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "Core\CoreEngine.h"

#include "TestScene\TestScene.h"


int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	CoreEngine::GetInstance().Init(1280, 720, 60); /* By keeping the resolution to 720p it is easier to look a the Console. */
	//CoreEngine::GetInstance().Init(1920, 1080, 60);
	CoreEngine::GetInstance().CreateEngineWindow("WolfEngine", new TestScene());
	CoreEngine::GetInstance().Start();

	return 0;
}