#include "Engine.h"
#include "Sphere.h"

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
	glEnable(GL_DEPTH_TEST); //Z-buffer
	float alpha = 0.1;
	while (!glfwWindowShouldClose(window))
	{
		this->camera->useProjection();
		this->camera->useView();
		alpha += 0.1;
		std::cout << alpha << std::endl;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (DrawableObject* object : this->objects) {
			object->rotate(alpha);
			object->render();
		}

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);

	this->status;
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}

void Engine::createObjects()
{
	const char* vertex_shader = "c:/users/ajrac/source/repos/ajraa/zpgprojekt/zpgprojekt/shaders/vertex/sphere.ver";
	const char* fragment_shader = "c:/users/ajrac/source/repos/ajraa/zpgprojekt/zpgprojekt/shaders/fragment/sphere.frag";

	//const char* vertex_shader = "C:/Users/LenovoYoga/source/repos/ZPGProjekt/ZPGProjekt/Shaders/Vertex/model.ver";
	//const char* fragment_shader = "C:/Users/LenovoYoga/source/repos/ZPGProjekt/ZPGProjekt/Shaders/Fragment/shader.frag";
	//const char* fragment_shader2 = "C:/Users/LenovoYoga/source/repos/ZPGProjekt/ZPGProjekt/Shaders/Fragment/shader2.frag";

	float points[] = { // x, y, z, r, g, b, a
		-.5f, -.5f, 10.0f, 1, 0, 0, 1,
		-.5f, .5f, 10.0f, 0, 1, 0, 1,
		.5f, .5f, 10.0f, 0, 0, 1, 1,
	};

	float points2[] = {
		0.5f, 0.5f, 1.0f, 1, 0, 0, 1,
		0.5f, -0.5f, 1.0f, 0, 1, 0, 1,
		-0.5f, -0.5f, 1.0f, 1, 0, 1, 1
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

	this->objects.push_back(new DrawableObject(new Shader(vertex_shader, fragment_shader), new Model(sphere, sizeof(sphere), 2880)));
	//this->objects.push_back(new DrawableObject(new Shader(vertex_shader, fragment_shader), new Model(points2, sizeof(points2))));

	for (DrawableObject* object : this->objects) {
		this->camera->addShader(object->getShader());
		object->initialize();
	}
}

void Engine::initialization()
{
	this->camera = new Camera();

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
