#include "ResourcesManager.hpp"

ResourcesManager::ResourcesManager()
    : _imagesPath(IMAGES_PATH_DEFAULT),
      _shadersPath(SHADERS_PATH_DEFAULT),
      _fontsPath(FONTS_PATH_DEFAULT) {
    createDefaultTexture();
}

ResourcesManager &ResourcesManager::getInstance() {
    static ResourcesManager instance;
    return instance;
}

void ResourcesManager::setPaths(const std::string &images_path, const std::string &shaders_path, const std::string &fonts_path) {
    _imagesPath = images_path;
    _shadersPath = shaders_path;
    _fontsPath = fonts_path;
}

bool ResourcesManager::loadTexture(const std::string &name, const std::string &path) {
    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
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
    std::shared_ptr<Font> font = std::make_shared<Font>();
    if (!font->loadFromFile(path, 24)) {
        LOG(Error) << font->getError();
        LOG(Error) << "Failed to load font: " << name << " from path: " << path;
        return false;
    }
    _resources.push_back({ResourceType::FONT, name, path, font});
    return true;
}

std::shared_ptr<Texture> ResourcesManager::getTexture(const std::string &name) {
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

std::shared_ptr<Font> ResourcesManager::getFont(const std::string &name) {
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
    _defaultTexture->create(16, 16);
    for (int y = 0; y < 16; ++y) {
        for (int x = 0; x < 16; ++x) {
            glm::vec4 color = ((x + y) % 2 == 0) ? glm::vec4(1.0, 0.0, 0.0, 1.0) : glm::vec4(0.0, 0.0, 0.0, 1.0);
            _defaultTexture->setPixel(x, y, color);
        }
    }
    _defaultTexture->updateTexture();
}
