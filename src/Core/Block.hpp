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
#include "Shader.hpp"

class Block : public Entity {
public:
	Block(const glm::vec3 &position, const std::array<GLuint, 6> textures);
	virtual ~Block();

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

private:
	void setupMesh();
	//void loadTextures(const std::array<std::string, 6> &textureFiles);
	void updateModelMatrix();

	glm::vec3 _position;
	float _angle;
	glm::vec3 _rotateAxis;
	glm::mat4 _modelMatrix;
	std::array<GLuint, 6> _textures;
	GLuint _vao, _vbo, _ebo;
};

#endif // BLOCK_HPP
