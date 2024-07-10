#include "Scene.hpp"
#include <algorithm> // pour std::remove
#include <glm/gtc/matrix_transform.hpp>

Scene::Scene(std::shared_ptr<Camera> camera, std::shared_ptr<Shader> shader) : _camera(camera), _shader(shader) {}

void Scene::reset() {

}

void Scene::addEntity(std::shared_ptr<Entity> entity) {
	_entities.push_back(entity);
}

void Scene::removeEntity(std::shared_ptr<Entity> entity) {
	_entities.erase(std::remove(_entities.begin(), _entities.end(), entity), _entities.end());
}

void Scene::update(float dt) {
	for (auto &entity : _entities) {
		entity->update(dt);
	}
}

void Scene::render(float aspectRatio) const {
	glm::mat4 viewMatrix = _camera->getViewMatrix();
	glm::mat4 projectionMatrix = _camera->getProjectionMatrix(aspectRatio);
	glm::mat4 viewProjMatrix = projectionMatrix * viewMatrix;

	_shader->use();
	_shader->setMat4("view", viewMatrix);
	_shader->setMat4("projection", projectionMatrix);

	for (const auto &entity : _entities) {
		if (isEntityInFrustum(entity, viewProjMatrix)) {
			glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), entity->position());
			_shader->setMat4("model", modelMatrix);
			entity->render();
		}
	}
}

bool Scene::isEntityInFrustum(std::shared_ptr<Entity> entity, const glm::mat4& viewProjMatrix) const {
	// Simplified frustum culling: checks if the entity's position is inside the frustum.
	// This can be improved by checking bounding boxes or spheres.
	glm::vec4 entityPos = viewProjMatrix * glm::vec4(entity->position().x, entity->position().y, entity->position().z, 1.0f);
	return entityPos.x > -entityPos.w && entityPos.x < entityPos.w &&
		   entityPos.y > -entityPos.w && entityPos.y < entityPos.w &&
		   entityPos.z > -entityPos.w && entityPos.z < entityPos.w;
}

