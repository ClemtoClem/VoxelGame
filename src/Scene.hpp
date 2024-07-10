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
 */

#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "Camera.hpp"
#include "Shader.hpp"
#include "Entity.hpp"

class Scene {
public:
	Scene(std::shared_ptr<Camera> camera, std::shared_ptr<Shader> shader);

	void reset();

	void addEntity(std::shared_ptr<Entity> entity);
	void removeEntity(std::shared_ptr<Entity> entity);

	void update(float dt);
	void render(float aspectRatio) const;

private:
	bool isEntityInFrustum(std::shared_ptr<Entity> entity, const glm::mat4& viewProjMatrix) const;
	bool isPointInFrustum(const glm::vec4& point) const;

	std::shared_ptr<Camera> _camera;
	std::shared_ptr<Shader> _shader;
	std::vector<std::shared_ptr<Entity>> _entities;
};

#endif // SCENE_HPP