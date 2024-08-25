/**
 *  __    __ _           _                __     ___  __ ____     _____                    ___   __  
 * / / /\ \ (_)_ __   __| | _____	  __ / _\   /   \/ /|___ \   / /___\_ __   ___ _ __   / _ \ / /  
 * \ \/  \/ / | '_ \ / _` |/ _ \ \ /\ / / \ \  / /\ / /   __) | / //  // '_ \ / _ \ '_ \ / /_\// /   
 *  \  /\  /| | | | | (_| | (_) \ V  V /  _\ \/ /_// /___/ __/ / / \_//| |_) |  __/ | | / /_\\/ /___ 
 *   \/  \/ |_|_| |_|\__,_|\___/ \_/\_/   \__/___,'\____/_____/_/\___/ | .__/ \___|_| |_\____/\____/ 
 *																	 |_|						   
 * @file Window.hpp
 * @author @ClemtoClem (https://github.com/ClemtoClem)
 * @date 09/07/2024
 * @brief Window class
 */

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Logger.hpp"

struct WindowCreateInfo {
	std::string title = "OpenGL with SDL2";
	int width = 800;
	int height = 600;
	int posX = SDL_WINDOWPOS_CENTERED;
	int posY = SDL_WINDOWPOS_CENTERED;
	bool fullscreen = false;
};

/**
 * @brief Main Window Class
 */
class Window {
public:
	Window();

	~Window();

	// Initializes and creates window
	bool initialize(const WindowCreateInfo &info);

	// Deallocates internals
	void release();

	SDL_Window *getSDLWindow();
	SDL_GLContext getGLContext();

	/**
	 * @brief Swap OpenGL framebuffers/Update Display
	 */
	void swapBuffer();

	// Handles window events
	void handleEvent(SDL_Event& evt);

	// Window dimensions
	int getWidth() const;
	int getHeight() const;
	glm::ivec2 getSize() const;
	float getRatio() const;

	// Window position
	int getPosX() const;
	int getPosY() const;
	glm::ivec2 getPos() const;
	int getCenterX() const;
	int getCenterY() const;

	void setTitle(const std::string &title);

	void toggleFullscreen();
	bool isFullScreen() const;

	// Window focus
	bool hasMouseFocus() const;
	bool hasKeyboardFocus() const;
	bool isMinimized() const;

	// Mouse
	void warpMouseCenter();

private:

	// Window data
	SDL_Window* _window;
	SDL_GLContext _context;

	std::string _title;

	// Window dimensions
	int _width;
	int _height;
	int _posX, _posY;
	int _centerX, _centerY;
	float _ratio;

	// Window focus
	bool _mouseFocus;
	bool _keyboardFocus;
	bool _fullscreen;
	bool _minimized;

	bool _isInitialized;
};

#endif // WINDOW_HPP
