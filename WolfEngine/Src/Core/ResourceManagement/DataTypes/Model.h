#pragma once

#include "..\DataTypes\DynamicBuffer.h"

#include "..\..\..\Rendering\Mesh.h"

struct Model {
private:
	Model() {}
public:
	Model(const char model_name[]) {
		name = model_name;
	}
	~Model() {
		for (u32 i = 0; i < meshes.Length(); i++) {
			delete(meshes[i]);
		}
		meshes.Clear();
		for (u32 i = 0; i < textures.Length(); i++) {
			delete(textures[i]);
		}
		textures.Clear();
	}

	DynamicBuffer<Mesh*> meshes;
	DynamicBuffer<Texture*> textures;
	const char *name;
};