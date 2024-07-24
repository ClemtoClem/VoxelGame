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

#include "Widget.hpp"
#include "../Core/Font.hpp"
#include "../Core/Texture.hpp"
#include "../Core/Shader.hpp"
#include <vector>
#include <memory>
#include <glm/glm.hpp>

namespace Render2D {

const std::string PATH_SHADERS_2D = "./resources/shaders/";

class Scene2D {
public:
	Scene2D(const glm::vec2 &screenSize = glm::vec2(1280, 720));
	~Scene2D();

	/// @brief Initialiser la scène
	/// @return Return true si la scène a été initialisée avec succès, false sinon
	bool init();

	/// @brief Reinitialiser la scène
	void reset();




	/// @brief Changer la taille de la scène
	/// @param screenSize	Nouvelle taille de la scène
	void setScreenSize(const glm::vec2 &screenSize);

	/// @brief Récupérer la taille de la scène
	/// @return Taille de la scène
	glm::vec2 getScreenSize() const;

	/// @brief Réccipérer la matrice de projection de la scène
	/// @return Matrice de projection de la scène
	glm::mat4 getProjectionMatrix() const;

	/// @brief Désactiver la scène
	void disable();

	/// @brief Activer la scène
	void enable();

	/// @brief Savoir si la scène est activée
	/// @return True si la scène est activée, false sinon
	bool isEnabled() const;




	/// @brief Afficher un rectangle coloré sur la scène
	/// @param position		Position du rectangle
	/// @param size			Taille du rectangle
	/// @param color		Couleur du rectangle
	void drawRectangle(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color);
	
	/// @brief Afficher une image sur la scène
	/// @param texture  	Texture à afficher
	/// @param position		Position de l'image
	/// @param size			Taille de l'image
	void drawImage(const Texture &texture, const glm::vec2 &position, const glm::vec2 &size);
	
	/// @brief Afficher du texte sur la scène
	/// @param font			Police de caractère
	/// @param text			Texte à afficher
	/// @param position		Position du texte
	/// @param color		Couleur du texte
	void drawText(Font &font, const std::string &text, const glm::vec2 &position, const glm::vec4 &color);





	/// @brief Ajouter un enfant à la scène
	/// @param widget Widget enfant à ajouter
	void addChild(std::shared_ptr<Widget> widget);

	/// @brief Supprimer un enfant de la scène
	/// @param name Nom de l'enfant à supprimer
	void deleteChild(const std::string &name);

	/// @brief Obtenir un enfant de la scène
	/// @param name Nom de l'enfant à obtenir
	std::shared_ptr<Widget> getChild(const std::string &name) const;

	/// @brief Supprimer tous les enfants de la scène
	void deleteChilden();





	/// @brief Gérer les événements de la scène
	/// @param evt 
	void handleEvent(SDL_Event& evt);

	/// @brief Mettre à jour la scène
	/// @param dt Délai entre chaque frame
	void update(float dt);
	
	/// @brief Afficher la scène
	void render() const;

private:
	/// @brief Initialiser les données de rendu de la scène
	void initRenderData();
	
	glm::vec2 _screenSize;
	glm::mat4 _projection;
	
	std::shared_ptr<Shader> _shader2D;
	GLuint _vao, _vbo, _ebo;

	std::vector<std::shared_ptr<Widget>> _children;

	bool _enabled;

};

using Scene2DPtr = std::shared_ptr<Scene2D>;

}

#endif // SCENE_2D_HPP
