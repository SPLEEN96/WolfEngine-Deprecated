#include "TestScene.h"

void TestScene::Init(ResourceFactory* rfactory_handle) {
	/* Load some 3D models */
	rfactory_handle->LoadModelDataInMemory("cube.3ds");
	rfactory_handle->LoadModelDataInMemory("Wolf.obj");



	/* Create a plane Entity with the cubel.3ds Model loaded*/
	Entity *plane = rfactory_handle->BuildEntityFromModelData("cube.3ds", &MAT_EMERALD, "plane", false);
	plane->GetTransform()->Scale(Vector3f(6.f, 0.1f, 10.f));             /* Scale it to make it look like a Plane*/
	plane->GetTransform()->SetPosition(Vector3f(0.f, -1.3f, 0.f));

	/* Create a Wolf Model Entity */
	Entity *model = rfactory_handle->BuildEntityFromModelData("Wolf.obj", &MAT_WHITE, "Wolf", false);

	/* Create a DirectionalLight */
	Entity *sunlight = new Entity("sun", false);
	sunlight->GetTransform()->SetPosition(Vector3f(0.f, 5.f, -5.f));
	sunlight->AddComponent(new DirectionalLight(RenderingEngine::GetInstance().GetDataHandle(), Vector3f(0.5f), 0.1f, Vector3f(0.f, 0.f, 1.f)));

	/* Create a Blue PointLight */
	Entity *light_01 = new Entity("light_01", false);
	light_01->GetTransform()->SetPosition(Vector3f(0.f, 0.f, 2.f));
	light_01->AddComponent(new PointLight(RenderingEngine::GetInstance().GetDataHandle(), Vector3f(0.f, 0.f, 1.f), 1.f, RANGE_7));
	light_01->AddComponent(new LightMeshRenderer((PointLight*)(light_01->GetComponent(0))));

	/* Create a Red PointLight */
	Entity *light_02 = new Entity("light_02", false);
	light_02->GetTransform()->SetPosition(Vector3f(-0.8f, -1.f, 0.f));
	light_02->AddComponent(new PointLight(RenderingEngine::GetInstance().GetDataHandle(), Vector3f(1.f, 0.f, 0.f), RANGE_20));
	light_02->AddComponent(new LightMeshRenderer(((PointLight*)(light_02->GetComponent(0)))));

	/* Create the Controller Entity with a Camera */
	Entity* Controller = new Entity("Controller");
	Controller->GetTransform()->SetPosition(Vector3f(0.f, 2.f, -3.5f));
	Controller->AddComponent(new KeyboardMovement());
	Controller->AddComponent(new Camera(RenderingEngine::GetInstance().GetDataHandle(), Controller, m_screen_width, m_screen_height));


	/* Add all the entities to the root entity */
	m_root_entity->AddChild(Controller);
	m_root_entity->AddChild(sunlight);
	m_root_entity->AddChild(plane);
	m_root_entity->AddChild(model);
	m_root_entity->AddChild(light_01);
	m_root_entity->AddChild(light_02);

	/* == Uncomment to test == */
	/* Demonstration of how fast loading 1000 entities is */
	//for (u16 i = 0; i < 1000; i++) {
	//	Entity* tmp_entity = rfactory_handle->BuildEntityFromModelData("Wolf.obj", &MAT_RUBY, "wolf", true);
	//	tmp_entity->GetTransform()->Translate(Vector3f(i, 0.f, 0.f)); /* Translate each entities on the x axis to draw them side by side */
	//	m_root_entity->AddChild(tmp_entity); /* Add the entity to the root entity */
	//}
}


void TestScene::Input(float dTime, KeyboardState* curr_keyboard_state, MouseState* curr_mouse_state) {
	m_root_entity->Input(dTime, curr_keyboard_state, curr_mouse_state);
}

void TestScene::Update(float dTime) {
  	m_root_entity->Update(dTime);
}






TestScene::~TestScene() {
	if (m_root_entity != NULL)
		delete m_root_entity;
}