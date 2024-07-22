/**
 *    ___ _            _    
 *   / __\ | ___   ___| | __
 *  /__\// |/ _ \ / __| |/ /
 * / \/  \ | (_) | (__|   < 
 * \_____/_|\___/ \___|_|\_\
 *
 * @file Block.hpp
 * @author @ClemtoClem
 * @date 09/07/2024
 * @brief Block class
*/

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <array>
#include <string>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Entity.hpp"
#include "../Shader.hpp"
#include "../Texture.hpp"
#include "../tiny_obj_loader.hpp"

class Block : public Entity {
public:
	enum class FormatFile {
		Data, // Fichier avec les vertices et les indices
		Object // Fichier .obj
	};

	Block(const std::string &typeName, const glm::vec3 &position, const std::array<std::shared_ptr<Texture>, 6> &textures, const std::vector<float> &vertices, const std::vector<unsigned int> &indice, const std::vector<unsigned int> &numberOfIndicesPerFace);
	Block(const std::string &typeName, const glm::vec3 &position, const std::array<std::shared_ptr<Texture>, 6> &textures, const std::string &filename, FormatFile format);

	virtual ~Block();

	/*bool loadMeshFromObj(const std::string &filename);*/
	bool loadMeshFromFile(const std::string &meshFile);

	virtual std::array<glm::vec3, 8> getBoundingBoxCorners() const override;

	virtual glm::vec3 &position() override;
	virtual const glm::vec3 &position() const override;
	virtual void position(const glm::vec3 &point) override;

	virtual void rotate(float angle, const glm::vec3 &axis) override;

	float &angle() override;
	float const &angle() const override;
	void angle(float angle) override;

	glm::vec3 &rotateAxis() override;
	const glm::vec3 &rotateAxis() const override;

	void rotateAxis(const glm::vec3 &axis) override;
	const glm::mat4 &modelMatrix() const override;

	virtual void update(float dt) override;
	virtual void render(const Shader &shader) const override;

protected:
	void free();

	void setupMesh(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<unsigned int> numberOfIndicesPerFace);

private:
	void updateModelMatrix();

	// créer des vertices et indices à partir d'une liste de cuboid
	/*void createVerticesAndIndicesFromCuboid(const std::vector<std::pair<glm::vec3, glm::vec3>>& cuboids,
                                    std::vector<float>& vertices,
                                    std::vector<unsigned int>& indices);
	*/

	glm::vec3 _position;
	float _angle;
	glm::vec3 _rotateAxis;
	glm::mat4 _modelMatrix;
	std::array<std::shared_ptr<Texture>, 6> _textures;
	GLuint _vao, _vbo, _ebo;
	std::vector<unsigned int> _numberOfIndicesPerFace;
	bool _isMeshSetup;
};

#endif // BLOCK_HPP
