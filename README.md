# WolfEngine :wolf: (name subject to change)
Realtime Rendering Engine in C++ and OPENGL (started 05/17/2018) <br/>
Librairies: glad, glm, glfw, stb_images, assimp, imgui

## Motivation
This project puts into practice everything I’ve learned in Software Engineering <br/>
over the last few years and it's helping me learn OpenGL. <br/>
Suffice to say that this is a work in progress!

## Screenshots
![Alt text](/screenshots/wolf_engine_01.png?raw=true "Transform component")
![Alt text](/screenshots/wolf_engine_02.png?raw=true "Light component")
![Alt text](/screenshots/wolf_engine_03.png?raw=true "Light color UI")

## Features (still barebones...)
 * Entity Component (EC)
 * Forward Rendering
 * Model Loading (can load up to 10k entities in less than 3 seconds)
 * Phong Shaders
 * UI (barely implemented)
 * Ease of use
 * Code Extensibility
 * An object wrapper for every library that I used
 * And more to come!
## Getting Started

### Config
In order for the engine to work, you need to:
* Change the VisualStudio target platform to win32<br/>
  - right-clicking on the project and choose **Properties**
  - click on the **Configuration Manager** at the top of the **Property Pages** dialog box
  ![Alt text](/screenshots/target_platform_1.png?raw=true "Configuration Manager")
  - change the **Active solution platform** to **x86** and click on close
  ![Alt text](/screenshots/target_platform_02.png?raw=true "Configuration Manager")
  - be sure that the selected platform is **Active(Win32)**
  ![Alt text](/screenshots/target_platform_03.png?raw=true "Configuration Manager")
  - and click on apply at the bottom of the **Property Pages** dialog box
* Change the project directory in the file <br/>
/Src/Core/ResourceManagement/Loaders/ResourceLoader.h
![Alt text](/screenshots/project_dir.png?raw=true "PROJECT_DIR")
* And compile the solution using visual studio

That's it! You are now ready to use it!

### How to use it
#### The Basics
In order to draw something on the screen, you have to write some code in a **Scene object**. <br/>
One called **TestScene** (/Src/TestScene/TestScene.cpp) comes with the project but you can create your own.
The "code" you have to write is an amalgam of **Entities**. An **Entity** is foremost an abstract concept; anything that is drawn, or not, in the scene.<br/>
What defines an Entity is its **Components**.
##### Some useful components
+ Transform (every entity has one per default)
+ MeshRenderer
+ LightMeshRenderer (for debugging purposes)
+ Camera (only one per scene)
+ DirectionalLight (only one per scene)
+ PointLight
+ KeyboardHandler/KeyboardMovement

Once an entity is defined, you need to add it to the root entity of the scene.<br/>
For each frame, the **Core Engine** updates and renders the **Root Entity**, all its **Child** and all its **Child Components**.<br/>

So, to recap, in order to draw something on the screen, you need to:<br/>
* Create an **Entity** and give it a name<br/>
```c++
Entity *some_light =new Entity("light_01");
```
* Add some **Components**<br/>
```c++
some_light->AddComponent(new PointLight(some, constructor, arguments));
some_light->AddComponent(new KeyboardMovement(some, other, arguments));
```
* Transform the entity with its **Transform Component** (optional)<br/>
```c++
/* Note that scaling or rotation doesn't affect a light */
some_light->GetTransform()->Scale(Vector3f(2.f, 1.f, 10.f)); /* the vector3f represent the 3 axis x,y,z */
some_light->GetTransform()->SetPosition(Vector3f(0.f, -1.3f, 0.f));
some_light->GetTransform()->Rotate(45.f, Vector3f(0.f, 1.f, 0.f)); /* rotate with an angle of 45 degree on the y axis */
```
* And add it to the **Root Entity** of the **Scene**<br/>
```c++
m_root_entity->AddChild(some_light);
```
And just like that, you have a light drawn on the screen! :smiley: <br/>
A test scene exemple and somes basic entities comes with the project.

#### Loading a 3d model
The **ResourceFactory** is used to load data(3D models, shaders, textures, etc..) in memory and keep a reference for future use.<br/>
A **ResourceFactory** handle comes in the form of an argument in the **Init()** method of the **Scene**.<br/>
It can be used to load a **Model** in memory <br/>
and then build an **Entity** containing a **Material** and an reference of the said **Model**. :dizzy_face: <br/>
Trust me, it is simpler than it looks! :joy: <br/>
Once a **Model** is loaded in memory, you can build as many entities as you want with it.
```c++
/* The initialization method of the Scene object TestScene */
void TestScene::Init(ResourceFactory* rfactory_handle){
  rfactory_handle->LoadModelDataInMemory("filename(without the full path)");  /* Load the model once... */
  for(size_t i=0; i<1000; i++){                                               /* ...use it how many times that you want! */
    Entity *tmp_entity  =new Entity();
    tmp_entity  =rfactory_handle->BuildEntityFromModelData("model filename", &some_material, "entity name");
    tmp_entity->Translate(Vector3f(i*i,0.f,0.f)); /* translate each entities on the x axis to draw them side by side */
    m_root_entity->AddChild(tmp_entity); /* add the entity to the root entity */
  }
}
```

You can find a list of **Material** in the file **/Src/Rendering/Material.h** <br/>
Some 3D **Models** come with the project in the folder **/Resources/Models/** <br/>

Remember that you only have to enter the filename in the **LoadModelDataInMemory()** method!<br/>
So, for the model /Project/Full/Path/Resources/Models/Xenomorph.obj the method will look like this:
```c++
rfactory_handle->LoadModelDataInMemory("Xenomorph.obj");
Entity *xeno  =rfactory->BuilEntityFromModelData("Xenomorph.obj", &MAT_OBSIDIAN, "xenomorph entity");
m_root_entity->AddChild(xeno);
```

#### Add some Lighting to the scene :star2:
A light is just an **Entity** with a light component.
There are three components(more to come) that you can use for a light **Entity**:
* DirectionalLight
* PointLight
* LightMeshRenderer

##### DirectionalLight :sun_with_face:
A **Directional Light** is a  distant light source modeled to be very VERY far away. Because the source is **infinitely** far away, the rays coming from the light are nearly parallel to each other, i.e. the light is coming from only one direction. <br/>
Hence the name **Directional light**. Because of this property, every object in the scene casts the same shadow. <br/>
This type of light is used to create effect such as sunlight. <br/>
![Alt text](/screenshots/directional.png?raw=true "Directional") <br/>
*img source: http://learningwebgl.com/lessons/lesson07/directional.png* <br/><br/>

The constructor of a DirectionalLight looks like this:
```c++
DirectionalLight(RenderingEngineData* rdata, Vector3f color, float intensity, Vector3f target) 
```
Where
+ rdata is an handle to to the **RenderingEngine Data**.<br/> 
It is use to automatically add the object to the list of lights of the **RenderingEngine**.<br/>
This list is then used each frames to render all the lights.
+ color is the color of the light
+ intensity is the force of the light
+ target is the direction of the light<br/><br/>

So, this is what the instantiation of a **DirectionalLight** pointing forward on the z axis looks like:
```c++
Entity *sunlight = new Entity("sun",false);                          /* first create an entity */
sunlight->GetTransform()->SetPosition(Vector3f(0.f, 5.f, -5.f));     /* set its position */
sunlight->AddComponent(new DirectionalLight(RenderingEngine::GetInstance().GetDataHandle(),Vector3f(0.5f), 0.1f, Vector3f(0.f, 0.f, 1.f)));
```
![Alt text](/screenshots/directional_before_after.png?raw=true "Before/After") <br/>
##### PointLight :high_brightness:
##### SpotLight :flashlight:
Will be implemented in the (not too) distant future...
### Final Point
Fear not! Once the project is set-up with the TestScene exemple, all of what you just red will make sense!

## Future of the project (not in order)
 * Arch Linux/CMake support
 * Quaternions for camera rotation
 * No librairies for matrix calculation
 * Data Oriented Design (Entity Component System or ECS)
 * Better UI implementation
 * Spotlight
 * Trully generic Shader Class
 * Blinn-Phong Shaders
 * Shadow Casting
 * Normal Mapping
 * And ultimately, Physically Based Rendering (PBR)
