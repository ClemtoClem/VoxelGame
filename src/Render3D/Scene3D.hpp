/**
 *  __                     _____   ___
 * / _\ ___ ___ _ __   ___|___ /  /   \
 * \ \ / __/ _ \ '_ \ / _ \ |_ \ / /\ /
 * _\ \ (_|  __/ | | |  __/___) / /_//
 * \__/\___\___|_| |_|\___|____/___,'
 * 
 * @file Scene.hpp
 * @author @ClemtoClem (https://github.com/ClemtoClem)
 * @date 09/07/2024
 * @brief Scene class
 */

#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "../Core/Shader.hpp"
#include "Entities/Entity.hpp"
#include "Frustum.hpp"
#include "Camera.hpp"
#include "Lights/Light.hpp"
#include "Lights/DirectionalLight.hpp"
#include "Lights/PointLight.hpp"
#include "Lights/SpotLight.hpp"

namespace Render3D {

#define MAX_POINT_LIGHTS 10
#define MAX_SPOT_LIGHTS 10

const std::string PATH_SHADERS_3D = "./resources/shaders/";

class Scene3D {
public:
	Scene3D(std::shared_ptr<Camera> camera);

	bool initialize();

	void reset();

	/// @brief Acyiver/Désactiver la scène
	void setEnable(bool enable);

	/// @brief Savoir si la scène est activée
	/// @return True si la scène est activée, false sinon
	bool isEnable() const;

	void setFog(float start, float end, const glm::vec4 &color);

	void addEntity(std::shared_ptr<Entity> entity);
	void removeEntity(std::shared_ptr<Entity> entity);
	void clearEntities();

	void addLight(std::shared_ptr<Light> light);
	void removeLight(std::shared_ptr<Light> light);
	void clearLights();

	bool entitiesSetupSuccessfully() const;

	void handleEvent(const SDL_Event& event);
	void update(float dt);
	void render(float aspectRatio) const;

private:
	std::shared_ptr<Camera> _camera;
	std::shared_ptr<Shader> _shader3DTexture;
	std::shared_ptr<Shader> _shader3DLight;
	std::vector<std::shared_ptr<Entity>> _entities;
	std::vector<std::shared_ptr<Light>> _lights;

	float _fogStart = 5.0f;
	float _fogEnd = 30.0f;
	glm::vec4 _fogColor = glm::vec4(0.7, 0.8, 0.9, 1.0); // bleu-gris

	bool _enabled;
};

using Scene3DPtr = std::shared_ptr<Scene3D>;

}

#endif // SCENE_HPP