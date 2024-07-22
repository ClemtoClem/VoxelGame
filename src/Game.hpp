/**
 *    ___                     
 *   / _ \__ _ _ __ ___   ___ 
 *  / /_\/ _` | '_ ` _ \ / _ \
 * / /_\\ (_| | | | | | |  __/
 * \____/\__,_|_| |_| |_|\___|
 *
 * @file Game.hpp
 * @author @ClemtoClem
 * @date 13/07/2024
 * @brief Game class
 */

#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <iostream>

#include "Core/ResourcesManager.hpp"
#include "Core/Window.hpp"
#include "Core/Scene.hpp"
#include "Core/Utils.hpp"
#include "GUI/GUI.hpp"

#include <memory>
#include <string>

const std::string FONT_PATH  = "./resources/fonts/";
const std::string IMAGE_PATH = "./resources/images/";

class Game {
public:
	Game();

	~Game();

	/**
	 * @brief Executer le jeu
	 * @param[in] argc Nombre de paramètres
	 * @param[in] argv Liste des paramètres
	 */
	void run(int argc, char *argv[]);

private:

	/**
	 * @brief Initialisation du jeu
	 * @param[in] argc Nombre de paramètres
	 * @param[in] argv Liste des paramètres
	 */
	bool init(int argc, char *argv[]);

	bool initSDL();
	bool initOpenGL();
	void closeSDL();

	bool load();
	void unload();

	void setPerformanceFrequency(float frequency);

	float _performanceFrequency, _performancePeriod;
	bool _isLoad;
	bool _running;

	Window   _window;
	GUI::GUI _gui;
	ResourcesManager _resourcesManager;

	std::shared_ptr<Camera> _camera;
	std::shared_ptr<Scene>  _scene;
};

#endif // GAME_HPP