/**
 *  __ _               _		   
 * / _\ |__   __ _  __| | ___ _ __ 
 * \ \| '_ \ / _` |/ _` |/ _ \ '__|
 * _\ \ | | | (_| | (_| |  __/ |   
 * \__/_| |_|\__,_|\__,_|\___|_|   
 * 
 * @file Shader.hpp
 * @author @ClemtoClem (https://github.com/ClemtoClem)
 * @date 09/07/2024
 * @brief Shader class
 */

#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>

class Shader {
public:
	// le constructeur lit et construit le shader
	Shader(const std::string &vertexPath, const std::string &fragmentPath);
	
	~Shader();

	std::string getError();
	bool hasError() const;

	// Activation du shader
	void use() const;
	// Désactivation du shader
	void unuse() const;

	void cleanup();
	
	// fonctions utiles pour l'uniform
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setUint(const std::string &name, unsigned int value) const;
	void setFloat(const std::string &name, float value) const;
	void setDouble(const std::string &name, double value) const;
	void setVec2(const std::string &name, const glm::vec2 &value) const;
	void setVec2(const std::string &name, float x, float y) const;
	void setVec3(const std::string &name, const glm::vec3 &value) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	void setVec4(const std::string &name, const glm::vec4 &value) const;
	void setVec4(const std::string &name, float x, float y, float z, float w) const;
	void setMat2(const std::string &name, const glm::mat2 &value) const;
	void setMat3(const std::string &name, const glm::mat3 &value) const;
	void setMat4(const std::string &name, const glm::mat4 &value) const;

private:
	GLuint _programID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
	std::string loadShaderSource(const std::string &filePath);
	GLuint compileShader(const std::string &source, GLenum shaderType);
	void checkCompileErrors(GLuint shader, std::string type);

	std::string _error;
};

#endif // SHADER_HPP
