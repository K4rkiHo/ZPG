// ***********************************************************************
//
//								 ZPG
// 
//						JAN KARKOŠKA - (KAR0229)
//
// ***********************************************************************

#include "Scene.h"
#include "Path_all.h"

Scene::Scene()
{

}

void Scene::Scene_Loop()
{
	this->height = 800;
	this->width = 600;

	int count_gold = 0;

	int scene_number;
	cout << "1. 4 koule TEST" << endl;
	cout << "2. Planety TEST" << endl;
	cout << "3. Phong TEST" << endl;
	cout << "4. Phong bad TEST" << endl;
	cout << "5. Resize TEST" << endl;
	cout << "6. 100 objektu TEST" << endl;
	cout << "7. Texture TEST" << endl;
	cout << "8. Final Scene" << endl;
	cout << "Zadej cislo sceny(1-8): ";
	cout << "";
	cin >> scene_number;

	GLFWwindow* window;
	glfwSetErrorCallback(CallBacks::error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	//inicializace konkretni verze
	// NEPOUŽÍVAT 
	//Version::inicialize_version();

	window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Sets the key callback
	glfwSetKeyCallback(window, CallBacks::key_callback);
	glfwSetCursorPosCallback(window, CallBacks::cursor_callback);
	glfwSetMouseButtonCallback(window, CallBacks::button_callback);
	glfwSetWindowFocusCallback(window, CallBacks::window_focus_callback);
	glfwSetWindowIconifyCallback(window, CallBacks::window_iconify_callback);
	glfwSetWindowSizeCallback(window, CallBacks::window_size_callback);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	// get version info
	Version::get_version();

	glm::vec4 lightColor = glm::vec4(1.0, 1.0, 1.0, 0.0); // Barva světla
	glm::vec3 lightPosition= glm::vec3(0.0, 1.0, 5.0); // Pozice světla
	glm::vec3 lightDirection = glm::vec3(0.0, -1.0, -0.5);
	float ambientStrength = 0.2f; // Síla svítivosti objektu
	float specularStrength = 0.5f; // Síla zrcadlového odrazu
	float shininess = 32.0f; // Lesk (bílá tečka -> větší float = menší bílé světlo)
	float typeLight = 4;
	float light_on = 1;

	//1 = point Light
	//2 = direction Light
	//3 = spotlight
	//4 = flashlight

	//4 koule
	if (scene_number == 1)
	{
		Scene_no1(window);
	}

	//Planety
	if (scene_number == 2)
	{
		Scene_no2(window);
	}

	//Phong good h = 1
	if (scene_number == 3)
	{
		Scene_no3(window);
	}

	//phong bad h = 1
	if (scene_number == 4)
	{
		Scene_no4(window);
	}
	//sirka obrazovky 
	if (scene_number == 5)
	{
		Scene_no5(window);
	}

	//vice objektu
	if (scene_number == 6)
	{
		Scene_no6(window);
	}
	//Texture Test
	if (scene_number == 7)
	{
		Scene_no7(window);
	}
	//3D textures models 
	if (scene_number == 8)
	{
		Scene_no8(window);
	}
}

void Scene::Scene_no1(GLFWwindow* window)
{
	glm::vec4 lightColor = glm::vec4(1.0, 1.0, 1.0, 0.0); // Barva světla
	glm::vec3 lightPosition = glm::vec3(0.0, 0.0, 0.0); // Pozice světla
	glm::vec3 lightDirection = glm::vec3(0.0, -1.0, -0.5);
	float ambientStrength = 0.2f; // Síla svítivosti objektu
	float specularStrength = 0.5f; // Síla zrcadlového odrazu
	float shininess = 32.0f; // Lesk (bílá tečka -> větší float = menší bílé světlo)
	float typeLight = 4;
	float light_on = 1;
	
	Model* m3 = new Model(sphere, sizeof(sphere), phong_vert_path2, phong_frag_path2, "phong_lights");
	m3->addTransform(new Scale(glm::vec3(0.5f)));
	m3->addTransform(new Translate(glm::vec3(1.0f, 0.0f, 0.0f)));

	Model* m4 = new Model(sphere, sizeof(sphere), phong_vert_path2, phong_frag_path2, "phong_lights");
	m4->addTransform(new Scale(glm::vec3(0.5f)));
	m4->addTransform(new Translate(glm::vec3(0.0f, 1.0f, 0.0f)));

	Model* m5 = new Model(sphere, sizeof(sphere), phong_vert_path2, phong_frag_path2, "phong_lights");
	m5->addTransform(new Scale(glm::vec3(0.5f)));
	m5->addTransform(new Translate(glm::vec3(-1.0f, 0.0f, 0.0f)));

	Model* m6 = new Model(sphere, sizeof(sphere), phong_vert_path2, phong_frag_path2, "phong_lights");
	m6->addTransform(new Scale(glm::vec3(0.5f)));
	m6->addTransform(new Translate(glm::vec3(0.0f, -1.0f, 0.0f)));

	Camera* camera = new Camera(glm::vec3(0.0, 0.0, 5.0), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0));
	camera->attach(m3->getShaderProgram());
	camera->attach(m4->getShaderProgram());
	camera->attach(m5->getShaderProgram());
	camera->attach(m6->getShaderProgram());

	Material* material = new Material(glm::vec4(0.385, 0.647, 0.812, 1.0));
	//Material* material = new Material(glm::vec4(1.0, 1.0, 1.0, 1.0));
	material->attach(m3->getShaderProgram());
	material->attach(m4->getShaderProgram());
	material->attach(m5->getShaderProgram());
	material->attach(m6->getShaderProgram());
	material->setColor();

	Light* l = new Light(lightPosition, lightColor, lightDirection, ambientStrength, specularStrength, shininess, 1, light_on);
	l->attach(m3->getShaderProgram());
	l->attach(m4->getShaderProgram());
	l->attach(m5->getShaderProgram());
	l->attach(m6->getShaderProgram());
	l->refrestLight();

	//LOADING LOOP
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		bool mouse_click = CallBacks::mouse_callkack(window);

		std::pair<double, double> pos = CallBacks::cursor_callback(window);
		auto currentFrame = static_cast<float>(glfwGetTime());
		camera->mouseMove(pos.first, pos.second, mouse_click);

		this->deltaTime = currentFrame - this->lastFrame;
		this->lastFrame = currentFrame;

		camera->move(window, deltaTime);
		camera->resizeWindow(window);

		m3->Create_Model();
		m4->Create_Model();
		m5->Create_Model();
		m6->Create_Model();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Scene::Scene_no2(GLFWwindow* window)
{
	glm::vec4 lightColor = glm::vec4(1.0, 1.0, 1.0, 0.0); // Barva světla
	glm::vec3 lightPosition = glm::vec3(0.0, 0.0, 1.0); //Pozice světla
	glm::vec3 lightDirection = glm::vec3(0.0, -1.0, -0.5);
	float ambientStrength = 0.8f; // Síla svítivosti objektu
	float specularStrength = 0.5f; // Síla zrcadlového odrazu
	float shininess = 32.0f; // Lesk (bílá tečka -> větší float = menší bílé světlo)
	float light_on = 1;
	float typeLight = 1;
	
	//slunce
	Model* m2 = new Model(sphere, sizeof(sphere), phong_vert_path2, phong_frag_path2, "phong_lights");
	m2->addTransform(new Scale(glm::vec3(0.4f)));
	m2->addTransform(new Translate(glm::vec3(0.0f, 0.0f, 1.0f)));
	//zeme
	Model* m3 = new Model(sphere, sizeof(sphere), phong_vert_path2, phong_frag_path2, "phong_lights");
	m3->addTransform(new Scale(glm::vec3(0.2f)));
	m3->addTransform(new Translate(glm::vec3(0.0f, 0.0f, 2.0f)));
	m3->addTransform(new Rotate(glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.007f));
	m3->addTransform(new Translate(glm::vec3(0.0f, 0.0f, 1.0f)));
	//mesic
	Model* m4 = new Model(sphere, sizeof(sphere), phong_vert_path2, phong_frag_path2, "phong_lights");
	m4->addTransform(new Scale(glm::vec3(0.1f)));
	m4->addTransform(new Translate(glm::vec3(0.0f, 0.0f, 1.0f)));
	m4->addTransform(new Rotate(glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.02f));
	m4->addTransform(new Translate(glm::vec3(0.0f, 0.0f, 2.0f)));
	m4->addTransform(new Rotate(glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.007f));
	m4->addTransform(new Translate(glm::vec3(0.0f, 0.0f, 1.0f)));
	//random planeta
	Model* m5 = new Model(sphere, sizeof(sphere), phong_vert_path2, phong_frag_path2, "phong_lights");
	m5->addTransform(new Scale(glm::vec3(0.6f)));
	m5->addTransform(new Translate(glm::vec3(0.0f, 0.0f, 5.0f)));
	m5->addTransform(new Rotate(glm::radians(5.0f), glm::vec3(0.0f, -1.0f, 0.0f), 0.003f));
	m5->addTransform(new Translate(glm::vec3(0.0f, 0.0f, 1.0f)));
	//random planeta
	Model* m6 = new Model(sphere, sizeof(sphere), phong_vert_path2, phong_frag_path2, "phong_lights");
	m6->addTransform(new Scale(glm::vec3(0.5f)));
	m6->addTransform(new Translate(glm::vec3(0.0f, 0.0f, 7.0f)));
	m6->addTransform(new Rotate(glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0006f));
	m6->addTransform(new Translate(glm::vec3(0.0f, 0.0f, 1.0f)));

	Material* mat1 = new Material(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	mat1->attach(m2->getShaderProgram());
	mat1->setColor();

	Material* mat2 = new Material(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
	mat2->attach(m4->getShaderProgram());
	mat2->setColor();

	Material* mat3 = new Material(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	mat3->attach(m3->getShaderProgram());
	mat3->setColor();

	Material* mat4 = new Material(glm::vec4(1.0f, 0.3f, 0.0f, 1.0f));
	mat4->attach(m5->getShaderProgram());
	mat4->setColor();

	Material* mat5 = new Material(glm::vec4(1.0f, 0.3f, 0.9f, 1.0f));
	mat5->attach(m6->getShaderProgram());
	mat5->setColor();

	Light* l = new Light(lightPosition, lightColor, lightDirection, ambientStrength, specularStrength, shininess, typeLight, light_on);
	l->attach(m2->getShaderProgram());
	l->attach(m3->getShaderProgram());
	l->attach(m4->getShaderProgram());
	l->attach(m5->getShaderProgram());
	l->attach(m6->getShaderProgram());
	l->refrestLight();

	Camera* camera = new Camera(glm::vec3(0.0, 15.0, 3.0), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0));
	camera->attach(m2->getShaderProgram());
	camera->attach(m3->getShaderProgram());
	camera->attach(m4->getShaderProgram());
	camera->attach(m5->getShaderProgram());
	camera->attach(m6->getShaderProgram());

	//LOADING LOOP
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClearColor(0.01f, 0.2f, 1.0f, 1);

		bool mouse_click = CallBacks::mouse_callkack(window);

		std::pair<double, double> pos = CallBacks::cursor_callback(window);
		auto currentFrame = static_cast<float>(glfwGetTime());
		camera->mouseMove(pos.first, pos.second, mouse_click);

		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		camera->move(window, deltaTime);
		camera->resizeWindow(window);

		m4->Create_Model();
		m3->Create_Model();
		m2->Create_Model();
		m5->Create_Model();
		m6->Create_Model();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Scene::Scene_no3(GLFWwindow* window)
{
	glm::vec4 lightColor = glm::vec4(1.0, 1.0, 1.0, 0.0); // Barva světla
	glm::vec3 lightPosition = glm::vec3(0.0, 0.0, 0.0); // Pozice světla
	glm::vec3 lightDirection = glm::vec3(0.0, -1.0, -0.5);
	float ambientStrength = 0.2f; // Síla svítivosti objektu
	float specularStrength = 0.5f; // Síla zrcadlového odrazu
	float shininess = 1.0f; // Lesk (bílá tečka -> větší float = menší bílé světlo)
	float light_on = 1;
	float typeLight = 1;

	Model* m3 = new Model(sphere, sizeof(sphere), phong_vert_path2, phong_frag_path2, "phong_lights");
	m3->addTransform(new Scale(glm::vec3(0.2f)));
	m3->addTransform(new Translate(glm::vec3(0.0f, 0.0f, 2.0f)));

	Camera* camera = new Camera(glm::vec3(0.0, 0.0, 3.0), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0));
	camera->attach(m3->getShaderProgram());

	Material* material = new Material(glm::vec4(0.385, 0.647, 0.812, 1.0));
	material->attach(m3->getShaderProgram());
	material->setColor();

	Light* l = new Light(lightPosition, lightColor, lightDirection, ambientStrength, specularStrength, shininess, 1, light_on);
	l->attach(m3->getShaderProgram());
	l->refrestLight();

	//LOADING LOOP
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		bool mouse_click = CallBacks::mouse_callkack(window);

		std::pair<double, double> pos = CallBacks::cursor_callback(window);
		auto currentFrame = static_cast<float>(glfwGetTime());
		camera->mouseMove(pos.first, pos.second, mouse_click);

		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		camera->move(window, deltaTime);
		camera->resizeWindow(window);

		m3->Create_Model();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Scene::Scene_no4(GLFWwindow* window)
{
	glm::vec4 lightColor = glm::vec4(1.0, 1.0, 1.0, 0.0); // Barva světla
	glm::vec3 lightPosition = glm::vec3(0.0, 0.0, 0.0); // Pozice světla
	glm::vec3 lightDirection = glm::vec3(0.0, -1.0, -0.5);
	float ambientStrength = 0.2f; // Síla svítivosti objektu
	float specularStrength = 0.5f; // Síla zrcadlového odrazu
	float shininess = 1.0f; // Lesk (bílá tečka -> větší float = menší bílé světlo)
	float light_on = 1;
	float typeLight = 1;

	Model* m3 = new Model(sphere, sizeof(sphere), phong_bad_vert_path, phong_bad_frag_path, "phong_bad");
	m3->addTransform(new Scale(glm::vec3(0.2f)));
	m3->addTransform(new Translate(glm::vec3(0.0f, 0.0f, 2.0f)));

	Camera* camera = new Camera(glm::vec3(0.0, 0.0, 3.0), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0));
	camera->attach(m3->getShaderProgram());

	Material* material = new Material(glm::vec4(0.385, 0.647, 0.812, 1.0));
	material->attach(m3->getShaderProgram());
	material->setColor();

	Light* l = new Light(lightPosition, lightColor, lightDirection, ambientStrength, specularStrength, shininess, 1, light_on);
	l->attach(m3->getShaderProgram());
	l->refrestLight();

	//LOADING LOOP
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		bool mouse_click = CallBacks::mouse_callkack(window);

		std::pair<double, double> pos = CallBacks::cursor_callback(window);
		auto currentFrame = static_cast<float>(glfwGetTime());
		camera->mouseMove(pos.first, pos.second, mouse_click);

		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		camera->move(window, deltaTime);
		camera->resizeWindow(window);

		m3->Create_Model();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Scene::Scene_no5(GLFWwindow* window)
{
	glm::vec4 lightColor = glm::vec4(1.0, 1.0, 1.0, 0.0); // Barva světla
	glm::vec3 lightPosition = glm::vec3(0.0, 1.0, 5.0); // Pozice světla
	glm::vec3 lightDirection = glm::vec3(0.0, -1.0, -0.5);
	float ambientStrength = 0.2f; // Síla svítivosti objektu
	float specularStrength = 0.5f; // Síla zrcadlového odrazu
	float shininess = 32.0f; // Lesk (bílá tečka -> větší float = menší bílé světlo)
	float typeLight = 4;
	float light_on = 1;

	Model* skybox = new Model(skycube, sizeof(skycube), skybox_texture_vert_path, skybox_texture_frag_path, "", "skybox");

	Model* m = new Model(suziFlat, sizeof(suziFlat), phong_vert_path2, phong_frag_path2, "phong_lights");
	m->addTransform(new Scale(glm::vec3(0.3f)));
	m->addTransform(new Rotate(glm::radians(15.0f), glm::vec3(1.0f, 1.0f, 0.0f), 0.001f));
	m->addTransform(new Translate(glm::vec3(-1.0f, 0.4f, 0.0f)));

	Model* m1 = new Model(cube, sizeof(cube), default_vert_path, default_frag_path, "default");
	m1->addTransform(new Rotate(glm::radians(15.0f), glm::vec3(1.0f, 1.0f, 0.0f), 0.15f));
	m1->addTransform(new Scale(glm::vec3(0.5f)));
	m1->addTransform(new Translate(glm::vec3(-2.0f, 0.0f, 1.0f)));

	Model* m2 = new Model(suziSmooth, sizeof(suziSmooth), phong_vert_path2, phong_frag_path2, "phong_lights");
	m2->addTransform(new Rotate(glm::radians(-110.0f), glm::vec3(0.0f, -1.0f, 0.0f), 0.0f));
	m2->addTransform(new Scale(glm::vec3(0.3f)));
	m2->addTransform(new Translate(glm::vec3(0.5f, 0.0f, 2.0f)));

	Model* m3 = new Model(sphere, sizeof(sphere), phong_vert_path2, phong_frag_path2, "phong_lights");
	m3->addTransform(new Scale(glm::vec3(0.25f)));
	m3->addTransform(new Translate(glm::vec3(1.0f, 0.0f, 0.0f)));

	Model* plain = new Model(plain_texture, sizeof(plain_texture), phong_texture_vert_path, phong_texture_frag_path, "", "texture");
	plain->addTransform(new Scale(glm::vec3(100.0f)));
	plain->addTransform(new Translate(glm::vec3(0.0f, -1.0f, 0.0f)));

	Model* m5 = new Model(tree, sizeof(tree), phong_vert_path2, phong_frag_path2, "phong_lights");
	m5->addTransform(new Scale(glm::vec3(0.5f)));
	m5->addTransform(new Translate(glm::vec3(0.0f, -1.0f, -3.0f)));

	Model* m6 = new Model(gift, sizeof(gift), default_vert_path, default_frag_path, "default");
	m6->addTransform(new Scale(glm::vec3(0.5f)));
	m6->addTransform(new Translate(glm::vec3(0.0f, -1.0f, 3.0f)));

	Model* m7 = new Model(bushes, sizeof(bushes), phong_vert_path2, phong_frag_path2, "phong_lights");
	m7->addTransform(new Scale(glm::vec3(0.5f)));
	m7->addTransform(new Translate(glm::vec3(0.6f, -1.0f, 2.6f)));

	Model* m8 = new Model(bushes, sizeof(bushes), phong_vert_path2, phong_frag_path2, "phong_lights");
	m8->addTransform(new Scale(glm::vec3(0.5f)));
	m8->addTransform(new Translate(glm::vec3(0.0f, -1.0f, 2.0f)));

	Model* m9 = new Model(bushes, sizeof(bushes), phong_vert_path2, phong_frag_path2, "phong_lights");
	m9->addTransform(new Scale(glm::vec3(0.5f)));
	m9->addTransform(new Translate(glm::vec3(-0.8f, -1.0f, 2.3f)));

	Model* m10 = new Model(tree, sizeof(tree), phong_vert_path2, phong_frag_path2, "phong_lights");
	m10->addTransform(new Scale(glm::vec3(0.9f)));
	m10->addTransform(new Translate(glm::vec3(-3.8f, -1.0f, 2.3f)));

	Light* l = new Light(lightPosition, lightColor, lightDirection, ambientStrength, specularStrength, shininess, 2, light_on);
	l->attach(m->getShaderProgram());
	l->attach(m1->getShaderProgram());
	l->attach(m2->getShaderProgram());
	l->attach(m3->getShaderProgram());
	//l->attach(plain->getShaderProgram());
	l->attach(m5->getShaderProgram());
	l->attach(m6->getShaderProgram());
	l->attach(m7->getShaderProgram());
	l->attach(m8->getShaderProgram());
	l->attach(m9->getShaderProgram());
	l->attach(m10->getShaderProgram());
	l->refrestLight();

	Camera* camera = new Camera(glm::vec3(0.0, 0.0, 5.0), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0));
	camera->attach(skybox->getShaderProgram());
	camera->attach(m->getShaderProgram());
	camera->attach(m1->getShaderProgram());
	camera->attach(m2->getShaderProgram());
	camera->attach(m3->getShaderProgram());
	camera->attach(plain->getShaderProgram());
	camera->attach(m5->getShaderProgram());
	camera->attach(m6->getShaderProgram());
	camera->attach(m7->getShaderProgram());
	camera->attach(m8->getShaderProgram());
	camera->attach(m9->getShaderProgram());
	camera->attach(m10->getShaderProgram());

	std::vector<const char*> texturePathsSkybox = {
		"./Textures/right.jpg",
		"./Textures/left.jpg",
		"./Textures/top.jpg",
		"./Textures/bottom.jpg",
		"./Textures/front.jpg",
		"./Textures/back.jpg"
	};

	//MUST BE First!!!
	Material* materialSkybox = new Material(texturePathsSkybox);
	materialSkybox->attach(skybox->getShaderProgram());
	materialSkybox->setTextureSkybox();

	const char* texturePathGrass = "./Textures/grass.png";
	Material* material_plain = new Material(texturePathGrass);
	material_plain->attach(plain->getShaderProgram());
	material_plain->setTextureRepeat(10);
	material_plain->setTexture();

	Material* material_grass = new Material(glm::vec4(0.0f, 1.0f, 0.3f, 1.0f));
	material_grass->attach(m7->getShaderProgram());
	material_grass->attach(m8->getShaderProgram());
	material_grass->attach(m9->getShaderProgram());
	material_grass->setColor();

	Material* material_tree = new Material(glm::vec4(0.0f, 1.0f, 0.7f, 1.0f));
	material_tree->attach(m5->getShaderProgram());
	material_tree->attach(m10->getShaderProgram());
	material_tree->setColor();

	Material* material_suzi = new Material(glm::vec4(0.9f, 1.0f, 0.7f, 1.0f));
	material_suzi->attach(m->getShaderProgram());
	material_suzi->attach(m2->getShaderProgram());
	material_suzi->setColor();

	Material* material_sphere = new Material(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	material_sphere->attach(m3->getShaderProgram());
	material_sphere->setColor();

	//LOADING LOOP
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.01f, 0.6f, 1.0f, 1);

		bool mouse_click = CallBacks::mouse_callkack(window);

		std::pair<double, double> pos = CallBacks::cursor_callback(window);
		auto currentFrame = static_cast<float>(glfwGetTime());
		camera->mouseMove(pos.first, pos.second, mouse_click);

		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		camera->move(window, deltaTime);
		camera->resizeWindow(window);


		//must be first!
		skybox->Create_Model();

		glClear(GL_DEPTH_BUFFER_BIT);
		//must be first!

		plain->Create_Model();
		m->Create_Model();
		m1->Create_Model();
		m2->Create_Model();
		m3->Create_Model();
		m5->Create_Model();
		m6->Create_Model();
		m7->Create_Model();
		m8->Create_Model();
		m9->Create_Model();
		m10->Create_Model();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Scene::Scene_no6(GLFWwindow* window)
{
	glm::vec4 lightColor = glm::vec4(1.0, 1.0, 1.0, 0.0); // Barva světla
	glm::vec3 lightPosition = glm::vec3(0.0, 1.0, 5.0); // Pozice světla
	glm::vec3 lightDirection = glm::vec3(0.0, -1.0, -0.5);
	float ambientStrength = 0.2f; // Síla svítivosti objektu
	float specularStrength = 0.5f; // Síla zrcadlového odrazu
	float shininess = 32.0f; // Lesk (bílá tečka -> větší float = menší bílé světlo)
	float typeLight = 4;
	float light_on = 1;

	Model* skybox = new Model(skycube, sizeof(skycube), skybox_texture_vert_path, skybox_texture_frag_path, "", "skybox");

	Model* plain_ = new Model(plain_texture, sizeof(plain_texture), phong_texture_vert_path, phong_texture_frag_path, "", "texture");
	plain_->addTransform(new Scale(glm::vec3(100.0f)));
	plain_->addTransform(new Translate(glm::vec3(0.0f, -1.0f, 0.0f)));

	std::vector<Model*> grass_vec;
	std::vector<Model*> tree_vec;
	std::vector<Model*> suzi_vec;
	std::vector<Model*> cube_vec;
	std::vector<Model*> sphere_vec;
	std::vector<Model*> triagles_vec;

	for (int i = 0; i < 20; i++)
	{
		grass_vec.push_back(new Model(bushes, sizeof(bushes), phong_vert_path2, phong_frag_path2, "phong_lights"));
		tree_vec.push_back(new Model(tree, sizeof(tree), phong_vert_path2, phong_frag_path2, "phong_lights"));
		suzi_vec.push_back(new Model(suziFlat, sizeof(suziFlat), phong_vert_path2, phong_frag_path2, "phong_lights"));
		cube_vec.push_back(new Model(cube, sizeof(cube), default_vert_path, default_frag_path, "default"));
		sphere_vec.push_back(new Model(sphere, sizeof(sphere), phong_vert_path2, phong_frag_path2, "phong_lights"));
		triagles_vec.push_back(new Model(triangle, sizeof(triangle), phong_texture_vert_path, phong_texture_frag_path, "", "texture"));
	}

	Light* l = new Light(lightPosition, lightColor, lightDirection, ambientStrength, specularStrength, shininess, 2, light_on);
	l->attach(plain_->getShaderProgram());

	for (int i = 0; i < 20; i++)
	{
		l->attach(grass_vec[i]->getShaderProgram());
		l->attach(tree_vec[i]->getShaderProgram());
		l->attach(suzi_vec[i]->getShaderProgram());
		l->attach(cube_vec[i]->getShaderProgram());
		l->attach(sphere_vec[i]->getShaderProgram());
	}
	l->refrestLight();

	Camera* camera = new Camera(glm::vec3(0.0, 0.0, 5.0), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0));
	camera->attach(skybox->getShaderProgram());
	camera->attach(plain_->getShaderProgram());

	std::vector<const char*> texturePathsSkybox = {
		"./Textures/posx.jpg",
		"./Textures/negx.jpg",
		"./Textures/posy.jpg",
		"./Textures/negy.jpg",
		"./Textures/posz.jpg",
		"./Textures/negz.jpg"
	};

	Material* material_skybox = new Material(texturePathsSkybox);
	material_skybox->attach(skybox->getShaderProgram());
	material_skybox->setTextureSkybox();

	Material* material_grass = new Material(glm::vec4(0.0f, 1.0f, 0.3f, 1.0f));
	Material* material_tree = new Material(glm::vec4(0.0f, 1.0f, 0.7f, 1.0f));
	Material* material_suzi = new Material(glm::vec4(0.9f, 1.0f, 0.7f, 1.0f));
	Material* material_sphere = new Material(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	const char* texturePathWood = "./Textures/wooden_fence.png";
	Material* material_wood_triagles = new Material(texturePathWood);



	for (int i = 0; i < 20; i++)
	{
		float randomX = static_cast<float>(rand()) / RAND_MAX;
		float randomZ = static_cast<float>(rand()) / RAND_MAX;
		float randomScale = static_cast<float>(rand()) / RAND_MAX;
		float randomRotation = glm::linearRand(-glm::pi<float>(), glm::pi<float>());
		float newX = randomX * 100.0 - 20.0;
		float newZ = randomZ * 100.0 - 20.0;
		float scale = randomScale * 0.9 + 0.1;
		grass_vec[i]->addTransform(new Rotate(glm::radians(randomRotation), glm::vec3(1.0f, 0.0f, 0.0f), 0.0f));
		grass_vec[i]->addTransform(new Translate(glm::vec3(newX, -1.0f, newZ)));
		camera->attach(grass_vec[i]->getShaderProgram());
	}
	for (int i = 0; i < 20; i++)
	{
		float randomX = static_cast<float>(rand()) / RAND_MAX;
		float randomZ = static_cast<float>(rand()) / RAND_MAX;
		float randomScale = static_cast<float>(rand()) / RAND_MAX;
		float randomRotation = glm::linearRand(-glm::pi<float>(), glm::pi<float>());
		float newX = randomX * 100.0 - 20.0;
		float newZ = randomZ * 100.0 - 20.0;
		float scale = randomScale * 0.9 + 0.1;
		tree_vec[i]->addTransform(new Rotate(glm::radians(randomRotation), glm::vec3(1.0f, 0.0f, 0.0f), 0.0f));
		tree_vec[i]->addTransform(new Translate(glm::vec3(newX, -1.0f, newZ)));
		tree_vec[i]->addTransform(new Scale(glm::vec3(scale)));
		camera->attach(tree_vec[i]->getShaderProgram());
	}

	for (int i = 0; i < 20; i++)
	{
		float randomX = static_cast<float>(rand()) / RAND_MAX;
		float randomZ = static_cast<float>(rand()) / RAND_MAX;
		float randomScale = static_cast<float>(rand()) / RAND_MAX;
		float randomRotation = glm::linearRand(-glm::pi<float>(), glm::pi<float>());
		float newX = randomX * 100.0 - 20.0;
		float newZ = randomZ * 100.0 - 20.0;
		float scale = randomScale * 0.9 + 0.1;
		suzi_vec[i]->addTransform(new Rotate(randomRotation, glm::vec3(1.0f, 1.0f, 0.0f), 0.0f));
		suzi_vec[i]->addTransform(new Translate(glm::vec3(newX, -1.0f, newZ)));
		suzi_vec[i]->addTransform(new Scale(glm::vec3(scale)));
		camera->attach(suzi_vec[i]->getShaderProgram());
	}

	for (int i = 0; i < 20; i++)
	{
		float randomX = static_cast<float>(rand()) / RAND_MAX;
		float randomZ = static_cast<float>(rand()) / RAND_MAX;
		float randomScale = static_cast<float>(rand()) / RAND_MAX;
		float randomRotation = glm::linearRand(-glm::pi<float>(), glm::pi<float>());
		float newX = randomX * 100.0 - 20.0;
		float newZ = randomZ * 100.0 - 20.0;
		float scale = randomScale * 0.9 + 0.1;
		cube_vec[i]->addTransform(new Rotate(randomRotation, glm::vec3(1.0f, 1.0f, 0.0f), 0.0f));
		cube_vec[i]->addTransform(new Translate(glm::vec3(newX, -1.0f, newZ)));
		cube_vec[i]->addTransform(new Scale(glm::vec3(scale)));
		camera->attach(cube_vec[i]->getShaderProgram());
	}

	for (int i = 0; i < 20; i++)
	{
		float randomX = static_cast<float>(rand()) / RAND_MAX;
		float randomZ = static_cast<float>(rand()) / RAND_MAX;
		float randomScale = static_cast<float>(rand()) / RAND_MAX;
		float randomRotation = glm::linearRand(-glm::pi<float>(), glm::pi<float>());
		float newX = randomX * 100.0 - 20.0;
		float newZ = randomZ * 100.0 - 20.0;
		float scale = randomScale * 0.9 + 0.1;
		sphere_vec[i]->addTransform(new Rotate(randomRotation, glm::vec3(1.0f, 1.0f, 0.0f), 0.0f));
		sphere_vec[i]->addTransform(new Translate(glm::vec3(newX, -1.0f, newZ)));
		sphere_vec[i]->addTransform(new Scale(glm::vec3(scale)));
		camera->attach(sphere_vec[i]->getShaderProgram());
	}

	for (int i = 0; i < 20; i++)
	{
		float randomX = static_cast<float>(rand()) / RAND_MAX;
		float randomZ = static_cast<float>(rand()) / RAND_MAX;
		float randomScale = static_cast<float>(rand()) / RAND_MAX;
		float randomRotation = glm::linearRand(-glm::pi<float>(), glm::pi<float>());
		float newX = randomX * 100.0 - 20.0;
		float newZ = randomZ * 100.0 - 20.0;
		float scale = randomScale * 0.9 + 0.1;
		triagles_vec[i]->addTransform(new Rotate(randomRotation, glm::vec3(1.0f, 1.0f, 0.0f), 0.0f));
		triagles_vec[i]->addTransform(new Translate(glm::vec3(newX, -1.0f, newZ)));
		triagles_vec[i]->addTransform(new Scale(glm::vec3(scale)));
		camera->attach(triagles_vec[i]->getShaderProgram());
	}

	//attach and set color
	for (int i = 0; i < 20; i++)
	{
		material_grass->attach(grass_vec[i]->getShaderProgram());
		material_grass->setColor();

		material_tree->attach(tree_vec[i]->getShaderProgram());
		material_tree->setColor();

		material_suzi->attach(suzi_vec[i]->getShaderProgram());
		material_suzi->setColor();

		material_sphere->attach(sphere_vec[i]->getShaderProgram());
		material_sphere->setColor();

		material_wood_triagles->attach(triagles_vec[i]->getShaderProgram());
		material_wood_triagles->setTexture();
	}
	const char* texturePathGrass = "./Textures/grass.png";

	Material* material_plain = new Material(texturePathGrass);
	material_plain->attach(plain_->getShaderProgram());
	material_plain->setTextureRepeat(100);
	material_plain->setTexture();

	//LOADING LOOP
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		bool mouse_click = CallBacks::mouse_callkack(window);

		std::pair<double, double> pos = CallBacks::cursor_callback(window);
		auto currentFrame = static_cast<float>(glfwGetTime());
		camera->mouseMove(pos.first, pos.second, mouse_click);

		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		camera->move(window, deltaTime);
		camera->resizeWindow(window);

		//must be first!
		skybox->Create_Model();

		glClear(GL_DEPTH_BUFFER_BIT);
		//must be first!

		for (int i = 0; i < 20; i++)
		{
			grass_vec[i]->Create_Model();
			tree_vec[i]->Create_Model();
			suzi_vec[i]->Create_Model();
			cube_vec[i]->Create_Model();
			sphere_vec[i]->Create_Model();
			triagles_vec[i]->Create_Model();
		}

		plain_->Create_Model();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Scene::Scene_no7(GLFWwindow* window)
{
	glm::vec4 lightColor = glm::vec4(1.0, 1.0, 1.0, 0.0); // Barva světla
	glm::vec3 lightPosition = glm::vec3(0.0, 0.0, 0.0); // Pozice světla
	glm::vec3 lightDirection = glm::vec3(0.0, -1.0, -0.5);
	float ambientStrength = 0.2f; // Síla svítivosti objektu
	float specularStrength = 0.5f; // Síla zrcadlového odrazu
	float shininess = 32.0f; // Lesk (bílá tečka -> větší float = menší bílé světlo)
	float typeLight = 4;
	float light_on = 1;

	const char* phong_texture_vert_path = "./Shaders/phongTextureLightTest.vert";
	const char* phong_texture_frag_path = "./Shaders/phongTextureLightTest.frag";
	std::vector<Model*> models_vec;

	//./Textures/grass.png
	const char* texturePathGrass = "./Textures/grass.png";
	const char* texturePathWood = "./Textures/wooden_fence.png";
	const char* texturePathZed = "./Textures/zed.png";
	const char* texturePathZed2 = "./Textures/gold.jpg";
	const char* texturePathGold = "./Textures/gold.jpg;";

	const char* zed_o = "./Models/3D_Models/zed.obj";
	const char* gold_o = "./Models/3D_Models/gold.obj";

	Model* m2 = new Model(cube, sizeof(cube), default_vert_path, default_frag_path, "default");
	m2->addTransform(new Translate(glm::vec3(0.0f, 0.0f, 2.0f)));

	Model* m = new Model(plain_texture, sizeof(plain_texture), phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture");
	m->addTransform(new Scale(glm::vec3(5.0f)));
	m->addTransform(new Translate(glm::vec3(0.0f, -1.0f, 0.0f)));

	Model* m3 = new Model(triangle, sizeof(triangle), phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture");
	m3->addTransform(new Translate(glm::vec3(1.0f, 0.0f, -1.0f)));


	Model* skybox = new Model(skycube, sizeof(skycube), skybox_texture_vert_path, skybox_texture_frag_path, "phong_lights", "skybox");
	models_vec.push_back(skybox);
	models_vec.push_back(m2);
	models_vec.push_back(m);
	models_vec.push_back(m3);


	//Model* m_test = new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", zed_o);

	Model* gold_test = new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", gold_o);
	gold_test->addTransform(new Rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.0f));
	gold_test->addTransform(new Rotate(glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.07f));
	gold_test->addTransform(new Scale(glm::vec3(0.06f)));
	gold_test->addTransform(new Translate(glm::vec3(2.0f, -1.0f, -1.0f)));
	models_vec.push_back(gold_test);

	Light* l = new Light(lightPosition, lightColor, lightDirection, ambientStrength, specularStrength, shininess, 4, light_on);
	l->attach(m2->getShaderProgram());
	l->attach(m->getShaderProgram());
	l->attach(m3->getShaderProgram());
	//l->attach(m_test->getShaderProgram());
	l->attach(gold_test->getShaderProgram());
	l->refrestLight();


	//m4->addTransform(new Scale(glm::vec3(100.0f)));
	Camera* camera = new Camera(glm::vec3(0.0, 0.0, 5.0), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0));
	camera->attach(m->getShaderProgram());
	camera->attach(m2->getShaderProgram());
	camera->attach(m3->getShaderProgram());
	//camera->attach(m_test->getShaderProgram());
	camera->attach(gold_test->getShaderProgram());
	camera->attach(skybox->getShaderProgram());

	//std::vector<const char*> texturePathGrass = { "./Textures/grass.png" };
	//std::vector<const char*> texturePathWood = { "./Textures/wooden_fence.png" };

	std::vector<const char*> texturePathsSkybox = {
		"./Textures/posx.jpg",
		"./Textures/negx.jpg",
		"./Textures/posy.jpg",
		"./Textures/negy.jpg",
		"./Textures/posz.jpg",
		"./Textures/negz.jpg"
	};

	//MUST BE First!!!
	Material* material2 = new Material(texturePathsSkybox);
	material2->attach(skybox->getShaderProgram());
	material2->setTextureSkybox();

	Material* material = new Material(texturePathGrass);
	material->attach(m->getShaderProgram());
	material->setTexture();

	Material* material1 = new Material(texturePathWood);
	material1->attach(m3->getShaderProgram());
	material1->setTexture();

	Material* materie = new Material(texturePathZed2);
	materie->attach(gold_test->getShaderProgram());
	materie->setTexture();

	std::vector<glm::vec3> vec;

	vec.push_back(glm::vec3(-2, 0, 0));
	vec.push_back(glm::vec3(0, 2, 0));
	vec.push_back(glm::vec3(0, -2, 0));
	vec.push_back(glm::vec3(2, 0, 0));

	glm::vec3 A(0.0f, 0.0f, 0.0f);  
	glm::vec3 B(2.0f, 0.0f, 0.0f); 

	float t = 0.1f;
	float delta = 0.01f;

	m2->addTransform(new BezierLine(vec, 0.5f, 0.01f));

	//LOADING LOOP
	while (!glfwWindowShouldClose(window)) {

		//glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);
		//glm::vec3 p = parameters * A * glm::transpose(B);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glClearColor(0.01f, 0.6f, 1.0f, 1);

		bool clickObj = CallBacks::mouse_right_callback(window);
		//bool removeObj = CallBacks::Q_key_pressed_callback(window);
		bool mouse_click = CallBacks::mouse_callkack(window);
		std::pair<double, double> pos = CallBacks::cursor_callback(window);
		auto currentFrame = static_cast<float>(glfwGetTime());
		camera->mouseMove(pos.first, pos.second, mouse_click);

		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		camera->move(window, deltaTime);
		camera->resizeWindow(window);

		//must be first!
		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		skybox->Create_Model();

		glClear(GL_DEPTH_BUFFER_BIT);
		//must be first!

		//m_test->Create_Model_3D();

		for (int i = 1; i < models_vec.size(); i++)
		{
			glStencilFunc(GL_ALWAYS, i, 0xFF);
			models_vec[i]->Create_Model();
		}

		if (SceneController::Mouse_right_keyPressed(window))
		{
			Model* model = new Model(triangle, sizeof(triangle), phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture");
			SceneController::PlaceObj_Mouse_right_keyPressed(window, models_vec, camera, model, material1, l);
		}

		SceneController::FlashLightControls(window, l);
		SceneController::RemoveGold_E_keyPressed(window, models_vec);
		SceneController::RemoveObj_Q_keyPressed(window, models_vec);
		SceneController::ChangeLight_L_keyPressed(window, l);


		glfwPollEvents();
		glfwSwapBuffers(window);

	}


	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Scene::Scene_no8(GLFWwindow* window)
{
	glm::vec4 lightColor = glm::vec4(1.0, 1.0, 1.0, 0.0); // Barva světla
	glm::vec3 lightPosition = glm::vec3(0.0, 0.0, 2.0); // Pozice světla
	glm::vec3 lightDirection = glm::vec3(0.0, -1.0, -1.0);
	float ambientStrength = 0.2f; // Síla svítivosti objektu
	float specularStrength = 0.5f; // Síla zrcadlového odrazu
	float shininess = 32.0f; // Lesk (bílá tečka -> větší float = menší bílé světlo)
	float typeLight = 4;
	float light_on = 0;
	std::vector<Model*> grass_vec;
	std::vector<Model*> tree_vec;
	std::vector<Model*> cat_vec;
	std::vector<Model*> gold_vec;
	std::vector<Model*> model_vec;

	const char* phong_texture_vert_path = "./Shaders/phongTextureLightTest.vert";
	const char* phong_texture_frag_path = "./Shaders/phongTextureLightTest.frag";

	const char* texturePathWood = "./Textures/Cat.jpg";
	const char* texturePathWood_tower = "./Textures/Wood_Tower_Col.jpg";
	const char* texturePath_landScape = "./Textures/grass.png";
	const char* texturePath_castle = "./Textures/castle.jpg";
	const char* texturePath_altan = "./Textures/altan.jpg";
	const char* texturePath_eiffel = "./Textures/eiffel.jpg";
	const char* texturePath_pingu = "./Textures/pingu.jpg";
	const char* texturePath_small_house = "./Textures/small_house.jpg";
	const char* texturePath_big_house = "./Textures/model.png";
	const char* texturePath_zombie = "./Textures/zombie.png";
	const char* texturePath_tree = "./Textures/tree.png";
	const char* texturePath_gold = "./Textures/gold.jpg";

	std::string model_path = "./Models/3D_Models/Cat.obj";
	std::string model_path_tower = "./Models/3D_Models/wooden_watch_tower.obj";
	std::string plane = "./Models/3D_Models/land.obj";
	std::string castle = "./Models/3D_Models/castle.obj";
	std::string altan_o = "./Models/3D_Models/altan.obj";
	std::string eiffel_o = "./Models/3D_Models/eiffel.obj";
	std::string pingu_o = "./Models/3D_Models/pingu.obj";
	std::string small_house_o = "./Models/3D_Models/small_house.obj";
	std::string big_house_o = "./Models/3D_Models/model.obj";
	std::string zombie_o = "./Models/3D_Models/zombie.obj";
	std::string tree_o = "./Models/3D_Models/tree.obj";
	std::string gold_o = "./Models/3D_Models/gold.obj";

	Model* plan = new Model(plain_texture, sizeof(plain_texture), phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture");
	plan->addTransform(new Scale(glm::vec3(100.0f)));
	plan->addTransform(new Translate(glm::vec3(0.0f, -1.0f, 0.0f)));

	Model* land = new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", plane);
	//land->addTransform(new Rotate(glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0.0f));
	land->addTransform(new Rotate(glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	land->addTransform(new Scale(glm::vec3(10.0f)));
	land->addTransform(new Translate(glm::vec3(0.0f, -1.0f, -10.0f)));

	Model* castle_m = new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", castle);
	//castle_m->addTransform(new Rotate(glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0.0f));
	castle_m->addTransform(new Rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.0f));
	castle_m->addTransform(new Scale(glm::vec3(0.001f)));
	castle_m->addTransform(new Translate(glm::vec3(0.0f, -1.0f, 0.0f)));

	Model* cat = new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", model_path);
	cat->addTransform(new Rotate(glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0.0f));
	cat->addTransform(new Rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.0f));
	cat->addTransform(new Scale(glm::vec3(0.001f)));
	cat->addTransform(new Translate(glm::vec3(0.0f, -1.0f, 3.0f)));
	//cat->addTransform(new Line(0.001f, 0.005f, glm::vec3(0.0f, -1.0f, 3.0f), glm::vec3(0.0f, 0.0f, 3.0f)));

	Model* tower = new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", model_path_tower);
	tower->addTransform(new Scale(glm::vec3(0.07f)));
	tower->addTransform(new Translate(glm::vec3(1.0f, -1.0f, 0.0f)));

	Model* tower2 = new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", model_path_tower);
	tower2->addTransform(new Scale(glm::vec3(0.07f)));
	tower2->addTransform(new Translate(glm::vec3(4.0f, -1.0f, -1.0f)));

	Model* altan = new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", altan_o);
	altan->addTransform(new Scale(glm::vec3(0.0007f)));
	altan->addTransform(new Rotate(glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0.0f));
	altan->addTransform(new Rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.0f));
	altan->addTransform(new Translate(glm::vec3(4.0f, -0.58f, -4.0f)));

	Model* eiffel = new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", eiffel_o);
	eiffel->addTransform(new Scale(glm::vec3(0.00007f)));
	eiffel->addTransform(new Rotate(glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0.0f));
	eiffel->addTransform(new Rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.0f));
	eiffel->addTransform(new Translate(glm::vec3(-4.0f, 0.4f, -4.2f)));

	Model* pingu = new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", pingu_o);
	pingu->addTransform(new Scale(glm::vec3(0.0007f)));
	//pingu->addTransform(new Rotate(glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0.0f));
	pingu->addTransform(new Rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.0f));
	pingu->addTransform(new Translate(glm::vec3(0.0f, -1.0f, 1.0f)));
	//pingu->addTransform(new Line(0.0001f, 0.0005f, glm::vec3(0.0f, -1.0f, 1.0f), glm::vec3(1.0f, -1.0f, 1.0f)));

	Model* small_house = new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", small_house_o);
	small_house->addTransform(new Scale(glm::vec3(0.0007f)));
	small_house->addTransform(new Rotate(glm::radians(60.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0.0f));
	small_house->addTransform(new Rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.0f));
	small_house->addTransform(new Translate(glm::vec3(-2.0f, -1.0f, 2.0f)));

	Model* big_house = new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", big_house_o);
	big_house->addTransform(new Scale(glm::vec3(0.07f)));
	big_house->addTransform(new Rotate(glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	//big_house->addTransform(new Rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.0f));
	big_house->addTransform(new Translate(glm::vec3(2.0f, -1.0f, 2.0f)));

	Model* zombie = new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", zombie_o);
	zombie->addTransform(new Scale(glm::vec3(0.07f)));
	zombie->addTransform(new Rotate(glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	//big_house->addTransform(new Rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.0f));
	zombie->addTransform(new Translate(glm::vec3(1.8f, -1.0f, 3.0f)));

	//small houses
	Model* small_house_1 = new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", small_house_o);
	small_house_1->addTransform(new Scale(glm::vec3(0.0007f)));
	small_house_1->addTransform(new Rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.0f));
	small_house_1->addTransform(new Translate(glm::vec3(-2.0f, -1.0f, 1.0f)));

	Model* small_house_2 = new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", small_house_o);
	small_house_2->addTransform(new Scale(glm::vec3(0.0007f)));
	small_house_2->addTransform(new Rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.0f));
	small_house_2->addTransform(new Translate(glm::vec3(-3.0f, -1.0f, 0.0f)));

	Model* small_house_3 = new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", small_house_o);
	small_house_3->addTransform(new Scale(glm::vec3(0.0007f)));
	small_house_3->addTransform(new Rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.0f));
	small_house_3->addTransform(new Translate(glm::vec3(-2.0f, -1.0f, -2.0f)));

	//zombie walk
	Model* zombie_1 = new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", zombie_o);
	zombie_1->addTransform(new Scale(glm::vec3(0.07f)));
	//zombie_1->addTransform(new Rotate(glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	//zombie_1->addTransform(new Translate(glm::vec3(1.0f, -1.0f, 3.0f)));
	zombie_1->addTransform(new Line(0.001f, 0.005f, glm::vec3(0.0f, -1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 2.0f)));

	//trees
	Model* tree = new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", tree_o);
	tree->addTransform(new Scale(glm::vec3(0.07f)));
	tree->addTransform(new Translate(glm::vec3(0.0f, -1.0f, 3.0f)));

	for (int i = 0; i < 20; i++)
	{
		tree_vec.push_back(new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", tree_o));
	}

	std::vector<glm::vec3> move_vec;
	move_vec.push_back(glm::vec3(1, -1, 3));
	move_vec.push_back(glm::vec3(0, -1, 5));
	move_vec.push_back(glm::vec3(-1, -1, 4));
	move_vec.push_back(glm::vec3(-2, -1, 2));
	Model* zombie_2 = new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", zombie_o);
	zombie_2->addTransform(new Scale(glm::vec3(0.07f)));
	//zombie_1->addTransform(new Rotate(glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f));
	//zombie_1->addTransform(new Translate(glm::vec3(1.0f, -1.0f, 3.0f)));
	zombie_2->addTransform(new BezierLine(move_vec, 0.001f, 0.005f));

	for (int i = 0; i < 20; i++)
	{
		//gold_vec.push_back(new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", model_path));
		grass_vec.push_back(new Model(bushes, sizeof(bushes), phong_vert_path2, phong_frag_path2, "phong_lights"));
		cat_vec.push_back(new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", model_path));
	}

	Model* skybox = new Model(skycube, sizeof(skycube), skybox_texture_vert_path, skybox_texture_frag_path, "", "skybox");
	std::vector<const char*> texturePathsSkybox = {
		"./Textures/right.jpg",
		"./Textures/left.jpg",
		"./Textures/top.jpg",
		"./Textures/bottom.jpg",
		"./Textures/front.jpg",
		"./Textures/back.jpg"
	};


	model_vec.push_back(skybox);
	for (int i = 1; i < 20; i++)
	{
		//gold_vec.push_back(new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", gold_o));
		model_vec.push_back(new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", gold_o));
	}

	model_vec.push_back(land);
	model_vec.push_back(zombie);
	model_vec.push_back(castle_m);
	model_vec.push_back(cat);
	model_vec.push_back(tower);
	model_vec.push_back(tower2);
	model_vec.push_back(altan);
	model_vec.push_back(pingu);
	model_vec.push_back(small_house);
	model_vec.push_back(big_house);
	model_vec.push_back(eiffel);

	Material* materialSkybox = new Material(texturePathsSkybox);
	materialSkybox->attach(skybox->getShaderProgram());
	materialSkybox->setTextureSkybox();

	Camera* camera = new Camera(glm::vec3(0.0, 0.0, 5.0), glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 1.0, 0.0));
	camera->attach(plan->getShaderProgram());
	camera->attach(castle_m->getShaderProgram());
	camera->attach(cat->getShaderProgram());
	camera->attach(tower->getShaderProgram());
	camera->attach(tower2->getShaderProgram());
	camera->attach(land->getShaderProgram());
	camera->attach(skybox->getShaderProgram());
	camera->attach(altan->getShaderProgram());
	camera->attach(eiffel->getShaderProgram());
	camera->attach(pingu->getShaderProgram());
	camera->attach(small_house->getShaderProgram());
	camera->attach(small_house_1->getShaderProgram());
	camera->attach(small_house_2->getShaderProgram());
	camera->attach(small_house_3->getShaderProgram());
	camera->attach(big_house->getShaderProgram());
	camera->attach(zombie->getShaderProgram());
	camera->attach(zombie_1->getShaderProgram());
	camera->attach(zombie_2->getShaderProgram());
	camera->attach(tree->getShaderProgram());

	Material* material = new Material(texturePathWood);
	material->attach(cat->getShaderProgram());
	for (int i = 0; i < 20; i++)
	{
		material->attach(cat_vec[i]->getShaderProgram());
	}
	material->setTexture();

	Material* material_tower = new Material(texturePathWood_tower);
	material_tower->attach(tower->getShaderProgram());
	material_tower->attach(tower2->getShaderProgram());
	material_tower->setTexture();

	Material* material_land = new Material(texturePath_landScape);
	material_land->attach(land->getShaderProgram());
	material_land->setTexture();

	Material* material_grass = new Material(texturePath_landScape);
	material_grass->attach(plan->getShaderProgram());
	material_grass->setTextureRepeat(1000);
	material_grass->setTexture();

	Material* material_castle = new Material(texturePath_castle);
	material_castle->attach(castle_m->getShaderProgram());
	material_castle->setTexture();

	Material* material_altan = new Material(texturePath_altan);
	material_altan->attach(altan->getShaderProgram());
	material_altan->setTexture();

	Material* material_eiffel = new Material(texturePath_eiffel);
	material_eiffel->attach(eiffel->getShaderProgram());
	material_eiffel->setTexture();

	Material* material_pingu = new Material(texturePath_pingu);
	material_pingu->attach(pingu->getShaderProgram());
	material_pingu->setTexture();

	Material* material_small_house = new Material(texturePath_small_house);
	material_small_house->attach(small_house->getShaderProgram());
	material_small_house->attach(small_house_1->getShaderProgram());
	material_small_house->attach(small_house_2->getShaderProgram());
	material_small_house->attach(small_house_3->getShaderProgram());
	material_small_house->setTexture();

	Material* material_big_house = new Material(texturePath_big_house);
	material_big_house->attach(big_house->getShaderProgram());
	material_big_house->setTexture();

	Material* material_zombie = new Material(texturePath_zombie);
	material_zombie->attach(zombie->getShaderProgram());
	material_zombie->attach(zombie_1->getShaderProgram());
	material_zombie->attach(zombie_2->getShaderProgram());
	material_zombie->setTexture();

	Material* material_plant = new Material(glm::vec4(0.0f, 1.0f, 0.3f, 1.0f));
	for (int i = 0; i < 20; i++)
	{
		material_plant->attach(grass_vec[i]->getShaderProgram());
		material_plant->setColor();
	}

	Material* material_gold = new Material(texturePath_gold);
	for (int i = 1; i < 20; i++)
	{
		material_gold->attach(model_vec[i]->getShaderProgram());
		material_gold->setTexture();
	}

	Material* material_tree = new Material(texturePath_tree);
	material_tree->attach(tree->getShaderProgram());
	for (int i = 0; i < 20; i++)
	{
		material_tree->attach(tree_vec[i]->getShaderProgram());
	}
	material_tree->setTexture();


	Light* l = new Light(lightPosition, lightColor, lightDirection, ambientStrength, specularStrength, shininess, typeLight, light_on);
	l->attach(plan->getShaderProgram());
	l->attach(cat->getShaderProgram());
	l->attach(tower->getShaderProgram());
	l->attach(tower2->getShaderProgram());
	l->attach(land->getShaderProgram());
	l->attach(castle_m->getShaderProgram());
	l->attach(altan->getShaderProgram());
	l->attach(eiffel->getShaderProgram());
	l->attach(pingu->getShaderProgram());
	l->attach(small_house->getShaderProgram());
	l->attach(small_house_1->getShaderProgram());
	l->attach(small_house_2->getShaderProgram());
	l->attach(small_house_3->getShaderProgram());
	l->attach(big_house->getShaderProgram());
	l->attach(zombie->getShaderProgram());
	l->attach(zombie_1->getShaderProgram());
	l->attach(zombie_2->getShaderProgram());
	l->attach(tree->getShaderProgram());

	for (int i = 0; i < 20; i++)
	{
		l->attach(tree_vec[i]->getShaderProgram());
	}
	for (int i = 1; i < 20; i++)
	{
		l->attach(model_vec[i]->getShaderProgram());
	}
	for (int i = 0; i < 20; i++)
	{
		l->attach(grass_vec[i]->getShaderProgram());
	}
	for (int i = 0; i < 20; i++)
	{
		l->attach(tree_vec[i]->getShaderProgram());
	}
	l->refrestLight();

	for (int i = 0; i < 20; i++)
	{
		float randomX = static_cast<float>(rand()) / RAND_MAX;
		float randomZ = static_cast<float>(rand()) / RAND_MAX;
		float randomScale = static_cast<float>(rand()) / RAND_MAX;
		float randomRotation = glm::linearRand(-glm::pi<float>(), glm::pi<float>());
		float newX = randomX * 50.0 - 20.0;
		float newZ = randomZ * 50.0 - 20.0;
		float scale = randomScale * 0.9 + 0.1;
		tree_vec[i]->addTransform(new Rotate(glm::radians(randomRotation), glm::vec3(1.0f, 0.0f, 0.0f), 0.0f));
		tree_vec[i]->addTransform(new Scale(glm::vec3(0.07f)));
		tree_vec[i]->addTransform(new Translate(glm::vec3(newX, -1.0f, newZ)));
		camera->attach(tree_vec[i]->getShaderProgram());
	}

	for (int i = 0; i < 20; i++)
	{
		float randomX = static_cast<float>(rand()) / RAND_MAX;
		float randomZ = static_cast<float>(rand()) / RAND_MAX;
		float randomScale = static_cast<float>(rand()) / RAND_MAX;
		float randomRotation = glm::linearRand(-glm::pi<float>(), glm::pi<float>());
		float newX = randomX * 50.0 - 20.0;
		float newZ = randomZ * 50.0 - 20.0;
		float scale = randomScale * 0.9 + 0.1;
		grass_vec[i]->addTransform(new Rotate(glm::radians(randomRotation), glm::vec3(1.0f, 0.0f, 0.0f), 0.0f));
		grass_vec[i]->addTransform(new Translate(glm::vec3(newX, -1.0f, newZ)));
		camera->attach(grass_vec[i]->getShaderProgram());
	}

	for (int i = 1; i < 20; i++)
	{
		float randomX = static_cast<float>(rand()) / RAND_MAX;
		float randomZ = static_cast<float>(rand()) / RAND_MAX;
		float randomScale = static_cast<float>(rand()) / RAND_MAX;
		float randomRotation = glm::linearRand(-glm::pi<float>(), glm::pi<float>());
		float newX = randomX * 50.0 - 20.0;
		float newZ = randomZ * 50.0 - 20.0;
		float scale = randomScale * 0.9 + 0.1;
		model_vec[i]->addTransform(new Rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.0f));
		model_vec[i]->addTransform(new Rotate(glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.07f));
		model_vec[i]->addTransform(new Scale(glm::vec3(0.006f)));
		model_vec[i]->addTransform(new Translate(glm::vec3(newX, -1.0f, newZ)));
		camera->attach(model_vec[i]->getShaderProgram());
	}

	//LOADING LOOP
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glClearColor(0.01f, 0.6f, 1.0f, 1);
		bool mouse_click = CallBacks::mouse_callkack(window);

		std::pair<double, double> pos = CallBacks::cursor_callback(window);
		auto currentFrame = static_cast<float>(glfwGetTime());
		camera->mouseMove(pos.first, pos.second, mouse_click);

		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		camera->move(window, deltaTime);
		camera->resizeWindow(window);

		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		skybox->Create_Model();
		glClear(GL_DEPTH_BUFFER_BIT);

		plan->Create_Model();

		for (int i = 1; i < model_vec.size(); i++)
		{
			glStencilFunc(GL_ALWAYS, i, 0xFF);
			model_vec[i]->Create_Model_3D();
		}

		for (int i = 0; i < 20; i++)
		{
			//gold_vec[i]->Create_Model();
			grass_vec[i]->Create_Model();
			tree_vec[i]->Create_Model();
		}

		small_house_1->Create_Model();
		small_house_2->Create_Model();
		small_house_3->Create_Model();
		zombie_1->Create_Model();
		zombie_2->Create_Model();
		tree->Create_Model();

		//int count = 0;
		glm::mat4x3 mat;
		glm::vec3 vec1;
		glm::vec3 vec2;
		glm::vec3 vec3;
		glm::vec3 vec4;
		int count = 0;
		std::vector<glm::vec3> click_pos;

		if (SceneController::M_keyPressed(window))
		{
			std::cout << "M - pressed!" << std::endl;
			int width, height;
			glfwGetFramebufferSize(window, &width, &height);
			GLbyte color[4];
			GLfloat depth;
			GLuint index;

			double x, y;
			glfwGetCursorPos(window, &x, &y);
			y = height - y;

			glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
			glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
			glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
			//printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth % f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);

			glm::vec3 screenX = glm::vec3(x, y, depth);
			glm::mat4 view = camera->getViewMatrix();
			glm::mat4 projection = camera->getProjectionMatrix();
			glm::vec4 viewPort = glm::vec4(0, 0, width, height);
			glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

			std::cout << pos.x << std::endl;

			click_pos.push_back(pos);
			count++;
			if (count == 4)
			{
				Model* model = new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", tree_o);
				model->addTransform(new Scale(glm::vec3(0.06f)));
				model->addTransform(new BezierLine(click_pos, 0.001f, 0.005f));

				material_tree->attach(model->getShaderProgram());
				camera->attach(model->getShaderProgram());
				l->attach(model->getShaderProgram());
				l->refrestLight();
				material_tree->setTexture();
				model_vec.push_back(model);
				//SceneController::PlaceObj_Mouse_right_keyPressed(window, model_vec, camera, model, material_tree, l);
			}
			
		}

		if (SceneController::Mouse_right_keyPressed(window))
		{
			Model* model = new Model(phong_texture_vert_path, phong_texture_frag_path, "phong_lights", "texture", tree_o);
			model->addTransform(new Scale(glm::vec3(0.06f)));
			SceneController::PlaceObj_Mouse_right_keyPressed(window, model_vec, camera, model, material_tree, l);
		}

		SceneController::RemoveGold_E_keyPressed(window, model_vec);
		SceneController::RemoveObj_Q_keyPressed(window, model_vec);
		SceneController::ChangeLight_L_keyPressed(window, l);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
