#include "Engine.h"
#include "Sphere.h"
#include "Models/suzi_flat.h"

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
	
	float alpha = 0;
	float x;
	float y;
	float x2;
	float y2;
	float angle = 0.0f;
	float centerX = 3.0f;
	float centerY = 0.0f;
	float radius = 30.0f;
	float radius2 = 10.0f;

	while (!glfwWindowShouldClose(window))
	{
		this->processUserInput();

		//this->camera->update();
		alpha += 0.5;
		angle += 0.01f;
		x = centerX + radius * cos(angle);
		y = centerY + radius * sin(angle);
		x2 = x + radius2 * cos(angle);
		y2 = y + radius2 * sin(angle);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		this->objects[0]->scale(3.0);
		this->objects[2]->scale(0.5f);
		this->objects[0]->translate(centerX, centerY, 0.f);
		this->objects[1]->translate(x, y, 0.f);
		this->objects[2]->translate(x2, y2, 0.f);
		
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
	const char* vertex_shader = "shaders/vertex/sphereLight.ver";
	const char* constant = "shaders/fragment/shader.frag";
	const char* lambert = "shaders/fragment/lambert.frag";
	const char* phong = "shaders/fragment/phong.frag";
	const char* blinn = "shaders/fragment/blinn.frag";
	
	Material* pearl = new Material(glm::vec3(0.25, 0.20725, 0.20725), glm::vec3(1, 0.829, 0.829), glm::vec3(0.296648, 0.296648, 0.296648), 0.088);
	DrawableObject* sphere1 = new DrawableObject(new Shader(vertex_shader, phong, this->camera), new Model(sphere, sizeof(sphere), (sizeof(sphere) / (6 * 4))));
	sphere1->setMaterial(pearl);
	this->objects.push_back(sphere1);
	DrawableObject* sphere2 = new DrawableObject(new Shader(vertex_shader, phong, this->camera), new Model(sphere, sizeof(sphere), (sizeof(sphere) / (6 * 4))));
	sphere2->setMaterial(pearl);
	this->objects.push_back(sphere2);
	DrawableObject* sphere3 = new DrawableObject(new Shader(vertex_shader, phong, this->camera), new Model(sphere, sizeof(sphere), (sizeof(sphere) / (6 * 4))));
	sphere3->setMaterial(pearl);
	this->objects.push_back(sphere3);

	for (DrawableObject* object : this->objects) {
		object->initialize();
		object->addLight(this->light);
	}
}

void Engine::initialization()
{
	this->camera = new Camera();
	this->light = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0), 1, 1);

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

void Engine::processUserInput()
{

	int previousWidth = 800;
	int previousHeight = 600;
	double x, y;

	glfwGetCursorPos(window, &x, &y);
	this->camera->moveCursor(x, y);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		this->camera->moveForward();
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		this->camera->moveBackwards();
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		this->camera->moveLeft();
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		this->camera->moveRight();
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		this->camera->moveUp();
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		this->camera->moveDown();
	}

	int currentWidth, currentHeight;
	glfwGetFramebufferSize(window, &currentWidth, &currentHeight);
	if (currentWidth != previousWidth || currentHeight != previousHeight)
	{
		previousHeight = currentHeight;
		previousWidth = currentWidth;
		glViewport(0, 0, currentWidth, currentHeight);
		this->camera->setProjection(currentHeight, currentWidth);
	}
}
