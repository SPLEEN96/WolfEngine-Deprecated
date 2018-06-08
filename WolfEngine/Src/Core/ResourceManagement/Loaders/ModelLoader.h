#pragma once

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "ResourceLoader.h"
#include "..\DataTypes\DynamicBuffer.h"
#include "..\DataTypes\Model.h"

#include "..\..\Entity.h"
#include "..\..\..\Components\MeshRenderer.h"

#include "..\..\..\Rendering\Vertex.h"
#include "..\..\..\Rendering\Mesh.h"

const char MODEL_PATH[] = PROJECT_DIR"Resources\\Models\\";

struct ModelLoader :public ResourceLoader {
	Model* LoadModel(const char* filename) {
		char* fullpath = ResourceLoader::GetFullPath(MODEL_PATH, filename);

		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(fullpath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			OutputErrorMsg("MeshLoader (assimp)", ERR_ASSIMP, importer.GetErrorString());
		}
		free(fullpath);

		
		DynamicBuffer<Mesh*> meshes;
		ProcessNode(meshes, scene->mRootNode, scene);

		Model *loaded_model = new Model(filename);
		for (u32 i = 0; i < meshes.Length(); i++) {
			loaded_model->meshes.PushBack(meshes[i]);
		}

		return loaded_model;
	}



private:
	/* Iterates through all the mesh of the rootnode and its children */
	void ProcessNode(DynamicBuffer<Mesh*> &meshes, aiNode *node, const aiScene *scene) {
		for (u32 i = 0; i < node->mNumMeshes; i++) {
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];

			meshes.PushBack(ProcessMesh(mesh, scene));
		}

		for (u32 i = 0; i < node->mNumChildren; i++) {
			ProcessNode(meshes, node->mChildren[i], scene);
		}
	}

	/* Convert an aiMesh to a Mesh */
	Mesh* ProcessMesh(aiMesh *aimesh, const aiScene *scene) {
		Mesh *mesh = new Mesh();
		DynamicBuffer<Vertex> vertices;
		DynamicBuffer<u32> indices;
		DynamicBuffer<Texture> textures;

		/* Process Vertex */
		for (u32 i = 0; i < aimesh->mNumVertices; i++) {
			Vertex vertex;
			/* Process Position */
			vertex.Position.X = aimesh->mVertices[i].x;
			vertex.Position.Y = aimesh->mVertices[i].y;
			vertex.Position.Z = aimesh->mVertices[i].z;

			/* Process Normal */
			if (aimesh->mNormals != NULL) {
				vertex.Normal.X = aimesh->mNormals[i].x;
				vertex.Normal.Y = aimesh->mNormals[i].y;
				vertex.Normal.Z = aimesh->mNormals[i].z;
			}

			/* Process TexCoordinates */
			if (aimesh->mTextureCoords[0] != NULL) {
				vertex.TexCoordinates.X = aimesh->mTextureCoords[0][i].x;
				vertex.TexCoordinates.Y = aimesh->mTextureCoords[0][i].y;
			}

			vertices.PushBack(vertex);
		}

		/* Process Indices */
		for (u32 i = 0; i < aimesh->mNumFaces; i++) {
			aiFace face = aimesh->mFaces[i];
			for (u32 j = 0; j < face.mNumIndices; j++) {
				indices.PushBack(face.mIndices[j]);
			}
		}

		mesh->GenData(&vertices[0], vertices.Length(), &indices[0], indices.Length());
		return mesh;
	}

};


