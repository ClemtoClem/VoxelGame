/**
 *  __    __ _           _                 __    ___  __ ____     _____                    ___   __  
 * / / /\ \ (_)_ __   __| | _____      __ / _\  /   \/ /|___ \   / /___\_ __   ___ _ __   / _ \ / /  
 * \ \/  \/ / | '_ \ / _` |/ _ \ \ /\ / / \ \  / /\ / /   __) | / //  // '_ \ / _ \ '_ \ / /_\// /   
 *  \  /\  /| | | | | (_| | (_) \ V  V /  _\ \/ /_// /___/ __/ / / \_//| |_) |  __/ | | / /_\\/ /___ 
 *   \/  \/ |_|_| |_|\__,_|\___/ \_/\_/   \__/___,'\____/_____/_/\___/ | .__/ \___|_| |_\____/\____/ 
 *                                                                     |_|                           
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

class Window {
public:
	// Initializes internals
	Window(const std::string &title = "OpenGL with SDL2", int width = 800, int height = 600);

	~Window();

	SDL_Window *get() { return _window; }

	// Creates window
	bool init();

	// Deallocates internals
	void free();

	// Creates GL context
	SDL_GLContext createGLContext();
	void GLSwap();

	// Handles window events
	void handleEvent(SDL_Event& evt);

	// Window dimensions
	int getWidth() const;
	int getHeight() const;
	int getCenterX() const;
	int getCenterY() const;
	float getRatio() const;

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
	int _centerX, _centerY;
	float _ratio;

	// Window focus
	bool _mouseFocus;
	bool _keyboardFocus;
	bool _fullScreen;
	bool _minimized;
};

#endif // WINDOW_HPP
