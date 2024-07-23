/**
 *  __                     ____     ___ 
 * / _\ ___ ___ _ __   ___|___ \   /   \
 * \ \ / __/ _ \ '_ \ / _ \ __) | / /\ /
 * _\ \ (_|  __/ | | |  __// __/ / /_// 
 * \__/\___\___|_| |_|\___|_____/___,'  
 *
 * @file Scene2D.hpp
 * @author @ClemtoClem
 * @date 23/07/2024
 * @brief Scene2D class
 */

#ifndef SCENE_2D_HPP
#define SCENE_2D_HPP

#include "Widget.hpp"
#include "../Core/Shader.hpp"
#include <vector>
#include <memory>
#include <glm/glm.hpp>

namespace GUI {

const std::string PATH_SHADERS_2D = "./resources/shaders/";

class Scene2D {
public:
	Scene2D(int screenWidth, int screenHeight);
	~Scene2D();

	/// @brief Initialiser la scène
	/// @return Return true si la scène a été initialisée avec succès, false sinon
	bool init();

    /// @brief Afficher un rectangle coloré sur la scène
    /// @param position		Position du rectangle
    /// @param size			Taille du rectangle
    /// @param color		Couleur du rectangle
    void drawRectangle(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color);
    
	/// @brief Afficher une image sur la scène
	/// @param textureID	Identifiant de la texture
	/// @param position		Position de l'image
	/// @param size			Taille de l'image
	void drawImage(GLuint textureID, const glm::vec2 &position, const glm::vec2 &size);
    
	/// @brief Afficher du texte sur la scène
	/// @param font			Police de caractère
	/// @param text			Texte à afficher
	/// @param position		Position du texte
	/// @param color		Couleur du texte
	void drawText(Font &font, const std::string &text, const glm::vec2 &position, const glm::vec4 &color);

	void setScreenSize(int width, int height);

	void addChild(std::shared_ptr<Widget> widget);

	void deleteChild(const std::string &name);

	std::shared_ptr<Widget> getChild(const std::string &name) const;

	void deleteChilden();

	void handleEvent(SDL_Event& evt);

	void update(float dt);
	
	void render() const;

private:
	void initRenderData();
	
	int _screenWidth;
	int _screenHeight;
	glm::mat4 _projection;
	
	std::shared_ptr<Shader> _shader2D;
	GLuint _vao, _vbo, _ebo;

	std::vector<std::shared_ptr<Widget>> _children;

};

}

#endif // SCENE_2D_HPP
