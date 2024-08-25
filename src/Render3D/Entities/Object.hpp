#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>
#include <string>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Entity.hpp"
#include "../../Core/Shader.hpp"
#include "../../Core/Texture.hpp"

namespace Render3D {

class Object : public Entity {
public:
	enum class FormatFile {
		Data, // Fichier avec les vertices et les indices
		Object // Fichier .obj
	};

	enum DrawType {
		Colored,
		Textured
	};

	Object(const std::string &typeName, const glm::vec3 &position, const std::vector<glm::vec4> &facesColors, const std::vector<float> &vertices, const std::vector<unsigned int> &indices, const std::vector<unsigned int> &numberOfIndicesPerFace);
	Object(const std::string &typeName, const glm::vec3 &position, const std::array<std::shared_ptr<Texture>, 6> &facesTextures, const std::vector<float> &vertices, const std::vector<unsigned int> &indices, const std::vector<unsigned int> &numberOfIndicesPerFace);
	Object(const std::string &typeName, const glm::vec3 &position, const std::array<std::shared_ptr<Texture>, 6> &facesTextures, const std::string &filename, FormatFile format);

	virtual ~Object();

	bool loadMeshFromFile(const std::string &meshFile, FormatFile format);
	bool setupSuccessfully() const;

	virtual void setFacesColors(const std::vector<glm::vec4> &facesColors);
	virtual void setFacesTextures(const std::array<std::shared_ptr<Texture>, 6> &facesTextures);

	virtual glm::vec3 &position() override;
	virtual const glm::vec3 &position() const override;
	virtual void position(const glm::vec3 &point) override;

	virtual void rotate(float angle, const glm::vec3 &axis) override;

	float &angle() override;
	const float &angle() const override;
	void angle(float angle) override;

	glm::vec3 &rotateAxis() override;
	const glm::vec3 &rotateAxis() const override;

	void rotateAxis(const glm::vec3 &axis) override;
	const glm::mat4 &modelMatrix() const override;
	
	virtual std::vector<glm::vec3> getBoundingBoxCorners() const override;

	virtual void update(float dt) override;
	virtual void render(const Shader &shader) const override;

protected:
	void free();

	void setupMesh(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<unsigned int> numberOfIndicesPerFace);

private:
	void updateModelMatrix();

	DrawType _drawType;

	glm::vec3 _position;
	float _angle;
	glm::vec3 _rotateAxis;
	glm::mat4 _modelMatrix;
	std::vector<glm::vec4> _facesColor;
	std::array<std::shared_ptr<Texture>, 6> _facesTextures;
	GLuint _vao, _vbo, _ebo;
	std::vector<unsigned int> _numberOfIndicesPerFace;
	bool _isMeshSetup;
};

} // namespace Render3D

#endif // OBJECT_HPP
