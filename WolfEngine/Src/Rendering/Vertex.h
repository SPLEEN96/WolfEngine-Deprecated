#pragma once

#include "..\Core\Math\Vector.h"


struct Vertex {
	Vertex() {}
	Vertex(Vector3fData position, Vector3fData normal, Vector2fData texcoord)
		:Position(position), Normal(normal), TexCoordinates(texcoord) {}

	Vector3fData Position;
	Vector3fData Normal;
	Vector2fData TexCoordinates;
};
