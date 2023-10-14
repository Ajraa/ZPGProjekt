#include "Engine.h"

Engine::~Engine()
{
	for (DrawableObject* object : this->objects)
		delete object;
}

void Engine::start()
{
	this->initialization();
	this->createObjects();
	this->run();
}

void Engine::run()
{
	while (!glfwWindowShouldClose(window))
	{

		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//this->objects[0]->rotate(5);
		//this->objects[1]->rotate(20);
		for (DrawableObject* object : this->objects) {
			//object->rotate(5);
			object->render();
		}

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);

	this->status;
	//glGetProgramiv(shader->getShaderProgram(), GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		//glGetProgramiv(shader->getShaderProgram(), GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		//glGetProgramInfoLog(shader->getShaderProgram(), infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}

void Engine::createObjects()
{
	const char* vertex_shader = "c:/users/ajrac/source/repos/ajraa/zpgprojekt/zpgprojekt/shaders/vertex/model.ver";
	const char* fragment_shader =  "c:/users/ajrac/source/repos/ajraa/zpgprojekt/zpgprojekt/shaders/fragment/shader.frag";
	const char* fragment_shader2 =  "c:/users/ajrac/source/repos/ajraa/zpgprojekt/zpgprojekt/shaders/fragment/shader2.frag";
	const char* fragment_shader3 = "c:/users/ajrac/source/repos/ajraa/zpgprojekt/zpgprojekt/shaders/fragment/model.frag";

	//const char* vertex_shader = "C:/Users/LenovoYoga/source/repos/ZPGProjekt/ZPGProjekt/Shaders/Vertex/model.ver";
	//const char* fragment_shader = "C:/Users/LenovoYoga/source/repos/ZPGProjekt/ZPGProjekt/Shaders/Fragment/shader.frag";
	//const char* fragment_shader2 = "C:/Users/LenovoYoga/source/repos/ZPGProjekt/ZPGProjekt/Shaders/Fragment/shader2.frag";

	float points[] = { // x, y, z, r, g, b, a
		-.5f, -.5f, .0f, 1, 1, 0, 1,
		-.5f, .5f, .0f, 1, 0, 0, 1,
		.5f, .5f, .0f, 0, 0, 0, 1,
		.5f, -.5f, .0f, 0, 1, 0, 1
	};

	float points2[] = {
		0.5f, 0.5f, 0.0f, 0, 0, 0, 1,
		0.5f, -0.5f, 0.0f, 0, 1, 1, 1,
		-0.5f, -0.5f, 0.0f, 1, 0, 1, 1
	};

	/*float points[] = {
	-0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f
	};

	float points2[] = {
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
	};*/

	this->objects.push_back(new DrawableObject(new Shader(vertex_shader, fragment_shader3), new Model(points, sizeof(points)), false));
	this->objects.push_back(new DrawableObject(new Shader(vertex_shader, fragment_shader3), new Model(points2, sizeof(points2)), false));

	for (DrawableObject* object : this->objects) {
		object->initialize();
	}
}

void Engine::initialization()
{
	// Projection matrix : 45� Field of View, 4 : 3 ratio, display range : 0.1 unit < -> 100 units
	this->Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);

	// Camera matrix
	this->View = glm::lookAt(
		glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	// Model matrix : an identity matrix (model will be at the origin)
	this->ViewModel = glm::mat4(1.0f);

	glfwSetErrorCallback(Callback::error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();


	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);
}
