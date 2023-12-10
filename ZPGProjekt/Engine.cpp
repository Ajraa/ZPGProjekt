#include "Engine.h"
#include "Sphere.h"
#include "Models/suzi_flat.h"
#include "Models/plain.h"
#include "Models/gift.h"
#include "Models/tree.h"
#include "Models/bushes.h"

const char* vertex_shader = "shaders/vertex/sphereLight.vert";
const char* constant = "shaders/fragment/shader.frag";
const char* lambert = "shaders/fragment/lambert.frag";
const char* phong = "shaders/fragment/phong.frag";
const char* blinn = "shaders/fragment/blinn.frag";
const char* phongReflector = "shaders/fragment/phongReflector.frag";

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
std::vector<float> xs;
std::vector<float> ys;
std::vector<float> zs;

void Engine::run()
{
	glEnable(GL_DEPTH_TEST); //Z-buffer
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	
	float alpha = 0.f;
	float beta = 0.f;
	float x = 0;

	const char* vertex = "shaders/vertex/skybox.vert";
	const char* fragment = "shaders/fragment/skybox.frag";
	Shader* shader = new Shader(vertex, fragment, this->camera);
	DrawableObject* sc = new DrawableObject(shader);
	sc->initialize();

	glm::mat4 A = glm::mat4(glm::vec4(-1.0, 3.0, -3.0, 1.0),
		glm::vec4(3.0, -6.0, 3.0, 0),
		glm::vec4(-3.0, 3.0, 0, 0),
		glm::vec4(1, 0, 0, 0));

	float t = 0.5f;
	float delta = 0.01;
	int currentBez = 0;

	while (!glfwWindowShouldClose(window))
	{
		this->processUserInput();

		if (Reflector* v = dynamic_cast<Reflector*>(this->lights[0])) {
			v->updatePosition(this->camera->getPosition());
		}

		//this->camera->update();
		//komenty
		alpha += 1;
		beta += 0.1;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		sc->translate(this->camera->getPosition());
		sc->render();	

		if (this->bezier.size() > 0) {
			glm::mat4x3 B = bezier[currentBez];
			glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);
			glm::vec3 p = parameters * A * glm::transpose(B);

			this->objects[1]->translate(p);
		}

		if (bezier.size() > 0) {
			if(t > 1.0f)
				if (bezier.size() > currentBez + 1) {
					currentBez++;
					t = 0;
				}
				else {
					delta *= -1;
				}

			if(t < 0.0f)
				if (currentBez > 0) {
					currentBez--;
					t = 1;
				}
				else {
					delta *= -1;
				}

			t += delta;
		}
		
		int i = 0;
		for (DrawableObject* object : this->objects) {
			glStencilFunc(GL_ALWAYS, object->getTextureId(), 0xFF);
			object->translate(xs[i], ys[i], zs[i]);
			if ( i == 0)
				this->objects[i]->scale(300);
			object->render();
			i++;
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
	Material* pearl = new Material(glm::vec3(0.25, 0.20725, 0.20725), glm::vec3(1, 0.829, 0.829), glm::vec3(0.296648, 0.296648, 0.296648), 0.088);
	DrawableObject* pl = new DrawableObject(new Shader(vertex_shader, phong, this->camera), new Model(plain, sizeof(plain), (sizeof(plain) / (6 * 4))));
	pl->setTexture("textures/grass.png");
	pl->setMaterial(pearl);
	this->objects.push_back(pl);
	xs.push_back((float)0);
	ys.push_back((float)0);
	zs.push_back((float)0);

	DrawableObject* house = new DrawableObject(new Shader(vertex_shader, phong, this->camera), new Model("objs/zombie.obj", "Textures/zombie.png"));
	house->setMaterial(pearl);
	this->objects.push_back(house);
	xs.push_back((float)10);
	ys.push_back((float)0);
	zs.push_back((float)10);

	/*DrawableObject* house = new DrawableObject(new Shader(vertex_shader, phong, this->camera), new Model("objs/house.obj", "Textures/house.png"));
	house->setMaterial(pearl);
	this->objects.push_back(house);
	xs.push_back((float)10);
	ys.push_back((float)0);
	zs.push_back((float)10);

	

	for (size_t i = 0; i < 20; i++)
	{
		DrawableObject* tr = new DrawableObject(new Shader(vertex_shader, phong, this->camera), new Model("objs/tree.obj", "Textures/tree.png"));
		tr->setMaterial(pearl);
		this->objects.push_back(tr);
		float x = rand() % 100;
		float z = rand() % 100;
		xs.push_back(x);
		ys.push_back(0);
		zs.push_back(z);
	}

	for (size_t i = 0; i < 20; i++)
	{
		DrawableObject* tr = new DrawableObject(new Shader(vertex_shader, phong, this->camera), new Model("objs/zombie.obj", "Textures/zombie.png"));
		tr->setMaterial(pearl);
		this->objects.push_back(tr);
		xs.push_back(rand() % 100);
		ys.push_back(0);
		zs.push_back(rand() % 100);
	}*/

	for (DrawableObject* object : this->objects) {
		object->setTextureId(this->textureId++);
		object->initialize();
		object->setLight(this->lights);
	} 
}

static void error_callback(int error, const char* description) { fputs(description, stderr); }

void Engine::initialization()
{
	this->camera = new Camera();
	this->lights.push_back(new Reflector(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.385, 0.647, 0.812, 1.0), 1, 1));
	this->lights.push_back(new Light(LightType::Point, glm::vec3(0.0f, 5.0f, 0.0f), glm::vec4(0.385, 0.647, 0.812, 1.0), 1, 1));
	this->lights.push_back(new Light(LightType::Point, glm::vec3(0.0f, 5.0f, 50.0f), glm::vec4(0.385, 0.647, 0.812, 1.0), 1, 1));
	this->lights[2]->setDirection(glm::vec3(1.0, 0.0, 0.0));

	this->previousWidth = 800;
	this->previousHeight = 600;

	glfwSetErrorCallback(error_callback);
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
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
}

bool keyDown = false;
void Engine::processUserInput()
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	
	std::cout << x << " " << y << std::endl;

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
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		this->processClick();
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && !keyDown) {
		keyDown = true;
		this->processBezierClick();
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
		keyDown = false;

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

void Engine::processClick()
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	GLbyte color[4];
	GLfloat depth;
	GLuint index;

	double x, y;

	//getting cursor position
	glfwGetCursorPos(window, &x, &y);
	
	GLint yp = viewport[3];

	double newy = yp - y;
	glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
	glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

	std::cout << "Clicked on pixel " << x << ", " << y <<  ", depth " << depth << ", stencil index " << index << std::endl;

	glm::vec3 screenCenter = glm::vec3(x, newy, depth);

	glm::mat4 view = this->camera->getView();
	glm::mat4 projection = this->camera->getProjection();

	glm::vec4 viewPort = glm::vec4(0, 0, viewport[2], viewport[3]);
	glm::vec3 pos = glm::unProject(screenCenter, view, projection, viewPort);
	printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);

	Material* pearl = new Material(glm::vec3(0.25, 0.20725, 0.20725), glm::vec3(1, 0.829, 0.829), glm::vec3(0.296648, 0.296648, 0.296648), 0.088);
	DrawableObject* tr = new DrawableObject(new Shader(vertex_shader, phong, this->camera), new Model("objs/tree.obj", "Textures/tree.png"));
	tr->setMaterial(pearl);
	this->objects.push_back(tr);
	xs.push_back(pos.x);
	ys.push_back(pos.y);
	zs.push_back(pos.z);

	tr->setTextureId(this->textureId++);
	tr->initialize();
	tr->setLight(this->lights);
}

void Engine::processBezierClick()
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	GLbyte color[4];
	GLfloat depth;
	GLuint index;

	double x, y;
	//getting cursor position
	glfwGetCursorPos(window, &x, &y);

	GLint yp = viewport[3];

	double newy = yp - y;
	glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
	glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

	std::cout << "Clicked on pixel " << x << ", " << y << ", depth " << depth << ", stencil index " << index << std::endl;

	glm::vec3 screenCenter = glm::vec3(x, newy, depth);

	glm::mat4 view = this->camera->getView();
	glm::mat4 projection = this->camera->getProjection();


	glm::vec4 viewPort = glm::vec4(0, 0, viewport[2], viewport[3]);
	glm::vec3 pos = glm::unProject(screenCenter, view, projection, viewPort);
	printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);

	this->tempBez.push_back(pos);
	if (tempBez.size() == 4) {
		this->bezier.push_back(glm::mat4x3(tempBez[0], tempBez[1], tempBez[2], tempBez[3]));
		glm::vec3 tmp = glm::vec3(tempBez[3]);
		this->tempBez.clear();
		this->tempBez.push_back(tmp);
	}
}
