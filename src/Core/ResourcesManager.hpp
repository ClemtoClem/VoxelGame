/**
 *    __
 *   /__\ ___  ___ ___  ___  _   _ _ __ ___ ___  ___	/\/\   __ _ _ __   __ _  __ _  ___ _ __ 
 *  / \/// _ \/ __/ __|/ _ \| | | | '__/ __/ _ \/ __|  /	\ / _` | '_ \ / _` |/ _` |/ _ \ '__|
 * / _  \  __/\__ \__ \ (_) | |_| | | | (_|  __/\__ \ / /\/\ \ (_| | | | | (_| | (_| |  __/ |   
 * \/ \_/\___||___/___/\___/ \__,_|_|  \___\___||___/ \/    \/\__,_|_| |_|\__,_|\__, |\___|_|   
 *                                                                              |___/
 * @file ResourcesManager.hpp
 * @author @ClemtoClem (https://github.com/ClemtoClem)
 * @date 06/07/2024
 * @brief ResourcesManager class
 */

#ifndef RESOURCES_MANAGER_HPP
#define RESOURCES_MANAGER_HPP

#include <string>
#include <vector>
#include <array>
#include <memory>
#include "Utils.hpp"
#include "Texture.hpp"
#include "Font.hpp"
#include "Shader.hpp"
#include "Logger.hpp"

const std::string IMAGES_PATH_DEFAULT  = "./resources/images/";
const std::string SHADERS_PATH_DEFAULT = "./resources/shaders/";
const std::string FONTS_PATH_DEFAULT   = "./resources/fonts/";

enum class ResourceType {
	TEXTURE,
	SHADER,
	FONT
};

struct Resource {
	ResourceType type;
	std::string name;
	std::string path;
	std::shared_ptr<void> data; // Utilisation de void* pour le stockage générique des ressources
};

class ResourcesManager {
public:
	ResourcesManager();

	static std::shared_ptr<ResourcesManager> getInstance();

	void setPaths(const std::string &images_path, const std::string &shaders_path, const std::string &fonts_path);

	bool loadTexture(const std::string &name, const std::string &path);
	bool loadShader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath);
	bool loadFont(const std::string &name, const std::string &path);

	std::shared_ptr<Texture> getTexture(const std::string &name);
	std::shared_ptr<Shader> getShader(const std::string &name);
	std::shared_ptr<Font> getFont(const std::string &name);


	static std::shared_ptr<ResourcesManager> instance;

private:
	std::vector<Resource> _resources;
	std::string _imagesPath, _shadersPath, _fontsPath;

	void createDefaultTexture();
	std::shared_ptr<Texture> _defaultTexture;
};

using ResourcesManagerPtr = std::shared_ptr<ResourcesManager>;

#endif // RESOURCES_MANAGER_HPP
