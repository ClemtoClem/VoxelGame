#ifndef RESOURCESMANAGER_HPP
#define RESOURCESMANAGER_HPP

#include <string>
#include <vector>
#include <array>
#include <memory>
#include <unordered_map>
#include <filesystem>
#include "Texture.hpp"
#include "Font.hpp"
#include "Shader.hpp"
#include "Logger.hpp"

const std::string IMAGES_PATH_DEFAULT = "./ressources/images/";
const std::string SHADERS_PATH_DEFAULT = "./ressources/shaders/";
const std::string FONTS_PATH_DEFAULT = "./ressources/fonts/";

class ResourcesManager {
public:
    ResourcesManager();

    static ResourcesManager &getInstance();

    void setPath(const std::string &images_path, const std::string &shaders_path, const std::string &fonts_path);

    void loadTexture(const std::string &name, const std::string &path);
    void loadTilesTexture(const std::string &name, const std::string &path);
    void loadShader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath);
    void loadFont(const std::string &name, const std::string &path, int fontSize);

    void loadAllTexturesInDirectory();

    std::shared_ptr<Texture> getTexture(const std::string &name);
    std::shared_ptr<Texture> getTileTexture(const std::string &name, Face face);
    std::array<std::shared_ptr<Texture>, 6> getTilesTexture(const std::string &name);
    std::shared_ptr<Shader> getShader(const std::string &name);
    std::shared_ptr<Font> getFont(const std::string &name);

private:
    std::unordered_map<std::string, std::shared_ptr<Texture>> _textures;
    std::unordered_map<std::string, std::array<std::shared_ptr<Texture>, 6>> _tilesTextures;
    std::unordered_map<std::string, std::shared_ptr<Shader>> _shaders;
    std::unordered_map<std::string, std::shared_ptr<Font>> _fonts;

    std::string images_path, shaders_path, fonts_path;
};

#endif // RESOURCESMANAGER_HPP
