#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <iostream>

#include "Logger.hpp"
#include "Scene.hpp"
#include "Block.hpp"
#include <memory>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool initSDL(SDL_Window*& window, SDL_GLContext& context) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		LOG(Fatal) << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		return false;
	}

	if (!(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) & (IMG_INIT_JPG | IMG_INIT_PNG))) {
		LOG(Fatal) << "Failed to initialize SDL_image: " << IMG_GetError() << std::endl;
		SDL_Quit();
		return -1;
	}

	window = SDL_CreateWindow("OpenGL with SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		LOG(Fatal) << "Failed to create window: " << SDL_GetError() << std::endl;
		return false;
	}

	context = SDL_GL_CreateContext(window);
	if (context == nullptr) {
		LOG(Fatal) << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
		return false;
	}

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		LOG(Fatal) << "Failed to initialize GLEW: " << glewGetErrorString(glewError) << std::endl;
		return false;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	return true;
}

void closeSDL(SDL_Window* window, SDL_GLContext context) {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[]) {
	Logger::createInstance();
	Logger::getInstance().enableWriteInTerminal();

	SDL_Window* window = nullptr;
	SDL_GLContext context;

	if (!initSDL(window, context)) {
		LOG(Fatal) << "Failed to initialize SDL and OpenGL" << std::endl;
		return -1;
	}

	std::shared_ptr<Shader> shader = std::make_shared<Shader>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader.glsl");
	auto camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
	Scene scene(camera, shader);

	std::array<std::string, 6> textureFiles = {
		"./res/concrete_front.png",
		"./res/concrete_back.png",
		"./res/concrete_left.png",
		"./res/concrete_right.png",
		"./res/concrete_top.png",
		"./res/concrete_bottom.png"
	};

	std::shared_ptr<Entity> block1 = std::make_shared<Block>(glm::vec3(0, 0, 0), textureFiles);
	std::shared_ptr<Entity> block2 = std::make_shared<Block>(glm::vec3(1, 1, 1), textureFiles);

	scene.addEntity(block1);
	scene.addEntity(block2);

	bool quit = false;
	SDL_Event event;

	float ratio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	int centerX = SCREEN_WIDTH / 2;
	int centerY = SCREEN_HEIGHT / 2;
	float deltaTime = 0.0;

	bool moveForward = false;
	bool moveBackward = false;
	bool moveLeft = false;
	bool moveRight = false;

	bool mouseCaptured = true;

	if (mouseCaptured) {
		SDL_SetRelativeMouseMode(SDL_TRUE);
		SDL_WarpMouseInWindow(window, centerX, centerY);
    }

	while (!quit) {
		auto startTime = std::chrono::high_resolution_clock::now();
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = true;
			} else if (event.type == SDL_MOUSEMOTION) {
				if (mouseCaptured) {
					float xpos = event.motion.x;
					float ypos = event.motion.y;

					float xoffset = xpos - centerX;
					float yoffset = centerY - ypos; // Reversed since y-coordinates go from bottom to top

					if (xoffset != 0.0f || yoffset != 0.0f) {
						//LOG(Debug) << "Mouse offset: (" << xoffset << ", " << yoffset << ")";

						camera->processMouseMovement(xoffset, yoffset);
						SDL_WarpMouseInWindow(window, centerX, centerY);
					}
				}
			} else if (event.type == SDL_MOUSEWHEEL) {
				camera->processMouseScroll(event.wheel.y);
			} else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						quit = true;
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
					case SDLK_e:
						mouseCaptured = !mouseCaptured;
						if (mouseCaptured) {
							SDL_SetRelativeMouseMode(mouseCaptured ? SDL_TRUE : SDL_FALSE);
							SDL_WarpMouseInWindow(window, centerX, centerY);
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
				}
			}
		}

		camera->processKeyboard(deltaTime, moveForward, moveBackward, moveLeft, moveRight);

		scene.update(deltaTime);

		glClear(GL_COLOR_BUFFER_BIT);

		scene.render(ratio);

		SDL_GL_SwapWindow(window);

		SDL_Delay(4);
		
		deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now() - startTime).count();
	}

	closeSDL(window, context);

	Logger::destroyInstance();
	return 0;
}
