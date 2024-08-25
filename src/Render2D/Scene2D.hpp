/**
 *  __                     ____     ___ 
 * / _\ ___ ___ _ __   ___|___ \   /   \
 * \ \ / __/ _ \ '_ \ / _ \ __) | / /\ /
 * _\ \ (_|  __/ | | |  __// __/ / /_// 
 * \__/\___\___|_| |_|\___|_____/___,'  
 *
 * @file Scene2D.hpp
 * @author @ClemtoClem (https://github.com/ClemtoClem)
 * @date 23/07/2024
 * @brief Scene2D class
 */

#ifndef SCENE_2D_HPP
#define SCENE_2D_HPP

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "Widget.hpp"
#include "../Core/Font.hpp"
#include "../Core/Texture.hpp"
#include "../Core/Shader.hpp"

namespace Render2D {

const std::string PATH_SHADERS_2D = "./resources/shaders/";

class Scene2D : public Widget {
public:
	Scene2D(const glm::vec2 &screenSize = glm::vec2(1280, 720));
	~Scene2D();

	/// @brief Initialiser la scène
	/// @return Return true si la scène a été initialisée avec succès, false sinon
	bool initialize() override;

	/// @brief Changer la taille de la scène
	/// @param scale Nouvelle taille de la scène
	void setScale(const glm::vec2 &scale) override;

	/// @brief Réccipérer la matrice de projection de la scène
	/// @return Matrice de projection de la scène
	glm::mat4 getProjectionMatrix() const;

	/// @brief Gérer les événements de la scène
	/// @param evt 
	void handleEvent(SDL_Event& evt);

	/// @brief Mettre à jour la scène
	/// @param dt Délai entre chaque frame
	void update(float dt);
	
	/// @brief Afficher la scène
	void render() const;

	/// @brief Fonction de rendu de la scène désactivée
	void render(const Shader &shader2D) const override;

private:	
	glm::vec2 _screenSize;
	glm::mat4 _projection;
	
	std::shared_ptr<Shader> _shader2D;
	GLuint _vao, _vbo, _ebo;

	bool _enabled;

};

using Scene2DPtr = std::shared_ptr<Scene2D>;

}

#endif // SCENE_2D_HPP
