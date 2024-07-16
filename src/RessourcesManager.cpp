#include "ResourcesManager.hpp"
#include "Logger.hpp"
#include "Utils.hpp"
#include "RessourcesManager.hpp"

ResourcesManager::ResourcesManager()
    : images_path(IMAGES_PATH_DEFAULT), shaders_path(SHADERS_PATH_DEFAULT), fonts_path(FONTS_PATH_DEFAULT) {}

ResourcesManager &ResourcesManager::getInstance() {
    static ResourcesManager instance;
    return instance;
}

void ResourcesManager::setPath(const std::string &images_path, const std::string &shaders_path, const std::string &fonts_path) {
    this->images_path = images_path;
    this->shaders_path = shaders_path;
    this->fonts_path = fonts_path;
}

void ResourcesManager::loadTexture(const std::string &name, const std::string &path) {
    auto texture = std::make_shared<Texture>();
    if (texture->loadFromFile(images_path + path)) {
        _textures[name] = texture;
        LOG(Info) << "Loaded texture: " << name;
    } else {
        LOG(Error) << "Failed to load texture: " << path;
    }
}

void ResourcesManager::loadTilesTexture(const std::string &name, const std::string &path) {
    auto tilesTextures = Texture::loadTilesFromFile(images_path + path);
    if (tilesTextures) {
        _tilesTextures[name] = *tilesTextures;
        LOG(Info) << "Loaded tiles texture: " << name;
    } else {
        LOG(Error) << "Failed to load tiles texture: " << path;
    }
}

void ResourcesManager::loadShader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath) {
    auto shader = std::make_shared<Shader>(shaders_path + vertexPath, shaders_path + fragmentPath);
    if (shader->getError().empty()) {
        _shaders[name] = shader;
        LOG(Info) << "Loaded shader: " << name;
    } else {
        LOG(Error) << "Failed to load shader: " << shader->getError();
    }
}

void ResourcesManager::loadFont(const std::string &name, const std::string &path, int fontSize) {
    auto font = std::make_shared<Font>();
    if (font->loadFromFile(fonts_path + path, fontSize)) {
        _fonts[name] = font;
        LOG(Info) << "Loaded font: " << name;
    } else {
        LOG(Error) << "Failed to load font: " << path;
    }
}

void ResourcesManager::loadAllTexturesInDirectory() {
    namespace fs = std::filesystem;
    try {
        for (const auto &entry : fs::directory_iterator(images_path)) {
            if (entry.is_regular_file()) {
                std::string filePath = entry.path().string();
                std::string fileName = entry.path().stem().string(); // Get the file name without extension
                loadTexture(fileName, filePath);
            }
        }
    } catch (const fs::filesystem_error &e) {
        LOG(Error) << "Filesystem error: " << e.what();
    } catch (const std::exception &e) {
        LOG(Error) << "Exception: " << e.what();
    }
}

std::shared_ptr<Texture> ResourcesManager::getTexture(const std::string &name)
{
    if (_textures.find(name) != _textures.end()) {
        return _textures[name];
    }
    LOG(Error) << "Texture not found: " << name;
    return nullptr;
}

std::shared_ptr<Texture> ResourcesManager::getTileTexture(const std::string &name, Face face) {
    auto it = _tilesTextures.find(name);
    if (it != _tilesTextures.end()) {
        switch (face) {
            case FRONT: return it->second[0];
            case BACK: return it->second[1];
            case LEFT: return it->second[2];
            case RIGHT: return it->second[3];
            case UP: return it->second[4];
            case DOWN: return it->second[5];
        }
    }
    LOG(Error) << "Tile texture not found: " << name << " for face " << face;
    return nullptr;
}

std::array<std::shared_ptr<Texture>, 6> ResourcesManager::getTilesTexture(const std::string &name) {
    if (_tilesTextures.find(name) != _tilesTextures.end()) {
        return _tilesTextures[name];
    }
    LOG(Error) << "Tiles texture not found: " << name;
    return {};
}

std::shared_ptr<Shader> ResourcesManager::getShader(const std::string &name) {
    if (_shaders.find(name) != _shaders.end()) {
        return _shaders[name];
    }
    LOG(Error) << "Shader not found: " << name;
    return nullptr;
}

std::shared_ptr<Font> ResourcesManager::getFont(const std::string &name) {
    if (_fonts.find(name) != _fonts.end()) {
        return _fonts[name];
    }
    LOG(Error) << "Font not found: " << name;
    return nullptr;
}
