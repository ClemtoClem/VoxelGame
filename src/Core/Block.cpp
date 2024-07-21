#include "Block.hpp"
#include "Logger.hpp"

Block::Block(const glm::vec3 &position, const std::array<GLuint, 6> textures)
	: _position(position), _angle(0.0f), _rotateAxis(glm::vec3(0.0f, 1.0f, 0.0f)), _modelMatrix(1.0f), _textures(textures) {
	//loadTextures(textureFiles);
	setupMesh();
}

Block::~Block() {
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ebo);
	//glDeleteTextures(6, _textures);
}

std::array<glm::vec3, 8> Block::getBoundingBoxCorners() const {
	glm::vec3 min = _position - glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 max = _position + glm::vec3(0.5f, 0.5f, 0.5f);

	return {
		min,
		glm::vec3(max.x, min.y, min.z),
		glm::vec3(max.x, max.y, min.z),
		glm::vec3(min.x, max.y, min.z),
		glm::vec3(min.x, min.y, max.z),
		glm::vec3(max.x, min.y, max.z),
		glm::vec3(max.x, max.y, max.z),
		glm::vec3(min.x, max.y, max.z)
	};
}

/*void Block::loadTextures(const std::array<std::string, 6> &textureFiles) {
	glGenTextures(6, _textures);

	for (int i = 0; i < 6; ++i) {
		glBindTexture(GL_TEXTURE_2D, _textures[i]);

		SDL_Surface *surface = IMG_Load(textureFiles[i].c_str());
		if (!surface) {
			LOG(Error) << "Failed to load texture: " << textureFiles[i] << " " << IMG_GetError();
			continue;
		}

		int mode = surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;

		glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
		
		// Filtrage
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glGenerateMipmap(GL_TEXTURE_2D);

		SDL_FreeSurface(surface);
	}
}*/

void Block::setupMesh() {
	float vertices[] = {
		// positions          // texture coords
		// Front face
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		// Back face
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		// Left face
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		// Right face
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		// Top face
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		// Bottom face
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	};

	unsigned int indices[] = {
		// Front face
		0, 1, 2, 2, 3, 0,
		// Back face
		4, 5, 6, 6, 7, 4,
		// Left face
		8, 9, 10, 10, 11, 8,
		// Right face
		12, 13, 14, 14, 15, 12,
		// Top face
		16, 17, 18, 18, 19, 16,
		// Bottom face
		20, 21, 22, 22, 23, 20,
	};

	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

glm::vec3 &Block::position() {
	return _position;
}

const glm::vec3 &Block::position() const {
	return _position;
}

void Block::position(const glm::vec3 &point) {
	_position = point;
}

void Block::rotate(float angle, const glm::vec3 &axis) {
	_angle = angle;
	_rotateAxis = glm::normalize(axis);
}

float &Block::angle() {
    return _angle;
}

const float &Block::angle() const {
    return _angle;
}

void Block::angle(float angle) {
	_angle = angle;
}

glm::vec3 &Block::rotateAxis() {
	return _rotateAxis;
}

const glm::vec3 &Block::rotateAxis() const  {
	return _rotateAxis;
}

void Block::rotateAxis(const glm::vec3 &axis) {
	_rotateAxis = glm::normalize(axis);
}

const glm::mat4 &Block::modelMatrix() const {
	return _modelMatrix;
}

void Block::update(float dt) {
	// Update logic for Block
	updateModelMatrix();
}

void Block::updateModelMatrix() {
	_modelMatrix = glm::translate(glm::mat4(1.0f), _position);
	_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_angle), _rotateAxis);
}

void Block::render(const Shader &shader) const {
	glBindVertexArray(_vao);

	shader.setMat4("model", _modelMatrix);
	
	for (int i = 0; i < 6; ++i) {
		glBindTexture(GL_TEXTURE_2D, _textures[i]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(i * 6 * sizeof(unsigned int)));
	}

	glBindVertexArray(0);
}