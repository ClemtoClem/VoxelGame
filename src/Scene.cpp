#include "Scene.hpp"
#include <algorithm> // pour std::remove
#include <glm/gtc/matrix_transform.hpp>

Scene::Scene(std::shared_ptr<Camera> camera, std::shared_ptr<Shader> shader) : m_camera(camera), m_shader(shader) {}

void Scene::addEntity(std::shared_ptr<Entity> entity) {
	m_entities.push_back(entity);
}

void Scene::removeEntity(std::shared_ptr<Entity> entity) {
	m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());
}

void Scene::update(float dt) {
	for (auto &entity : m_entities) {
		entity->update(dt);
	}
}

void Scene::render(float aspectRatio) const {
	glm::mat4 viewMatrix = m_camera->getViewMatrix();
	glm::mat4 projectionMatrix = m_camera->getProjectionMatrix(aspectRatio);
	glm::mat4 viewProjMatrix = projectionMatrix * viewMatrix;

	m_shader->use();
	m_shader->setMat4("view", viewMatrix);
	m_shader->setMat4("projection", projectionMatrix);

	for (const auto &entity : m_entities) {
		if (isEntityInFrustum(entity, viewProjMatrix)) {
			glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), entity->position());
			m_shader->setMat4("model", modelMatrix);
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

