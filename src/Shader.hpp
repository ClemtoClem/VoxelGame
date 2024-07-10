/**
 *  __ _               _           
 * / _\ |__   __ _  __| | ___ _ __ 
 * \ \| '_ \ / _` |/ _` |/ _ \ '__|
 * _\ \ | | | (_| | (_| |  __/ |   
 * \__/_| |_|\__,_|\__,_|\___|_|   
 * 
 * @file Shader.hpp
 * @author ClemtoClem
 * @date 09/07/2024
 */

#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>

class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void use() const;
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec3(const std::string &name, const glm::vec3 &value) const;
	void setMat4(const std::string &name, const glm::mat4 &value) const;

private:
	GLuint _programID;
	std::string loadShaderSource(const char* filePath);
	GLuint compileShader(const char* source, GLenum shaderType);
	void checkCompileErrors(GLuint shader, std::string type);
};

#endif // SHADER_HPP
