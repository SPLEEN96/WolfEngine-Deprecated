#pragma once
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw_gl3.h>

#include "..\Core\Window.h"
#include "..\Core\Time.h"

#include "..\Core\Entity.h"
#include "..\Components\EntityComponent.h"
#include "..\Components\Lights\BaseLight.h"
#include "..\Components\Lights\PointLight.h"
#include "..\Components\Lights\DirectionalLight.h"

#include "..\Core\ResourceManagement\ResourceFactory.h"

#include "..\Core\Math\Vector.h"


/* This class was just to test out a UI library that I just discovered called ImgGui. */
/* This is the reason why the code is not profesionnal. */
class GUImanager {
public:
	GUImanager() {

	}
	void Init(Window* window, Entity* root_entity) {
		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window->GetHandle(), true);
		ImGui::StyleColorsClassic();

		for (u32 i = 0; i < root_entity->NumberOfChildren(); i++) {
			entities.PushBack(root_entity->GetChild(i)->GetName());
		}
	}

	void CleanUp() {
		ImGui_ImplGlfwGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void Render(Entity* root_entity, ResourceFactory* rfactory) {
		static Entity* selected_entity;
		static Entity* prev_entity;
		static bool restart = false;
		static EntityComponent* selected_component;
		static COMPONENT_TYPE selected_tab_id = COMP_NULL;
		static Vector3fData color;
		static Transform *transform;
		

		
		ImGui_ImplGlfwGL3_NewFrame();
		ImGui::SetNextWindowSize(ImVec2(500, 600));
		ImGui::Begin("Entity Manager", NULL, ImGuiWindowFlags_NoScrollbar);

		ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		
		/*ImGui::SetNextWindowSize(ImVec2(500, 150));*/
		//if (ImGui::Begin("EntityCreation",NULL,ImGuiWindowFlags_NoCollapse)) {
		//	CreateEntityUI(root_entity, rfactory);

		//	ImGui::End();
		//}
	
		static int curr_item = 0;
		ImGui::Combo("Entities", &curr_item, &entities[0], entities.Length());
		
		
		ImGui::BeginChild(1, ImVec2(500, 570));
		{
			if (prev_entity != selected_entity){
				selected_tab_id = COMP_NULL;
				restart = true;
			}

			prev_entity = selected_entity;
			selected_entity = root_entity->GetChild(curr_item);

			
			if (ImGui::Button("Transform", ImVec2(150, 25))) {
				selected_tab_id = COMP_TRANSFORM;
			}
			for (u32 j = 0; j < selected_entity->NumberOfComponents(); j++) {
				EntityComponent* curr_component = selected_entity->GetComponent(j);
				ImGui::SameLine();
				if (curr_component->GetType() != COMP_LMESH_RENDERER &&
					curr_component->GetType() != COMP_INPUT &&
					curr_component->GetType() != COMP_CAMERA) {
					if (ImGui::Button(curr_component->GetTypeStr(), ImVec2(150, 25))) {
						selected_component = curr_component;
						selected_tab_id = curr_component->GetType();
						break;
					}
				}
			}

			ImGui::NewLine();
			ImGui::BeginChild(2, ImVec2(500, 570));
			{
				switch (selected_tab_id) {
				case COMP_TRANSFORM:
					transform = selected_entity->GetTransform();
					TransformUI(transform, restart);
					break;

				case COMP_MESH_RENDERER:
					ImGui::Text("MeshRenderer");
					break;

				case COMP_LIGHT:
					color.X = ((BaseLight*)selected_component)->GetColor().X();
					color.Y = ((BaseLight*)selected_component)->GetColor().Y();
					color.Z = ((BaseLight*)selected_component)->GetColor().Z();

					LightUI(color, selected_component);
					
					((BaseLight*)selected_component)->SetColor(color);
					break;

				

				default:
					ImGui::Text("");
					break;
				}
			}
			ImGui::EndChild();
		}
		ImGui::EndChild();
		
		ImGui::End();
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		
	}

	void CreateEntityUI(Entity* root_entity, ResourceFactory* rfactory) {
		static char filename[30] = "";
		ImGui::Text("Load a 3D Model:");
		ImGui::InputText("Model filename", filename, 30);

		if (ImGui::Button("GO!", ImVec2(100, 50))) {
			if (!rfactory->FindModelByName(filename))
				rfactory->LoadModelDataInMemory(filename);
			Entity* entity = rfactory->BuildEntityFromModelData(filename, &MAT_WHITE, filename, false);
			root_entity->AddChild(entity);
			entities.PushBack(entity->GetName());
		}
	}

	void TransformUI(Transform* transform, bool& restart) {
		ImGui::Text("TRANSFORM\n\n");
		
		ImGui::Text("Scale:");
		
		static bool lock_axes = false;
		static bool high_precision = false;
		Vector3fData scale = Vector3fData(transform->GetScale().X(), transform->GetScale().Y(), transform->GetScale().Z());
		ImGui::Checkbox("Lock Axes", &lock_axes);
		if (lock_axes) {
			ImGui::Checkbox("High Precision", &high_precision);
			if (high_precision)
				ImGui::DragFloat("s", &scale.X, 0.001f, 0.0001f, 30.f);
			else
				ImGui::SliderFloat("s", &scale.X, 0.0001f, 30.0f);
			scale.Z = scale.Y = scale.X;
		}
		else {
			ImGui::SliderFloat("sX", &scale.X, 0.0001f, 30.0f);
			ImGui::SliderFloat("sY", &scale.Y, 0.0001f, 30.0f);
			ImGui::SliderFloat("sZ", &scale.Z, 0.0001f, 30.0f);
		}
		transform->Scale(scale);

		ImGui::Text("\nPosition:");
		Vector3fData position = Vector3fData(transform->GetPosition().X(), transform->GetPosition().Y(), transform->GetPosition().Z());
		ImGui::SliderFloat("pX", &position.X, 30.0f, -30.0f);
		ImGui::SliderFloat("pY", &position.Y, -30.0f, 30.0f);
		ImGui::SliderFloat("pZ", &position.Z, -30.0f, 30.0f);

		transform->SetPosition(position);

		ImGui::Text("\nRotation:");
		static float angle = 0.f; 
		Vector3fData axes = Vector3fData(0.f, 0.f, 0.f);
		static bool x = false, y = false, z = false;
		static float speed = 0.f;
		static bool time = false;
		if (restart) {
			angle = transform->GetCurrAngle();
			x = y = z = time = false;
			speed = 0.f;
			restart = false;
		}

		ImGui::PushItemWidth(100);
		ImGui::SliderFloat("Angle", &angle, 0.f, 360.f); ImGui::SameLine();

		ImGui::Checkbox("rX", &x); ImGui::SameLine();
		ImGui::Checkbox("rY", &y); ImGui::SameLine();
		ImGui::Checkbox("rZ", &z);

		ImGui::Checkbox("Turn Over Time", &time); ImGui::SameLine();
		ImGui::SliderFloat("Speed", &speed, 0.f, 6.f);

		if (x)axes.X = 1;
		if (y)axes.Y = 1;
		if (z)axes.Z = 1;

		if (!x && !y && !z)
			return;
		if (time) {
			angle = 45.f;
			transform->Rotate(Time::GetTime()*angle*speed, axes);
			return;
		}
		transform->Rotate(angle, axes);
		angle = transform->GetCurrAngle();
	}



	void ColorUI(Vector3fData &color) {
		ImGui::Text("COLOR");
		ImGui::SliderFloat3("color (r,g,b)", &color.X, 0.0f, 1.0f);
		ImGui::ColorEdit3("clear color", &color.X);
	}

	void LightUI(Vector3fData &color, EntityComponent* selected_component) {
		ColorUI(color);

		LIGHT_TYPES light_type = ((BaseLight*)selected_component)->GetLightType();
		if (light_type == LIGHT_POINT) {
			ImGui::NewLine();
			PointLightUI(((PointLight*)selected_component));
		}
		else {

		}
	}
	void PointLightUI(PointLight* curr_light) {
		ImGui::Text("POINT-LIGHT");
		static int curr_range = 0;
		const char* ranges[] = { "7","20","32","50","100","600" };
		ImGui::Combo("LightRange", &curr_range, ranges, 6);
		curr_light->SetRange((POINT_RANGE)curr_range);
	}

private:
	DynamicBuffer<const char*> entities;
};



//// Animate a simple progress bar
//static float progress = 0.0f, progress_dir = 1.0f;
//
//progress += progress_dir * 0.4f * ImGui::GetIO().DeltaTime;
//if (progress >= +1.1f) { progress = +1.1f; progress_dir *= -1.0f; }
//if (progress <= -0.1f) { progress = -0.1f; progress_dir *= -1.0f; }
//
//
//// Typically we would use ImVec2(-1.0f,0.0f) to use all available width, or ImVec2(width,0.0f) for a specified width. ImVec2(0.0f,0.0f) uses ItemWidth.
//ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));
//ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
//ImGui::Text("Progress Bar");
//
//float progress_saturated = (progress < 0.0f) ? 0.0f : (progress > 1.0f) ? 1.0f : progress;
//char buf[32];
//sprintf(buf, "%d/%d", (int)(progress_saturated * 1753), 1753);
//ImGui::ProgressBar(progress, ImVec2(0.f, 0.f), buf);