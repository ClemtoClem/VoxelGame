#include "Game.hpp"
#include <stdexcept>

Game::Game()
 : _isLoad(false), _running(false), _window("OpenGL with SDL2", 800, 600) {}

Game::~Game() {
    closeSDL();
    Logger::destroyInstance();
}

void Game::run(int argc, char *argv[]) {
    if (!init(argc, argv)) {
        return;
    }

    if (!load()) {
        return;
    }

    SDL_Event event;
    float deltaTime = 0.0f;

    bool moveForward = false;
    bool moveBackward = false;
    bool moveLeft = false;
    bool moveRight = false;
    bool moveDown = false;
    bool moveUp = false;

    bool mouseCaptured = true;

    if (mouseCaptured) {
        SDL_SetRelativeMouseMode(SDL_TRUE);
        _window.warpMouseCenter();
    }

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

                    float xoffset = xpos - _window.getCenterX();
                    float yoffset = _window.getCenterY() - ypos; // Reversed since y-coordinates go from bottom to top

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
                        moveForward = true;
                        break;
                    case SDLK_s:
                        moveBackward = true;
                        break;
                    case SDLK_q:
                        moveLeft = true;
                        break;
                    case SDLK_d:
                        moveRight = true;
                        break;
                    case SDLK_LSHIFT:
                        moveDown = true;
                        break;
                    case SDLK_SPACE:
                        moveUp = true;
                        break;
                    
                    case SDLK_e:
                        mouseCaptured = !mouseCaptured;
                        SDL_SetRelativeMouseMode(mouseCaptured ? SDL_TRUE : SDL_FALSE);
                        if (mouseCaptured) {
                            _window.warpMouseCenter();
                        }
                        break;
                }
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_z:
                        moveForward = false;
                        break;
                    case SDLK_s:
                        moveBackward = false;
                        break;
                    case SDLK_q:
                        moveLeft = false;
                        break;
                    case SDLK_d:
                        moveRight = false;
                        break;
                    case SDLK_LSHIFT:
                        moveDown = false;
                        break;
                    case SDLK_SPACE:
                        moveUp = false;
                        break;
                }
            }
        }

        _camera->processKeyboard(deltaTime, moveForward, moveBackward, moveLeft, moveRight, moveDown, moveUp);

        _scene->update(deltaTime);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _scene->render(_window.getRatio());

        _window.GLSwap();

        SDL_Delay(4);

        deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now() - startTime).count();
    }

    unload();
}

bool Game::init(int argc, char *argv[]) {
    Logger::createInstance();
    Logger::getInstance().enableWriteInTerminal();

    if (!initSDL()) {
        LOG(Fatal) << "Failed to initialize SDL and OpenGL" << std::endl;
        return false;
    }

    _shader = std::make_shared<Shader>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader.glsl");
    _camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
    _scene = std::make_shared<Scene>(_camera, _shader);

    LOG(Debug) << "Init game success!";

    return true;
}

bool Game::load() {
    if (_isLoad) {
        unload();
    }

    std::array<std::string, 6> textureFiles = {
        "./res/concrete_front.png",
        "./res/concrete_back.png",
        "./res/concrete_left.png",
        "./res/concrete_right.png",
        "./res/concrete_top.png",
        "./res/concrete_bottom.png"
    };

    try {
        std::shared_ptr<Entity> block1 = std::make_shared<Block>(glm::vec3(0, 0, 0), textureFiles);
        std::shared_ptr<Entity> block2 = std::make_shared<Block>(glm::vec3(1, 1, 1), textureFiles);

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
        _scene->reset();
        _isLoad = false;
    }
}

bool Game::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        LOG(Fatal) << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) & (IMG_INIT_JPG | IMG_INIT_PNG))) {
        LOG(Fatal) << "Failed to initialize SDL_image: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    if (!_window.init() || !_window.createGLContext()) {
        return false;
    }

    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        LOG(Fatal) << "Failed to initialize GLEW: " << glewGetErrorString(glewError) << std::endl;
        return false;
    }

    return true;
}

void Game::closeSDL() {
    _window.free();
    IMG_Quit();
    SDL_Quit();
}
