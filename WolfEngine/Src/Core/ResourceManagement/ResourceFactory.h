#pragma once

#include "Loaders\ModelLoader.h"
#include "Loaders\ShaderSourceLoader.h"
#include "Loaders\ImageLoader.h"

#include "DataTypes\DynamicBuffer.h"
#include "DataTypes\Model.h"

class ResourceFactory {
public:
	ResourceFactory() {}
	~ResourceFactory() {
		for (u32 i = 0; i < m_loaded_models.Length(); i++)
			delete(m_loaded_models[i]);
		m_loaded_models.Clear();
	}

	void LoadModelDataInMemory(const char* filename) {
		m_loaded_models.PushBack(m_mloader.LoadModel(filename));
	}

	/* Create an entity with a mesh renderer using a model previously loaded in memory */
	Entity* BuildEntityFromModelData(const char model_name[], Material* material, const char entity_name[], bool entityIsStatic) {
		Entity* model_entity = new Entity(entity_name, entityIsStatic);
		Model* model = FindModelByName(model_name);

		for (u32 i = 0; i < model->meshes.Length(); i++) {
			Entity* child = new Entity("child", entityIsStatic);
			Mesh* mesh = new Mesh(*model->meshes[i]->GetData());
			child->AddComponent(new MeshRenderer(mesh, material));
			model_entity->AddChild(child);
		}

		return model_entity;
	}
	Model* FindModelByName(const char model_name[]) {
		for (u32 i = 0; i < m_loaded_models.Length(); i++) {
			if (strcmp(m_loaded_models[i]->name, model_name) == 0)
				return m_loaded_models[i];
		}
		//OutputErrorMsg("RessourceFactory", ERR_NONAME, "No Model with that name exist in memory.");
		return NULL;
	}

private:
	DynamicBuffer<Model*> m_loaded_models;
	
	/* Still not implemented... */
    DynamicBuffer<GLuint> m_loaded_shd_programs;
	DynamicBuffer<GLuint> m_loaded_textures;


	ModelLoader m_mloader;
	ShaderSourceLoader m_ssloader;
	ImageLoader m_iloader;
};


