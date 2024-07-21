/**
 *  __                     
 * / _\ ___ ___ _ __   ___ 
 * \ \ / __/ _ \ '_ \ / _ \
 * _\ \ (_|  __/ | | |  __/
 * \__/\___\___|_| |_|\___|
 * 
 * @file Scene.hpp
 * @author @ClemtoClem
 * @date 09/07/2024
 * @brief Scene class
 */

#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "Camera.hpp"
#include "Shader.hpp"
#include "Entity.hpp"
#include "Light.hpp"

#define MAX_POINT_LIGHTS 10
#define MAX_SPOT_LIGHTS 10

const std::string PATH_SHADERS_3D = "./resources/shaders/";

class Scene {
public:
	Scene(std::shared_ptr<Camera> camera);

	bool init();

	void reset();

	void addEntity(std::shared_ptr<Entity> entity);
	void removeEntity(std::shared_ptr<Entity> entity);
	void clearEntities();

	void addLight(std::shared_ptr<Light> light);
	void removeLight(std::shared_ptr<Light> light);
	void clearLights();

	void update(float dt);
	void render(float aspectRatio) const;

private:
	bool isEntityInFrustum(std::shared_ptr<Entity> entity, const glm::mat4& viewProjMatrix) const;
	bool isPointInFrustum(const glm::vec4& point) const;

	std::shared_ptr<Camera> _camera;
	std::shared_ptr<Shader> _shader3DLight;
	std::vector<std::shared_ptr<Entity>> _entities;
	std::vector<std::shared_ptr<Light>> _lights;
};

#endif // SCENE_HPP