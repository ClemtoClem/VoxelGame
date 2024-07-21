#include "Game.hpp"
#include <stdexcept>

#include "Core/Logger.hpp"
#include "Core/Block.hpp"
#include "Core/Color.hpp"

#include "GUI/Frame.hpp"
#include "GUI/Button.hpp"
#include "GUI/Text.hpp"

Game::Game()
 : _isLoad(false), _running(false), _window("OpenGL with SDL2", 800, 600), _gui() {}

Game::~Game() {
	closeSDL();
	LOG(Debug) << "Close game success!";
	Logger::destroyInstance();
}

/* - - - - - - - - - - - - - - - - - - - - */

bool Game::init(int argc, char *argv[]) {
	Logger::removeFile();
	Logger::createInstance();
	Logger::getInstance().enableWriteInTerminal();

	if (!initSDL()) {
		LOG(Fatal) << "Failed to initialize SDL" << std::endl;
		return false;
	}
	if (!initOpenGL()) {
		LOG(Fatal) << "Failed to initialize OpenGL" << std::endl;
		return false;
	}

	if (!_gui.init()) {
		LOG(Fatal) << "Failed to initialize GUI" << std::endl;
		return false;
	}
	
	_camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
	_scene = std::make_shared<Scene>(_camera);
	if (!_scene->init()) {
		LOG(Fatal) << "Failed to initialize scene" << std::endl;
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
		LOG(Fatal) << "Failed to initialize window" << std::endl;
		return false;
	}

	return true;
}

bool Game::initOpenGL() {
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		LOG(Fatal) << "Failed to initialize GLEW: " << glewGetErrorString(glewError) << std::endl;
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
		_gui.addChild(mainFrame);

		std::shared_ptr<Button> button = std::make_shared<Button>("button1", FONT_PATH + "arial.ttf", 24, "Click Me", Color::PURPLE2, Color::WHITE);
		button->setHoverBackgroundColor(Color::PURPLE1);
		button->setPosition(glm::vec2(5.0f, 5.0f));
		button->setSize(glm::vec2(110.0f, 30.0f));
		button->setCallback([]() {
			std::cout << "Button clicked!" << std::endl;
		});

		mainFrame->addChild(button);*/

		// Load game resources

		std::array<std::string, 6> textureFiles = {
			IMAGE_PATH + "concrete_front.png",
			IMAGE_PATH + "concrete_back.png",
			IMAGE_PATH + "concrete_left.png",
			IMAGE_PATH + "concrete_right.png",
			IMAGE_PATH + "concrete_top.png",
			IMAGE_PATH + "concrete_bottom.png"
		};
		_camera->setPosition(glm::vec3(0.0f, 0.0f, 3.0f));

		// Créer une source de lumière directionnelle (similaire au soleil)
		std::shared_ptr<Light> directionalLight = std::make_shared<Light>();
		glm::vec3 lightDirection = glm::normalize(glm::vec3(-1.0f, -1.0f, -1.0f));  // Direction de la lumière (vers le haut à gauche)
		glm::vec3 lightColor = glm::vec3(1.0f, 0.8f, 0.6f);  // Couleur jaune orangée
		directionalLight->SetDirectionalLight(lightDirection, lightColor);
		_scene->addLight(directionalLight);

		// générer un plateau de blocks
		int plateauWidth = 10;
		int plateauHeight = 10;
		
		for (int x = -plateauWidth/2; x < plateauWidth/2; x++) {
			for (int z = -plateauHeight/2; z < plateauHeight/2; z++) {
				std::shared_ptr<Entity> block = std::make_shared<Block>(glm::vec3(x, 0, z), textureFiles);
				_scene->addEntity(block);
			}
		}

		// Créez des blocks
		std::shared_ptr<Entity> block1 = std::make_shared<Block>(glm::vec3(1, 1, 1), textureFiles);
		std::shared_ptr<Entity> block2 = std::make_shared<Block>(glm::vec3(2, 2, 2), textureFiles);
		
		_scene->addEntity(block1);
		_scene->addEntity(block2);

		_isLoad = true;

		LOG(Debug) << "Load game success!";
	} catch (std::exception &e) {
		LOG(Error) << "Load game failed: " << e.what();
	}
	
	return _isLoad;
}

void Game::unload() {
	if (_isLoad) {
		_gui.deleteChilden();
		_scene->reset();
		_isLoad = false;
	}
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
	_gui.setScreenSize(_window.getWidth(), _window.getHeight());

	_running = true;

	while (_running) {
		auto startTime = std::chrono::high_resolution_clock::now();
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
					case SDLK_LSHIFT:
						cameraMovement = static_cast<Camera::Movement>(cameraMovement | Camera::DOWN);
						break;
					case SDLK_SPACE:
						cameraMovement = static_cast<Camera::Movement>(cameraMovement | Camera::UP);
						break;
					case SDLK_e:
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
						cameraMovement = static_cast<Face>(cameraMovement & ~Camera::FORWARD);
						break;
					case SDLK_s:
						cameraMovement = static_cast<Face>(cameraMovement & ~Camera::BACKWARD);
						break;
					case SDLK_q:
						cameraMovement = static_cast<Face>(cameraMovement & ~Camera::LEFT);
						break;
					case SDLK_d:
						cameraMovement = static_cast<Face>(cameraMovement & ~Camera::RIGHT);
						break;
					case SDLK_LSHIFT:
						cameraMovement = static_cast<Face>(cameraMovement & ~Camera::DOWN);
						break;
					case SDLK_SPACE:
						cameraMovement = static_cast<Face>(cameraMovement & ~Camera::UP);
						break;
				}
			}

			_gui.handleEvent(event);
		}

		// Mettre à jour la caméra, la scène et les widgets
		_camera->processKeyboard(deltaTime, cameraMovement);
		_scene->update(deltaTime);
		_gui.update(deltaTime);

		// Effacer le tampon de couleur et le tampon de profondeur
		glClearColor(Color::SKY_BLUE.r, Color::SKY_BLUE.g, Color::SKY_BLUE.b, Color::SKY_BLUE.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Rendre la scène 3D
		_scene->render(_window.getRatio());

		// Rendre l'interface utilisateur
		_gui.render();

		_window.GLSwap();

		SDL_Delay(4);

		deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now() - startTime).count();
	}

	unload();
}
