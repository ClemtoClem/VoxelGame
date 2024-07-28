#include "ResourcesManager.hpp"

std::shared_ptr<ResourcesManager> ResourcesManager::instance = nullptr;

ResourcesManager::ResourcesManager()
	: _imagesPath(IMAGES_PATH_DEFAULT),
	  _shadersPath(SHADERS_PATH_DEFAULT),
	  _fontsPath(FONTS_PATH_DEFAULT) {
	createDefaultTexture();
}

std::shared_ptr<ResourcesManager> ResourcesManager::getInstance() {
	if (!instance) {
		instance = std::make_shared<ResourcesManager>();
	}
	return instance;
}

void ResourcesManager::setPaths(const std::string &images_path, const std::string &shaders_path, const std::string &fonts_path) {
	_imagesPath = images_path;
	_shadersPath = shaders_path;
	_fontsPath = fonts_path;
}

bool ResourcesManager::loadTexture(const std::string &name, const std::string &path) {
	TexturePtr texture = std::make_shared<Texture>();
	if (!texture->loadFromFile(path)) {
		LOG(Error) << "Failed to load texture: " << name << " from path: " << path;
		return false;
	}
	_resources.push_back({ResourceType::TEXTURE, name, path, texture});
	return true;
}

bool ResourcesManager::loadShader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath) {
	std::shared_ptr<Shader> shader = std::make_shared<Shader>(vertexPath, fragmentPath);
	if (shader->hasError()) {
		LOG(Error) << shader->getError();
		LOG(Error) << "Failed to load shader: " << name << " from vertex path: " << vertexPath << " and fragment path: " << fragmentPath;
		return false;
	}
	_resources.push_back({ResourceType::SHADER, name, vertexPath + " " + fragmentPath, shader});
	return true;
}

bool ResourcesManager::loadFont(const std::string &name, const std::string &path) {
	FontPtr font = std::make_shared<Font>();
	if (!font->loadFromFile(path)) {
		LOG(Error) << font->getError();
		LOG(Error) << "Failed to load font: " << name << " from path: " << path;
		return false;
	}
	_resources.push_back({ResourceType::FONT, name, path, font});
	return true;
}

TexturePtr ResourcesManager::getTexture(const std::string &name) {
	for (auto &resource : _resources) {
		if (resource.type == ResourceType::TEXTURE && resource.name == name) {
			return std::static_pointer_cast<Texture>(resource.data);
		}
	}
	LOG(Error) << "Texture not found: " << name;
	return _defaultTexture;
}

std::shared_ptr<Shader> ResourcesManager::getShader(const std::string &name) {
	for (auto &resource : _resources) {
		if (resource.type == ResourceType::SHADER && resource.name == name) {
			return std::static_pointer_cast<Shader>(resource.data);
		}
	}
	LOG(Error) << "Shader not found: " << name;
	return nullptr;
}

FontPtr ResourcesManager::getFont(const std::string &name) {
	for (auto &resource : _resources) {
		if (resource.type == ResourceType::FONT && resource.name == name) {
			return std::static_pointer_cast<Font>(resource.data);
		}
	}
	LOG(Error) << "Font not found: " << name;
	return nullptr;
}

void ResourcesManager::createDefaultTexture() {
	_defaultTexture = std::make_shared<Texture>();
	std::vector<glm::vec4> pixels(16*16);
	for (int y = 0; y < 16; ++y) {
		for (int x = 0; x < 16; ++x) {
			glm::vec4 color = ((x + y) % 2 == 0) ? glm::vec4(Color::RED) : glm::vec4(Color::BLACK);
			pixels[y * 16 + x] = color;
		}
	}
	_defaultTexture->createFromPixels(glm::vec2(16, 16), pixels);
}
