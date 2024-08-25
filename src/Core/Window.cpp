#include "Window.hpp"

Window::Window() 
	: _window(nullptr), _context(nullptr), _title(""), _width(0), _height(0), 
	  _mouseFocus(false), _keyboardFocus(false), _fullscreen(false), _minimized(false),
	  _isInitialized(false) {
}

Window::~Window() {
	release();
}

bool Window::initialize(const WindowCreateInfo &info) {
	if (!_isInitialized) {
		_title  = info.title;
		_width  = info.width;
		_height = info.height;
		_posX   = info.posX;
		_posY   = info.posY;
		_fullscreen = info.fullscreen;

		_centerX = _width / 2;
		_centerY = _height / 2;
		_ratio = static_cast<float>(_width) / static_cast<float>(_height);

		_window = SDL_CreateWindow(_title.c_str(), _posX, _posY, _width, _height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (_window == nullptr) {
			LOG(Fatal) << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			return false;
		}

		_context = SDL_GL_CreateContext(_window);
		if (_context == nullptr) {
			LOG(Fatal) << "OpenGL context could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			return false;
		}

		_mouseFocus = true;
		_keyboardFocus = true;

		_isInitialized = true;
	}
	return true;
}

void Window::release() {
	if (_isInitialized) {
		if (_window != nullptr) {
			SDL_DestroyWindow(_window);
			_window = nullptr;
		}
		if (_context != nullptr) {
			SDL_GL_DeleteContext(_context);
			_context = nullptr;
		}

		_isInitialized = false;
	}
}

SDL_Window *Window::getSDLWindow() {
	return _window;
}

SDL_GLContext Window::getGLContext() {
    return _context;
}

void Window::swapBuffer() {
	SDL_GL_SwapWindow(_window);
}

void Window::handleEvent(SDL_Event& evt) {
	if (evt.type == SDL_WINDOWEVENT) {
		switch (evt.window.event) {
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			_width = evt.window.data1;
			_height = evt.window.data2;
			_centerX = _width / 2;
			_centerY = _height / 2;
			_ratio = static_cast<float>(_width) / static_cast<float>(_height);
			glViewport(0, 0, _width, _height);
			break;
		/*case SDL_WINDOWEVENT_EXPOSED:
			SDL_GL_SwapWindow(_window);
			break;*/
		case SDL_WINDOWEVENT_ENTER:
			_mouseFocus = true;
			break;
		case SDL_WINDOWEVENT_LEAVE:
			_mouseFocus = false;
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			_keyboardFocus = true;
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			_keyboardFocus = false;
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			_minimized = true;
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			_minimized = false;
			break;
		case SDL_WINDOWEVENT_RESTORED:
			_minimized = false;
			break;
		}
	}
}

int Window::getWidth() const {
	return _width;
}

int Window::getHeight() const {
	return _height;
}

glm::ivec2 Window::getSize() const {
    return glm::ivec2(_width, _height);
}

int Window::getPosX() const {
    return _posX;
}

int Window::getPosY() const {
    return _posY;
}

glm::ivec2 Window::getPos() const {
    return glm::ivec2(_posX, _posY);
}

int Window::getCenterX() const {
	return _centerX;
}

int Window::getCenterY() const {
	return _centerY;
}

float Window::getRatio() const {
	return _ratio;
}

void Window::setTitle(const std::string &title) {
	SDL_SetWindowTitle(_window, title.c_str());
}

void Window::toggleFullscreen() {
	_fullscreen = !_fullscreen;
	SDL_SetWindowFullscreen(_window, _fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
}

bool Window::isFullScreen() const {
	return _fullscreen;
}

bool Window::hasMouseFocus() const {
	return _mouseFocus;
}

bool Window::hasKeyboardFocus() const {
	return _keyboardFocus;
}

bool Window::isMinimized() const {
	return _minimized;
}

void Window::warpMouseCenter() {
	SDL_WarpMouseInWindow(_window, _centerX, _centerY);
}
