#include "Shader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include "Logger.hpp"

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) : _error("") {
	std::string vertexCode = loadShaderSource(vertexPath);
	if (vertexCode.empty()) {
		return;
	}
	//LOG(Info) << "Vertex shader loaded";
	
	std::string fragmentCode = loadShaderSource(fragmentPath);
	if (fragmentCode.empty()) {
		return;
	}
	//LOG(Info) << "Fragment shader loaded";

	_vertexShaderID   = compileShader(vertexCode.c_str(), GL_VERTEX_SHADER);
	_fragmentShaderID = compileShader(fragmentCode.c_str(), GL_FRAGMENT_SHADER);

	_programID = glCreateProgram();
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);
	glLinkProgram(_programID);
	checkCompileErrors(_programID, "PROGRAM");
}

Shader::~Shader() {
	cleanup();
}

std::string Shader::getError() {
	std::string str = _error;
	_error.clear();
	return str;
}

bool Shader::hasError() const {
	return !_error.empty();
}

void Shader::use() const {
	glUseProgram(_programID);
}

void Shader::unuse() const {
	glUseProgram(0);
}

void Shader::cleanup() {
	unuse();
	glDetachShader(_programID, GL_VERTEX_SHADER);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
	glDeleteProgram(_vertexShaderID);
	glDeleteProgram(_fragmentShaderID);
	glDeleteProgram(_programID);
}

void Shader::setBool(const std::string &name, bool value) const {
	glUniform1i(glGetUniformLocation(_programID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
	glUniform1i(glGetUniformLocation(_programID, name.c_str()), value);
}

void Shader::setUint(const std::string &name, unsigned int value) const {
	glUniform1ui(glGetUniformLocation(_programID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
	glUniform1f(glGetUniformLocation(_programID, name.c_str()), value);
}

void Shader::setDouble(const std::string &name, double value) const {
	glUniform1d(glGetUniformLocation(_programID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
	glUniform2fv(glGetUniformLocation(_programID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec2(const std::string &name, float x, float y) const {
	glUniform2f(glGetUniformLocation(_programID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
	glUniform3fv(glGetUniformLocation(_programID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const {
	glUniform3f(glGetUniformLocation(_programID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
	glUniform4fv(glGetUniformLocation(_programID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const {
	glUniform4f(glGetUniformLocation(_programID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string &name, const glm::mat2 &value) const {
	glUniformMatrix2fv(glGetUniformLocation(_programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setMat3(const std::string &name, const glm::mat3 &value) const {
	glUniformMatrix3fv(glGetUniformLocation(_programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setMat4(const std::string &name, const glm::mat4 &value) const {
	glUniformMatrix4fv(glGetUniformLocation(_programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

std::string Shader::loadShaderSource(const std::string &filePath) {
	std::ifstream shaderFile;
	std::stringstream shaderStream;

	// ouverture du fichier
	shaderFile.open(filePath);
	if (!shaderFile.is_open()) {
		std::stringstream ss;
		ss << "SHADER_FILE_NOT_FOUND: " << filePath;
		_error = ss.str();
		return "";
	}
	// lecture du fichier et place le contenu dans le flux
	shaderStream << shaderFile.rdbuf();
	shaderFile.close();

	return shaderStream.str();
}

GLuint Shader::compileShader(const std::string &source, GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);
	const GLchar* shaderCode = source.c_str();
	glShaderSource(shader, 1, &shaderCode, NULL);
	glCompileShader(shader);
	checkCompileErrors(shader, shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");
	return shader;
}

void Shader::checkCompileErrors(GLuint shader, std::string type) {
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::stringstream ss;
			ss << "SHADER_COMPILATION_ERROR of type: " << type << "\n\t\t" << infoLog;
			_error = ss.str();	
		} else {
			LOG(Debug) << "Shader " << type << " compiled successfully";
		}
	} else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::stringstream ss;
			ss << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n\t\t" << infoLog;
			_error = ss.str();
		} else {
			LOG(Debug) << "Program linked successfully";
		}
	}
}
