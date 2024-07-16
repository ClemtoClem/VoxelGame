#ifndef RESOURCESMANAGER_HPP
#define RESOURCESMANAGER_HPP

#include <string>
#include <vector>
#include <array>
#include <memory>
#include "Utils.hpp"
#include "Texture.hpp"
#include "Font.hpp"
#include "Shader.hpp"
#include "Logger.hpp"

const std::string IMAGES_PATH_DEFAULT = "./resources/images/";
const std::string SHADERS_PATH_DEFAULT = "./resources/shaders/";
const std::string FONTS_PATH_DEFAULT = "./resources/fonts/";

enum Face {
    FRONT = 1U,
    BACK = 2U,
    LEFT = 4U,
    RIGHT = 8U,
    UP = 16U,
    DOWN = 32U,
};

enum class ResourceType {
    TEXTURE,
    SHADER,
    TILES_TEXTURE,
    FONT
};

struct Resource {
    ResourceType type;
    std::string name;
    std::string path;
    void *data;
};

class ResourcesManager {
public:
    ResourcesManager();

    static ResourcesManager &getInstance();

    void setPaths(const std::string &images_path, const std::string &shaders_path, const std::string &fonts_path);

    void loadTexture(const std::string &name, const std::string &path);
    void loadTilesTexture(const std::string &name, const std::string &path);
    void loadShader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath);
    void loadFont(const std::string &name, const std::string &path);

    std::shared_ptr<Texture> getTexture(const std::string &name);
    std::shared_ptr<Texture> getTileTexture(const std::string &name, Face face);
    std::array<std::shared_ptr<Texture>, 6> getTilesTexture(const std::string &name);
    std::shared_ptr<Shader> getShader(const std::string &name);
    std::shared_ptr<Font> getFont(const std::string &name);

private:
    std::vector<Resource> _resources;
    std::string _imagesPath, _shadersPath, _fontsPath;

    std::shared_ptr<Texture> createDefaultTexture();

    // Méthode pour logguer les erreurs
    void logError(const std::string &message) {
        LOG(Error) << message;
    }
};

#endif // RESOURCESMANAGER_HPP
