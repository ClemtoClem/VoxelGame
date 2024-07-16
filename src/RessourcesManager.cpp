#include "ResourcesManager.hpp"

ResourcesManager::ResourcesManager()
    : _imagesPath(IMAGES_PATH_DEFAULT),
      _shadersPath(SHADERS_PATH_DEFAULT),
      _fontsPath(FONTS_PATH_DEFAULT) {}

ResourcesManager &ResourcesManager::getInstance() {
    static ResourcesManager instance;
    return instance;
}

void ResourcesManager::setPaths(const std::string &images_path, const std::string &shaders_path, const std::string &fonts_path) {
    _imagesPath = images_path;
    _shadersPath = shaders_path;
    _fontsPath = fonts_path;
}

void ResourcesManager::loadTexture(const std::string &name, const std::string &path) {
    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    if (!texture->loadFromFile(path)) {
        texture = createDefaultTexture();
        logError("Failed to load texture: " + name + " from path: " + path);
    }
    _resources.push_back({ResourceType::TEXTURE, name, path, texture.get()});
}

void ResourcesManager::loadTilesTexture(const std::string &name, const std::string &path) {
    std::array<std::shared_ptr<Texture>, 6> textures = Texture::createTilesFromFile(path);
    if (textures[0]) {
        for (int i = 0; i < 6; ++i) {
            _resources.push_back({ResourceType::TILES_TEXTURE, name, path, textures[i].get()});
        }
    } else {
        logError("Failed to load tiles texture: " + name + " from path: " + path);
    }
}

void ResourcesManager::loadShader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath) {
    std::shared_ptr<Shader> shader = std::make_shared<Shader>(vertexPath, fragmentPath);
    if (!shader->isValid()) {
        logError("Failed to load shader: " + name + " from vertex path: " + vertexPath + " and fragment path: " + fragmentPath);
    }
    _resources.push_back({ResourceType::SHADER, name, vertexPath + " " + fragmentPath, shader.get()});
}

void ResourcesManager::loadFont(const std::string &name, const std::string &path) {
    std::shared_ptr<Font> font = std::make_shared<Font>(path);
    if (!font->isValid()) {
        logError("Failed to load font: " + name + " from path: " + path);
    }
    _resources.push_back({ResourceType::FONT, name, path, font.get()});
}

std::shared_ptr<Texture> ResourcesManager::getTexture(const std::string &name) {
    for (auto &resource : _resources) {
        if (resource.type == ResourceType::TEXTURE && resource.name == name) {
            return std::shared_ptr<Texture>(static_cast<Texture*>(resource.data));
        }
    }
    logError("Texture not found: " + name);
    return createDefaultTexture();
}

std::shared_ptr<Texture> ResourcesManager::getTileTexture(const std::string &name, Face face) {
    for (auto &resource : _resources) {
        if (resource.type == ResourceType::TILES_TEXTURE && resource.name == name) {
            return std::shared_ptr<Texture>(static_cast<Texture*>(resource.data + (face - 1)));
        }
    }
    logError("Tiles texture not found: " + name);
    return createDefaultTexture();
}

std::array<std::shared_ptr<Texture>, 6> ResourcesManager::getTilesTexture(const std::string &name) {
    std::array<std::shared_ptr<Texture>, 6> textures;
    for (auto &resource : _resources) {
        if (resource.type == ResourceType::TILES_TEXTURE && resource.name == name) {
            for (int i = 0; i < 6; ++i) {
                textures[i] = std::shared_ptr<Texture>(static_cast<Texture*>(resource.data + i));
            }
            return textures;
        }
    }
    logError("Tiles texture not found: " + name);
    return Texture::createTilesFromFile(""); // Retourner des textures par défaut
}

std::shared_ptr<Shader> ResourcesManager::getShader(const std::string &name) {
    for (auto &resource : _resources) {
        if (resource.type == ResourceType::SHADER && resource.name == name) {
            return std::shared_ptr<Shader>(static_cast<Shader*>(resource.data));
        }
    }
    logError("Shader not found: " + name);
    return nullptr;
}

std::shared_ptr<Font> ResourcesManager::getFont(const std::string &name) {
    for (auto &resource : _resources) {
        if (resource.type == ResourceType::FONT && resource.name == name) {
            return std::shared_ptr<Font>(static_cast<Font*>(resource.data));
        }
    }
    logError("Font not found: " + name);
    return nullptr;
}

std::shared_ptr<Texture> ResourcesManager::createDefaultTexture() {
    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    texture->createEmpty(16, 16);
    _resources.push_back({ResourceType::TEXTURE, "DefaultTexture", "Default", texture.get()});
    return texture;
}
