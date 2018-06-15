# WolfEngine (name subject to change)
Realtime Rendering Engine in C++ and OPENGL (started 05/17/2018) <br/>
Librairies used : glad, glm, glfw, stb_images, assimp, imgui

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
 * Model Loading
 * Phong Shaders
 * UI (barely implemented)
 * Ease of use
 * Code Extensibility
 * An object wrapper for every library that I used
 * And more to come!
## Getting Started

### Config
In order for the engine to work, you need to:
* Have a graphic card that supports OpenGL 3.3
* Update your VisualStudio to its latest version
* Change the VisualStudio target platform to Win32<br/>
  - right-click on the project in VisualStudio and choose **Properties**
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
#### The Basics :book:
In order to draw something on the screen, you have to write some code in a **Scene object** (/Src/Core/Scene.h). <br/>
One called **TestScene** (/Src/TestScene/TestScene.cpp) comes with the project but you can create your own.
The "code" you have to write is an amalgam of **Entities**. An **Entity** (/Src/Core/Entity.h) is foremost an abstract concept; anything that is drawn, or not, in the scene.<br/>
What defines an Entity is its **Components** (/Src/Components/EntityComponent.h).
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
some_light->GetTransform()->Scale(Vector3f(2.f, 1.f, 10.f)); /* The vector3f represent the 3 axis x,y,z */
some_light->GetTransform()->SetPosition(Vector3f(0.f, -1.3f, 0.f));
some_light->GetTransform()->Rotate(45.f, Vector3f(0.f, 1.f, 0.f)); /* Rotate with an angle of 45 degree on the y axis */
```
* And add it to the **Root Entity** of the **Scene**<br/>
```c++
m_root_entity->AddChild(some_light);
```
And just like that, you have a light drawn on the screen! <br/>
A test scene exemple and somes basic entities comes with the project.

#### The Camera :camera:
It is required to add a **Camera** to the **Scene**.
The constructor looks like this:
```c++
Camera(RenderingEngineData* rdata, Entity* parent,
		const float& screen_width, const float& screen_height, const float &fov = 45.f, 
		const float &zNear = 0.01f, const float &zFar = 300.f, 
		Vector3f target = Vector3f(0.f, 0.f, 1.f))
```
Where
+ rdata is a handle to to the **RenderingEngine Data**.<br/> 
It is used to automatically add the **Camera** to the **RenderingEngine**.<br/>
+ parent is the entity containing it (Remember that **Camera** is an **EntityComponent**).
+ screen_width and screen_height are the width and height of the **Window**. <br/>
You can access them with the member attributes of the **Scene** m_screen_width and m_screen_height.
+ You don't have to play with the rest of the arguments, but if you do,
  - fov is the **Field of View** angle of the camera. It determines how wide you can see in the **Scene**.
  - zNear is the front of the **Clipping Plane** of the **Camera**. It determines how close an object is from the **Camera** before being **Clipped**(not drawned).
  - zFar is the back of the **Clipping Plane** of the **Camera**. It determines how far an object can be from the **Camera** before being **Clipped**(not drawned).
  - target is the direction of the **Camera**. <br/><br/>

So, this is what the instantiation of a **Camera** looks like:
```c++
Entity* Controller = new Entity("Controller");
Controller->AddComponent(new Camera(RenderingEngine::GetInstance().GetDataHandle(), Controller, m_screen_width, m_screen_height));
Controller->AddComponent(new KeyboardMovement()); /* If you want to be able to move with the keyboard */
```

#### Loading a 3d model :floppy_disk:
The **ResourceFactory** (/Src/Core/ResourceManagement/ResourceFactory.h) is used to load data(3D models, shaders, textures, etc..) in memory and to keep a reference for future use.<br/>
A **ResourceFactory** handle comes in the form of an argument in the **Init()** method of the **Scene**.<br/>
It can be used to load a **Model** in memory <br/>
and then build an **Entity** containing a **Material** and an reference of the said **Model**. <br/>
Trust me, it is simpler than it looks! <br/>
Once a **Model** is loaded in memory, you can build as many entities as you want with it.
```c++
/* The initialization method of the Scene object TestScene */
void TestScene::Init(ResourceFactory* rfactory_handle){
  rfactory_handle->LoadModelDataInMemory("filename(without the full path)");  /* Load the model once... */
  
  for(size_t i=0; i<1000; i++){                                               /* ...use it how many times that you want! */
    Entity *tmp_entity =rfactory_handle->BuildEntityFromModelData("model filename", &some_material, "entity name");
    tmp_entity->GetTransform()->Translate(Vector3f(i*i,0.f,0.f)); /* Translate each entities on the x axis to draw them side by side */
    m_root_entity->AddChild(tmp_entity); /* Add the entity to the root entity */
  }
}
```

You can find a list of **Material** in the file **/Src/Rendering/Material.h** <br/>
Some 3D **Models** come with the project in the folder **/Resources/Models/** <br/>

Remember that you only have to enter the filename in the **LoadModelDataInMemory()** method.<br/>
So, for the model /Project/Full/Path/Resources/Models/Wolf.obj the method will look like this:
```c++
rfactory_handle->LoadModelDataInMemory("Wolf.obj");
Entity *model  =rfactory->BuilEntityFromModelData("Wolf.obj", &MAT_OBSIDIAN, "wolf entity");
m_root_entity->AddChild(model);
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

The constructor of a **DirectionalLight** looks like this:
```c++
/* Found in /Src/Components/Lights/DirectionalLight.h */
DirectionalLight(RenderingEngineData* rdata, Vector3f color, float intensity, Vector3f target);
```
Where
+ rdata is a handle to to the **RenderingEngine Data**.<br/> 
It is use to automatically add the object to the list of lights of the **RenderingEngine**.<br/>
This list is then used each frames to render all the lights.
+ color is the color(r,g,b) of the light.
+ intensity is the force of the light (it looks better when the intensity is lower).
+ target is the direction of the light.<br/><br/>

So, this is what the instantiation of a **DirectionalLight** pointing forward on the z axis looks like:
```c++
Entity *sunlight = new Entity("sun", false);                         /* First create an entity */
sunlight->GetTransform()->SetPosition(Vector3f(0.f, 5.f, -5.f));     /* Set its position */
sunlight->AddComponent(new DirectionalLight(RenderingEngine::GetInstance().GetDataHandle(),Vector3f(0.5f), 0.1f, Vector3f(0.f, 0.f, 1.f)));
m_root_entity->AddChild(sunlight);                                   /* Don't forget to add it to the RootEntity! */
```
![Alt text](/screenshots/directional_before_after.png?raw=true "Before/After") <br/>
##### PointLight :high_brightness:
A **PointLight** is a point in 3D space that emits rays in all directions. The light rays fade out quadratically until they meet the **Range** of the **PointLight** where the **Intensity** is set to zero. This process is called **Attenuation**. <br/>
They are the most commonly used light effects in a scene. <br/>
![Alt text](/screenshots/pointlight.png?raw=true "PointLight") <br/>
*img source: http://www.scratchapixel.com/images/upload/shading-intro/shad-sphericallight2.png?*

The constructor of a **PointLight** looks like this:
```c++
/* found in /Src/Components/Lights/PointLight.h */
PointLight(RenderingEngineData* rdata, Vector3f color, float intensity =1.f, const POINT_RANGE &range =RANGE_7);
```
Where
+ rdata is a handle to to the **RenderingEngine Data**.<br/> 
It is used to automatically add the object to the list of lights of the **RenderingEngine**.<br/>
This list is then used each frames to render all the lights.
+ color is the color(r,g,b) of the light.
+ intensity is the force of the light (you can leave it to 1).
+ range is an **Enum** found with the definition of **PointLight** and determines the **Range** of the light.
  - Some range example: RANGE_7, RANGE_20, RANGE_32,..

So, this is what the instantiation of a **PointLight** with a red color, a range of 20 and a position of (x=-1, y=0.5, z=0) looks like: 
```c++
Entity *light = new Entity("light", false);                          /* First create an entity */
light->GetTransform()->SetPosition(Vector3f(-1.f, 0.5f, 0.f));       /* Set its position */
light->AddComponent(new PointLight(RenderingEngine::GetInstance().GetDataHandle(),Vector3f(1.f,0.f,0.f), RANGE_20);
m_root_entity->AddChild(light);                                     /* Don't forget to add it to the RootEntity! */
```
![Alt text](/screenshots/pointlight_ex.png?raw=true "Before/After") <br/>

##### SpotLight :flashlight:
Will be implemented in the (not too) distant future...
### Final Point
Fear not! Once the project is set-up with the TestScene exemple, all of what you just red will make sense!
Also, don't forget to look at the terminal for errors.

## Future of the project (not in order)
 * Arch Linux/CMake support
 * Batch Rendering
 * Forward**Plus** Rendering or Deferred Rendering
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
