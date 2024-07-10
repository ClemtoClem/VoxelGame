#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <iostream>

#include "Shader.hpp"
#include "Window.hpp"
#include "Scene.hpp"
#include "GUI/GUI.hpp"

#include <memory>
#include <string>

const std::string FONT_PATH = "res/fonts/";
const std::string IMAGE_PATH = "res/images/";

class Game {
public:
    Game();

    ~Game();

    void run(int argc, char *argv[]);

private:

    /**
     * @brief Initialisation du jeu
     * @param[in] argc Nombre de paramètres
     * @param[in] argv liste des paramètres
     */
    bool init(int argc, char *argv[]);

    bool load();
    void unload();

    bool initSDL();
    void closeSDL();

    bool initOpenGL();

    bool _isLoad;
    bool _running;

    Window _window;
    GUI    _gui;

    std::shared_ptr<Shader> _shader;
    std::shared_ptr<Camera> _camera;
    std::shared_ptr<Scene> _scene;
};

#endif // GAME_HPP