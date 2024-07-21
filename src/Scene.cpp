#include "Scene.hpp"
#include <algorithm> // pour std::remove
#include <glm/gtc/matrix_transform.hpp>
#include "Logger.hpp"

Scene::Scene(std::shared_ptr<Camera> camera) : _camera(camera) {}

bool Scene::init() {
	_shader3DLight = std::make_shared<Shader>(PATH_SHADERS_3D + "vertex_shader_3d.glsl", PATH_SHADERS_3D + "fragment_shader_3d.glsl");
	const std::string &err2 = _shader3DLight->getError();
	if (!err2.empty()) {
		LOG(Error) << err2;
		return false;
	}
	return true;
}

void Scene::reset() {
	clearEntities();
	clearLights();
}

void Scene::addEntity(std::shared_ptr<Entity> entity) {
	// on véririfie que l'entité n'est pas déjà dans la scène
	if (std::find(_entities.begin(), _entities.end(), entity)!= _entities.end()) {
		LOG(Error) << "Entity already in scene";
		return;
	}
	_entities.push_back(entity);
}

void Scene::removeEntity(std::shared_ptr<Entity> entity) {
	_entities.erase(std::remove(_entities.begin(), _entities.end(), entity), _entities.end());
}

void Scene::clearEntities() {
	_entities.clear();
}

void Scene::addLight(std::shared_ptr<Light> light) {
	// on véririfie que l'entité n'est pas déjà dans la scène
	if (std::find(_lights.begin(), _lights.end(), light)!= _lights.end()) {
		LOG(Error) << "Light already in scene";
		return;
	}
	_lights.push_back(light);
}

void Scene::removeLight(std::shared_ptr<Light> light) {
	_lights.erase(std::remove(_lights.begin(), _lights.end(), light), _lights.end());
}

void Scene::clearLights() {
	_lights.clear();
}

void Scene::update(float dt) {
    for (auto &entity : _entities) {
		entity->update(dt);
	}
}

void Scene::render(float aspectRatio) const {
    // Matrices de vue et de projection
    glm::mat4 viewMatrix = _camera->getViewMatrix();
    glm::mat4 projectionMatrix = _camera->getProjectionMatrix(aspectRatio);
    glm::mat4 viewProjMatrix = projectionMatrix * viewMatrix;

    // Utilisation du shader de lumière 3D
    _shader3DLight->use();
    _shader3DLight->setMat4("view", viewMatrix);
    _shader3DLight->setMat4("projection", projectionMatrix);
    _shader3DLight->setVec3("viewPos", _camera->getPosition());

    /*int pointLightIndex = 0;
    int spotLightIndex = 0;

    // Configuration des uniformes pour chaque type de lumière
    for (const auto &light : _lights) {
		light->setPosition(_camera->getPosition());
		light->setDirection(_camera->getFront());

        if (light->getType() == Light::POINT) {
            light->setUniforms(*_shader3DLight, pointLightIndex++);
        } else if (light->getType() == Light::SPOT) {
            light->setUniforms(*_shader3DLight, spotLightIndex++);
        } else { // Lumière directionnelle
            light->setUniforms(*_shader3DLight); // Une seule lumière directionnelle, donc index 0
        }
    }

    // Définir le nombre de lumières ponctuelles et spot dans le shader
    _shader3DLight->setInt("numPointLights", pointLightIndex);
    _shader3DLight->setInt("numSpotLights", spotLightIndex);*/

    // Rendu des entités visibles
    for (const auto &entity : _entities) {
        if (isEntityInFrustum(entity, viewProjMatrix)) {
            entity->render(*_shader3DLight);
        }
    }
}

bool Scene::isEntityInFrustum(std::shared_ptr<Entity> entity, const glm::mat4& viewProjMatrix) const {
	// Simplified frustum culling: checks if the entity's position is inside the frustum.
	// This can be improved by checking bounding boxes or spheres.
	auto corners = entity->getBoundingBoxCorners();
	for (const auto& corner : corners) {
		glm::vec4 transformedCorner = viewProjMatrix * glm::vec4(corner, 1.0f);
		if (isPointInFrustum(transformedCorner)) {
			return true;
		}
	}
	return false;
}

bool Scene::isPointInFrustum(const glm::vec4 &point) const {
	return point.x > -point.w*1.5 && point.x < point.w*1.5 &&
		   point.y > -point.w*1.5 && point.y < point.w*1.5 &&
		   point.z > -point.w*1.5 && point.z < point.w*1.5;
}
