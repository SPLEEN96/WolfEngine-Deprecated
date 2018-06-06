#pragma once

#include "..\Rendering\Vertex.h"

static Vertex TRIANGLE_DATA[] = {
	Vertex(Vector3fData(-0.5f,-0.5f,0.f), Vector3fData(0.f,0.f,0.f), Vector2fData(0.f,0.f)),
	Vertex(Vector3fData(0.5f,-0.5f,0.f),Vector3fData(0.f,0.f,0.f), Vector2fData(0.f,0.f)),
	Vertex(Vector3fData(0.f,0.5f,0.f),Vector3fData(0.f,0.f,0.f), Vector2fData(0.f,0.f))
};
static u32 TRIANGLE_INDICES[]={0,1,2};
