#include "Scene3D.hpp"
#include <algorithm> // pour std::remove
#include <glm/gtc/matrix_transform.hpp>
#include "../Core/Logger.hpp"

namespace Render3D {

Scene3D::Scene3D(std::shared_ptr<Camera> camera) : _camera(camera), _enabled(true) {
}

bool Scene3D::initialize() {
	_shader3DTexture = std::make_shared<Shader>(PATH_SHADERS_3D + "shader_3d_texture.vert", PATH_SHADERS_3D + "shader_3d_texture.frag");
	const std::string &err1 = _shader3DTexture->getError();
	if (!err1.empty()) {
		LOG(Error) << err1;
		return false;
	}
	
	_shader3DLight = std::make_shared<Shader>(PATH_SHADERS_3D + "shader_3d_light.vert", PATH_SHADERS_3D + "shader_3d_light.frag");
	const std::string &err2 = _shader3DLight->getError();
	if (!err2.empty()) {
		LOG(Error) << err2;
		return false;
	}
	return true;
}

void Scene3D::reset() {
	clearEntities();
	clearLights();
}

void Scene3D::setEnable(bool enable) {
	_enabled = enable;
}

bool Scene3D::isEnable() const {
	return _enabled;
}

void Scene3D::setFog(float start, float end, const glm::vec4 &color) {
	_fogStart = start;
	_fogEnd = end;
	_fogColor = color;
}

void Scene3D::addEntity(std::shared_ptr<Entity> entity) {
	// on véririfie que l'entité n'est pas déjà dans la scène
	if (std::find(_entities.begin(), _entities.end(), entity)!= _entities.end()) {
		LOG(Error) << "Entity already in scene";
		return;
	}
	_entities.push_back(entity);
}

void Scene3D::removeEntity(std::shared_ptr<Entity> entity) {
	_entities.erase(std::remove(_entities.begin(), _entities.end(), entity), _entities.end());
}

void Scene3D::clearEntities() {
	_entities.clear();
}

void Scene3D::addLight(std::shared_ptr<Light> light) {
	// on véririfie que l'entité n'est pas déjà dans la scène
	if (std::find(_lights.begin(), _lights.end(), light)!= _lights.end()) {
		LOG(Error) << "Light already in scene";
		return;
	}
	_lights.push_back(light);
}

void Scene3D::removeLight(std::shared_ptr<Light> light) {
	_lights.erase(std::remove(_lights.begin(), _lights.end(), light), _lights.end());
}

void Scene3D::clearLights() {
	_lights.clear();
}

bool Scene3D::entitiesSetupSuccessfully() const {
	for (auto &entity : _entities) {
		if (!entity->setupSuccessfully()) {
			return false;
		}
	}
    return true;
}

void Scene3D::handleEvent(const SDL_Event &event) {

}

void Scene3D::update(float dt) {
	if (_enabled) {
		//LOG(Debug) << "Update entities...";
		for (auto &entity : _entities) {
			entity->update(dt);
		}
		//LOG(Debug) << "Entities are updated";
	}
}

void Scene3D::render(float aspectRatio) const {
	/*
		Coordinates space convertion for rendering
		┌───────┐       ┌───────┐       ┌───────┐            ┌───────┐          ┌────────┐
		│ Local │──────\| World |──────\| View  |───────────\| Clip  |─────────\| Screen │
		│ Space │──────/| Space │──────/| Space │───────────/| Space |─────────/| Space  |
		└───────┘ Model └───────┘ View  └───────┘ Projection └───────┘ Viewport └────────┘
				  matrix          matrix          matrix               transformation
				  (object)        (camera)        (camera)             (screen)
	*/


    if (_enabled) {
        // Matrices de vue et de projection
        glm::mat4 viewMatrix       = _camera->getViewMatrix();
        glm::mat4 projectionMatrix = _camera->getProjectionMatrix(aspectRatio);
		glm::mat4 viewProjMatrix = projectionMatrix * viewMatrix;

        // Génération du frustum
        Frustum frustum;
		frustum.CalculatePlanes(viewProjMatrix);

		// Rendu des entités visibles
        for (const auto& entity : _entities) {
            auto corners = entity->getBoundingBoxCorners();
			// adapter les coordonnées pour des coins du cube dans l'espace de la scène
			for (auto &corner : corners) {
				corner = entity->modelMatrix() * glm::vec4(corner, 1.0f);
			}

			_shader3DTexture->use();
			_shader3DTexture->setMat4("view", viewMatrix);
			_shader3DTexture->setMat4("projection", projectionMatrix);
			_shader3DTexture->setMat4("model", entity->modelMatrix());

			_shader3DTexture->setFloat("fogStart", _fogStart);
			_shader3DTexture->setFloat("fogEnd", _fogEnd);
			_shader3DTexture->setVec4("fogColor", _fogColor);
            
			//if (frustum.LeastOnePointIsInside(corners)) {
                entity->render(*_shader3DTexture);
            //}
        }

        // Utilisation du shader de lumière 3D
        /*_shader3DLight->use();
        _shader3DLight->setMat4("view", viewMatrix);
        _shader3DLight->setMat4("projection", projectionMatrix);
		modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f)); // a smaller cube
		_shader3DLight->setMat4("model", modelMatrix);*/

        //_shader3DLight->setVec3("viewPos", _camera->getPosition());
		//_shader3DLight->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
/*
        //_shader3DLight->setFloat("strength", 0.2f);
        _shader3DLight->setInt("material.shiness", 64);
        _shader3DLight->setInt("material.diffuse", 0);
		_shader3DLight->setInt("material.specular", 1);
		_shader3DLight->setInt("material.normal", 2);


		// Définir le nombre de lumières ponctuelles et spot dans le shader
		// Configuration des uniformes pour chaque type de lumière

		int pointLightIndex = 0;
		int spotLightIndex = 0;

		for (const auto &light : _lights) {
			switch(light->getType()) {
				case Light::Type::POINT:
					light->setLightUniforms(*_shader3DLight, pointLightIndex);
					pointLightIndex++;
					break;
				case Light::Type::SPOT:
					light->setLightUniforms(*_shader3DLight, spotLightIndex);
					spotLightIndex++;
					break;
				default:
					light->setLightUniforms(*_shader3DLight, 0);
					break;
			}
		}

		_shader3DLight->setInt("numPointLights", pointLightIndex);
		_shader3DLight->setInt("numSpotLights", spotLightIndex);
*/

		//LOG(Debug) << "Entities are rendered";
    }
}

}