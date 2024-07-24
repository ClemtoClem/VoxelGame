#include "Game.hpp"
#include <stdexcept>

#include "Core/Logger.hpp"
#include "Core/Color.hpp"

#include "Render3D/Entities/Block.hpp"
#include "Render3D/Entities/Cube.hpp"
#include "Render3D/Entities/Stair.hpp"
#include "Render3D/Entities/InnerStair.hpp"

#include "Render2D/Frame.hpp"
#include "Render2D/Button.hpp"
#include "Render2D/Text.hpp"

using namespace Render2D;
using namespace Render3D;

Game::Game() : _isLoad(false), _running(false), _window("OpenGL with SDL2", 800, 600), _gui() {
	setPerformanceFrequency(60.0f);
}

Game::~Game() {
	closeSDL();
	LOG(Debug) << "Close game success!";
	Logger::destroyInstance();
}

/* - - - - - - - - - - - - - - - - - - - - */

bool Game::init(int argc, char *argv[]) {
	Logger::removeFile();
	Logger::createInstance().enableWriteInTerminal();

	if (!initSDL()) {
		LOG(Fatal) << "Failed to initialize SDL";
		return false;
	}
	if (!initOpenGL()) {
		LOG(Fatal) << "Failed to initialize OpenGL";
		return false;
	}

	// Taille maximale d'un tampon
	GLint maxBufferSize;
	glGetIntegerv(GL_MAX_ELEMENT_INDEX, &maxBufferSize);
	LOG(Info) << "Max element index: " << maxBufferSize;

	// Taille maximale d'un vertex attrib array
	GLint maxVertexAttribs;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);
	LOG(Info) << "Max vertex attribs: " << maxVertexAttribs;

	// Taille maximale d'un vertex attrib stride
	GLint maxVertexAttribStride;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIB_STRIDE, &maxVertexAttribStride);
	LOG(Info) << "Max vertex attrib stride: " << maxVertexAttribStride;

	if (!_scene2D->init()) {
		LOG(Fatal) << "Failed to initialize 2D scene";
		return false;
	}
	
	_camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
	_scene3D = std::make_shared<Scene3D>(_camera);
	if (!_scene3D->init()) {
		LOG(Fatal) << "Failed to initialize 3D scene";
		return false;
	}

	/* Import resources */
	bool result = true;
	result &= _resourcesManager.loadTexture("concrete_front",  IMAGE_PATH + "concrete_front.png");
	result &= _resourcesManager.loadTexture("concrete_back",   IMAGE_PATH + "concrete_back.png");
	result &= _resourcesManager.loadTexture("concrete_left",   IMAGE_PATH + "concrete_left.png");
	result &= _resourcesManager.loadTexture("concrete_right",  IMAGE_PATH + "concrete_right.png");
	result &= _resourcesManager.loadTexture("concrete_top",	IMAGE_PATH + "concrete_top.png");
	result &= _resourcesManager.loadTexture("concrete_bottom", IMAGE_PATH + "concrete_bottom.png");
	result &= _resourcesManager.loadTexture("bricks_wall",	 IMAGE_PATH + "bricks_wall.jpg");
	result &= _resourcesManager.loadTexture("wood_planks",	 IMAGE_PATH + "wood_planks.jpg");

	if (!result) {
		LOG(Fatal) << "Failed to load resources";
		return false;
	}

	LOG(Debug) << "Init game success!";

	return true;
}

bool Game::initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		LOG(Fatal) << "Failed to initialize SDL: " << SDL_GetError();
		return false;
	}

	if (!(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) & (IMG_INIT_JPG | IMG_INIT_PNG))) {
		LOG(Fatal) << "Failed to initialize SDL_image: " << IMG_GetError();
		return false;
	}

	if (TTF_Init() == -1) {
		LOG(Fatal) << "Failed to initialize SDL_ttf: " << TTF_GetError();
		return false;
	}

	if (!_window.init() || !_window.createGLContext()) {
		LOG(Fatal) << "Failed to initialize window";
		return false;
	}

	return true;
}

bool Game::initOpenGL() {
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		LOG(Fatal) << "Failed to initialize GLEW: " << glewGetErrorString(glewError);
		return false;
	}

	// Activer le test de profondeur
	glEnable(GL_DEPTH_TEST);
	// Configurer le test de profondeur pour utiliser le tampon de profondeur
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);

	return true;
}

void Game::closeSDL() {
	_window.free();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

/* - - - - - - - - - - - - - - - - - - - - */

bool Game::load() {
	try {
		if (_isLoad) {
			unload();
		}

		// Load gui

		/*std::shared_ptr<Frame> mainFrame = std::make_shared<Frame>("mainFrame", glm::vec2(5.0f, 5.0f), glm::vec2(120.0f, 100.0f), Color::GRAY3, Color::DARK_GRAY2, 2.0f);
		mainFrame->setRotation(20.0f);
		_scene2D->addChild(mainFrame);

		std::shared_ptr<Button> button = std::make_shared<Button>("button1", FONT_PATH + "arial.ttf", 24, "Click Me", Color::PURPLE2, Color::WHITE);
		button->setHoverBackgroundColor(Color::PURPLE1);
		button->setPosition(glm::vec2(5.0f, 5.0f));
		button->setSize(glm::vec2(110.0f, 30.0f));
		button->setCallback([]() {
			std::cout << "Button clicked!" << std::endl;
		});

		mainFrame->addChild(button);*/

		// Load game resources

		//LOG(Debug) << "Loading game resources...";

		std::array<std::shared_ptr<Texture>, 6> textures_block1 = {
			_resourcesManager.getTexture("concrete_front"),
			_resourcesManager.getTexture("concrete_back"),
			_resourcesManager.getTexture("concrete_left"),
			_resourcesManager.getTexture("concrete_right"),
			_resourcesManager.getTexture("concrete_top"),
			_resourcesManager.getTexture("concrete_bottom")
		};
		for (auto texture : textures_block1) {
			throwIfNullptr<std::shared_ptr<Texture>>(texture, "resources is null");
		}

		std::array<std::shared_ptr<Texture>, 6> textures_block2 = {
			_resourcesManager.getTexture("bricks_wall"),
			_resourcesManager.getTexture("bricks_wall"),
			_resourcesManager.getTexture("bricks_wall"),
			_resourcesManager.getTexture("bricks_wall"),
			_resourcesManager.getTexture("bricks_wall"),
			_resourcesManager.getTexture("bricks_wall")
		};
		for (auto texture : textures_block2) {
			throwIfNullptr<std::shared_ptr<Texture>>(texture, "resources is null");
		}

		std::array<std::shared_ptr<Texture>, 6> textures_block3 = {
			_resourcesManager.getTexture("wood_planks"),
			_resourcesManager.getTexture("wood_planks"),
			_resourcesManager.getTexture("wood_planks"),
			_resourcesManager.getTexture("wood_planks"),
			_resourcesManager.getTexture("wood_planks"),
			_resourcesManager.getTexture("wood_planks")
		};
		for (auto texture : textures_block3) {
			throwIfNullptr<std::shared_ptr<Texture>>(texture, "resources is null");
		}

		_camera->setPosition(glm::vec3(0.0f, 0.0f, 3.0f));

		// Créer une source de lumière directionnelle (similaire au soleil)
		std::shared_ptr<Light> directionalLight = std::make_shared<Light>();
		glm::vec3 lightDirection = glm::normalize(glm::vec3(-1.0f, -1.0f, -1.0f));  // Direction de la lumière (vers le haut à gauche)
		glm::vec3 lightColor = glm::vec3(1.0f, 0.8f, 0.6f);  // Couleur jaune orangée
		directionalLight->SetDirectionalLight(lightDirection, lightColor);
		_scene3D->addLight(directionalLight);

		// générer un plateau de blocks
		int plateauWidth = 40;
		int plateauHeight = 40;
		
		for (int x = -plateauWidth/2; x < plateauWidth/2; x++) {
			for (int z = -plateauHeight/2; z < plateauHeight/2; z++) {
				std::shared_ptr<Entity> block = std::make_shared<Cube>(glm::vec3(x, 0, z), textures_block1);
				_scene3D->addEntity(block);
			}
		}

		// Créez des murs en briques
		int wallX = -5;
		int wallY = -6;
		int wallZ = 1;
		int wallWidth = 8;
		int wallHeight = 8;
		int wallDepth = 3;
		int x, y, z;
		for (int k = 0; k < wallDepth; k++) {
			z = wallZ + k;
			for (int i = 1; i<wallWidth-1; i++) {
				x = wallX + i;
				std::shared_ptr<Entity> wall_block1 = std::make_shared<Cube>(glm::vec3(x, z, wallY), textures_block2);
				_scene3D->addEntity(wall_block1);
				std::shared_ptr<Entity> wall_block2 = std::make_shared<Cube>(glm::vec3(x, z, wallY+wallHeight-1), textures_block2);
				_scene3D->addEntity(wall_block2);
			}
			for (int j = 0; j<wallHeight; j++) {
				y = wallY + j;
				std::shared_ptr<Entity> wall_block1 = std::make_shared<Cube>(glm::vec3(wallX, z, y), textures_block2);
				_scene3D->addEntity(wall_block1);
				std::shared_ptr<Entity> wall_block2 = std::make_shared<Cube>(glm::vec3(wallX+wallWidth-1, z, y), textures_block2);
				_scene3D->addEntity(wall_block2);
			}
		}
		for (int i = 1; i<wallWidth-1; i++) {
			x = wallX + i;
			for (int j = 0; j<wallHeight; j++) {
				y = wallY + j;
				std::shared_ptr<Entity> floor_block = std::make_shared<Cube>(glm::vec3(x, wallZ, y), textures_block3);
				_scene3D->addEntity(floor_block);
			}
		}
		for (int i = 0; i<wallWidth; i++) {
			x = wallX + i;
			std::shared_ptr<Entity> stair_block1 = std::make_shared<Stair>(glm::vec3(x, wallZ, wallY+wallHeight), textures_block3);
			_scene3D->addEntity(stair_block1);
			std::shared_ptr<Entity> stair_block2 = std::make_shared<Stair>(glm::vec3(x, wallZ, wallY-1), textures_block3);
			stair_block2->rotate(180.0f, AxisY); // rotation autour de l'axe y
			_scene3D->addEntity(stair_block2);

		}


		std::shared_ptr<Entity> inner_stair_block1 = std::make_shared<InnerStair>(glm::vec3(-18,1,-18), textures_block3);
		inner_stair_block1->rotate(0.0f, AxisY); // rotation autour de l'axe y
		_scene3D->addEntity(inner_stair_block1);
		std::shared_ptr<Entity> inner_stair_block2 = std::make_shared<InnerStair>(glm::vec3(-18,1,-17), textures_block3);
		inner_stair_block2->rotate(90.0f, AxisY); // rotation autour de l'axe y
		_scene3D->addEntity(inner_stair_block2);
		std::shared_ptr<Entity> inner_stair_block3 = std::make_shared<InnerStair>(glm::vec3(-17,1,-18), textures_block3);
		inner_stair_block3->rotate(180.0f, AxisY); // rotation autour de l'axe y
		_scene3D->addEntity(inner_stair_block3);
		std::shared_ptr<Entity> inner_stair_block4 = std::make_shared<InnerStair>(glm::vec3(-17,1,-17), textures_block3);
		inner_stair_block4->rotate(270.0f, AxisY); // rotation autour de l'axe y
		_scene3D->addEntity(inner_stair_block4);


		_camera->setPosition(glm::vec3(0.0f, 3.0f, 3.0f));

		_isLoad = true;

		LOG(Debug) << "Load game success!";
	} catch (std::exception &e) {
		LOG(Error) << "Load game failed: " << e.what();
	}
	
	return _isLoad;
}

void Game::unload() {
	if (_isLoad) {
		_scene2D->reset();
		_scene3D->reset();
		_isLoad = false;
	}
}

void Game::setPerformanceFrequency(float frequency) {
	_performanceFrequency = frequency;
	_performancePeriod = 1.0f / frequency;
}

/* - - - - - - - - - - - - - - - - - - - - */

void Game::run(int argc, char *argv[]) {
	if (!init(argc, argv)) {
		return;
	}

	if (!load()) {
		return;
	}

	SDL_Event event;
	float deltaTime = 0.0f;

	Camera::Movement cameraMovement = static_cast<Camera::Movement>(0);

	bool mouseCaptured = true;
	bool firstMouse = true;

	if (mouseCaptured) {
		SDL_SetRelativeMouseMode(SDL_TRUE);
		_window.warpMouseCenter();
		firstMouse = true;
	}
	_scene2D->setScreenSize(_window.getWidth(), _window.getHeight());

	_running = true;

	while (_running) {
		Uint64 startTime = SDL_GetTicks64();

		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				_running = false;
			} else if (event.type == SDL_WINDOWEVENT) {
				_window.handleEvent(event);
			} else if (event.type == SDL_MOUSEMOTION) {
				if (mouseCaptured) {
					float xpos = event.motion.x;
					float ypos = event.motion.y;

					float xoffset = 0.0f, yoffset = 0.0f;
					if (!firstMouse) {
						xoffset = xpos - _window.getCenterX();
						yoffset = _window.getCenterY() - ypos; // Reversed since y-coordinates go from bottom to top
					} else {
						firstMouse = false;
					}

					if (xoffset != 0.0f || yoffset != 0.0f) {
						_camera->processMouseMovement(xoffset, yoffset);
						_window.warpMouseCenter();
					}
				}
			} else if (event.type == SDL_MOUSEWHEEL) {
				_camera->processMouseScroll(event.wheel.y);
			} else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						_running = false;
						break;
					case SDLK_z:
						cameraMovement = static_cast<Camera::Movement>(cameraMovement | Camera::FORWARD);
						break;
					case SDLK_s:
						cameraMovement = static_cast<Camera::Movement>(cameraMovement | Camera::BACKWARD);
						break;
					case SDLK_q:
						cameraMovement = static_cast<Camera::Movement>(cameraMovement | Camera::LEFT);
						break;
					case SDLK_d:
						cameraMovement = static_cast<Camera::Movement>(cameraMovement | Camera::RIGHT);
						break;
					case SDLK_e:
						cameraMovement = static_cast<Camera::Movement>(cameraMovement | Camera::DOWN);
						break;
					case SDLK_SPACE:
						cameraMovement = static_cast<Camera::Movement>(cameraMovement | Camera::UP);
						break;
					case SDLK_LSHIFT:
						_camera->movementSpeedUp();
						break;
					case SDLK_F1:
						mouseCaptured = !mouseCaptured;
						SDL_SetRelativeMouseMode(mouseCaptured ? SDL_TRUE : SDL_FALSE);
						if (mouseCaptured) {
							_window.warpMouseCenter();
							firstMouse = true;
						}
						break;
				}
			} else if (event.type == SDL_KEYUP) {
				switch (event.key.keysym.sym) {
					case SDLK_z:
						cameraMovement = static_cast<Camera::Movement>(cameraMovement & ~Camera::FORWARD);
						break;
					case SDLK_s:
						cameraMovement = static_cast<Camera::Movement>(cameraMovement & ~Camera::BACKWARD);
						break;
					case SDLK_q:
						cameraMovement = static_cast<Camera::Movement>(cameraMovement & ~Camera::LEFT);
						break;
					case SDLK_d:
						cameraMovement = static_cast<Camera::Movement>(cameraMovement & ~Camera::RIGHT);
						break;
					case SDLK_e:
						cameraMovement = static_cast<Camera::Movement>(cameraMovement & ~Camera::DOWN);
						break;
					case SDLK_SPACE:
						cameraMovement = static_cast<Camera::Movement>(cameraMovement & ~Camera::UP);
						break;
					case SDLK_LSHIFT:
						_camera->movementSpeedDown();
						break;
				}
			}

			_scene2D->handleEvent(event);
			_scene3D->handleEvent(event);
		}

		// Mettre à jour la scène 2D
		_scene2D->update(deltaTime);

		// Mettre à jour la position de la caméra
		_camera->processKeyboard(deltaTime, cameraMovement);
		// Mettre à jour la scène 3D
		_scene3D->update(deltaTime);

		// Effacer le tampon de couleur et le tampon de profondeur
		glClearColor(Color::SKY_BLUE.r, Color::SKY_BLUE.g, Color::SKY_BLUE.b, Color::SKY_BLUE.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Rendu de la scène 3D
		_scene3D->render(_window.getRatio());

		// Rendu de la scène 2D
		_scene2D->render();

		// Échange des buffers et mise à jour de l'écran
		_window.GLSwap();

		SDL_Delay((deltaTime < _performancePeriod) ? (_performancePeriod - deltaTime) : 0);

		Uint64 endTime = SDL_GetTicks64();
		deltaTime = (endTime - startTime) / 1000.0f;
	}

	unload();
}
