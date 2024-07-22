#include "Block.hpp"
#include "../Logger.hpp"
#include "../Utils.hpp"

Block::Block(const std::string &typeName, const glm::vec3 &position, const std::array<std::shared_ptr<Texture>, 6> &textures, const std::vector<float> &vertices, const std::vector<unsigned int> &indices, const std::vector<unsigned int> &numberOfIndicesPerFace)
	: Entity(typeName), _position(position), _angle(0.0f), _rotateAxis(glm::vec3(0.0f, 1.0f, 0.0f)), _modelMatrix(1.0f), _textures(textures), _isMeshSetup(false) {
		setupMesh(vertices, indices, numberOfIndicesPerFace);
}

Block::Block(const std::string &typeName, const glm::vec3 &position, const std::array<std::shared_ptr<Texture>, 6> &textures, const std::string &filename, FormatFile format)
	: Entity(typeName), _position(position), _angle(0.0f), _rotateAxis(glm::vec3(0.0f, 1.0f, 0.0f)), _modelMatrix(1.0f), _textures(textures), _isMeshSetup(false) {
		
		bool result = false;
		switch (format) {
			case FormatFile::Object:
				//result = loadMeshFromObj(filename);
				break;
			case FormatFile::Data:
				result = loadMeshFromFile(filename);
				break;
		}
		if (!result) {
			throw std::runtime_error("Failed to load mesh from file: " + filename);
		}
}

Block::~Block() {
	free();
}

/*bool Block::loadMeshFromObj(const std::string &filename) {
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn;
	std::string err;

	// Charger le fichier .obj
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename.c_str(), NULL, true);
	
	if (!warn.empty()) {
		LOG(Warning) << warn << std::endl;
	}

	if (!err.empty()) {
		LOG(Error) << err << std::endl;
	}

	if (!ret) {
		LOG(Error) << "Failed to load/parse .obj file: " << filename << std::endl;
		return false;
	}

	// Parcourir les formes (shapes)
	for (const auto& shape : shapes) {
		// Parcourir les indices
		for (const auto& index : shape.mesh.indices) {
			// Extraire les vertices
			vertices.push_back(attrib.vertices[3 * index.vertex_index + 0]);
			vertices.push_back(attrib.vertices[3 * index.vertex_index + 1]);
			vertices.push_back(attrib.vertices[3 * index.vertex_index + 2]);

			// Extraire les coordonnées de texture (si elles existent)
			if (!attrib.texcoords.empty()) {
				vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
				vertices.push_back(attrib.texcoords[2 * index.texcoord_index + 1]);
			}

			// Ajouter l'indice
			indices.push_back(indices.size());
		}
	}

	setupMesh(vertices, indices);

	return true;
}
*/
bool Block::loadMeshFromFile(const std::string &filename) {
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<unsigned int> numberOfIndicesPerFace;

	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Unable to open file: " + filename);
	}

	std::string line;
	bool readingVertices = true;
	bool readingIndices = false;

	while (std::getline(file, line)) {
		if (line.empty() || line[0] == '/') {
			continue; // Ignore empty lines or comments
		}

		std::istringstream iss(line);
		if (readingVertices) {
			float x, y, z, u, v;
			if (iss >> x >> y >> z >> u >> v) {
				vertices.insert(vertices.end(), {x, y, z, u, v});
			} else {
				readingVertices = false;
				readingIndices = true;
			}
		}

		if (!readingVertices && readingIndices) {
			unsigned int i1, i2, i3;
			if (iss >> i1 >> i2 >> i3) {
				indices.insert(indices.end(), {i1, i2, i3});
			} else {
				readingIndices = false;
			}
		}

		if (!readingVertices && !readingIndices) {
			unsigned int nb;
			if (iss >> nb)
				numberOfIndicesPerFace.push_back(nb);
		}
	}

	file.close();

	if (vertices.empty() || indices.empty()) {
		LOG(Warning) << "File is empty!";
		return false;
	}

	setupMesh(vertices, indices, numberOfIndicesPerFace);

	return true;
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

void Block::free() {
	if (_isMeshSetup) {
		glDeleteVertexArrays(1, &_vao);
		glDeleteBuffers(1, &_vbo);
		glDeleteBuffers(1, &_ebo);
		_isMeshSetup = false;
	}
}

void Block::setupMesh(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<unsigned int> numberOfIndicesPerFace) {
	if (vertices.empty() || indices.empty()) return;
	free();
	_numberOfIndicesPerFace = numberOfIndicesPerFace;

	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	glBindVertexArray(_vao);

	// Charger les vertices dans un GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	// Charger les indices dans un GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Assurez-vous de vérifier les erreurs
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		LOG(Error) << "OpenGL Error: " << error << std::endl;
		return;
	}

	_isMeshSetup = true;
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
void Block::updateModelMatrix() {
	_modelMatrix = glm::translate(glm::mat4(1.0f), _position);
	_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_angle), _rotateAxis);
}

/*
void Block::createVerticesAndIndicesFromCuboid(const std::vector<std::pair<glm::vec3, glm::vec3>> &cuboids, std::vector<float> &vertices, std::vector<unsigned int> &indices) {
	size_t indexOffset = 0;

	for (const auto& cuboid : cuboids) {
		glm::vec3 p1 = cuboid.first;
		glm::vec3 p2 = cuboid.second;

		// Calcul des coins du parallélépipède
		glm::vec3 v0 = glm::vec3(p1.x, p1.y, p1.z);
		glm::vec3 v1 = glm::vec3(p2.x, p1.y, p1.z);
		glm::vec3 v2 = glm::vec3(p2.x, p2.y, p1.z);
		glm::vec3 v3 = glm::vec3(p1.x, p2.y, p1.z);
		glm::vec3 v4 = glm::vec3(p1.x, p1.y, p2.z);
		glm::vec3 v5 = glm::vec3(p2.x, p1.y, p2.z);
		glm::vec3 v6 = glm::vec3(p2.x, p2.y, p2.z);
		glm::vec3 v7 = glm::vec3(p1.x, p2.y, p2.z);

		// Coordonnées de texture
		float text0[4] = {0.0f, 0.0f, 0.0f, 0.0f};
		float text1[4] = {0.0f, 0.0f, 0.0f, 0.0f};
		float text2[4] = {0.0f, 0.0f, 0.0f, 0.0f};
		float text3[4] = {0.0f, 0.0f, 0.0f, 0.0f};
		float text4[4] = {0.0f, 0.0f, 0.0f, 0.0f};
		float text5[4] = {0.0f, 0.0f, 0.0f, 0.0f};

		// Faces du parallélépipède (chaque face est définie par deux triangles)

		Face faces[6] = {
			// Face avant
			{ {v0, v1, v2, v3}, text0, {0, 1, 2, 0, 2, 3} },
			// Face arrière
			{ {v4, v5, v6, v7}, text1, {4, 5, 6, 4, 6, 7} },
			// Face gauche
			{ {v0, v3, v7, v4}, text2, {8, 9, 10, 8, 10, 11} },
			// Face droite
			{ {v1, v5, v6, v2}, text3, {12, 13, 14, 12, 14, 15} },
			// Face haut
			{ {v3, v2, v6, v7}, text4, {16, 17, 18, 16, 18, 19} },
			// Face bas
			{ {v0, v1, v5, v4}, text5, {20, 21, 22, 20, 22, 23} }
		};

		for (const auto& face : faces) {
			for (int i = 0; i < 4; ++i) {
				vertices.push_back(face.vertices[i].x);
				vertices.push_back(face.vertices[i].y);
				vertices.push_back(face.vertices[i].z);
				vertices.push_back(face.texCoords[2 * i]);
				vertices.push_back(face.texCoords[2 * i + 1]);
			}
			for (int i = 0; i < 6; ++i) {
				indices.push_back(indexOffset + face.indices[i]);
			}
			indexOffset += 4;
		}
	}
}*/

void Block::update(float dt) {
	// Update logic for Block
	updateModelMatrix();
}


void Block::render(const Shader &shader) const {
	if (_isMeshSetup) {
		glBindVertexArray(_vao);

		shader.setMat4("model", _modelMatrix);
		
		unsigned int offset=0;
		for (int i = 0; i < 6; ++i) {
			_textures[i]->use();
			glDrawElements(GL_TRIANGLES, _numberOfIndicesPerFace[i], GL_UNSIGNED_INT, (void*)(offset * sizeof(unsigned int)));
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(i * 6 * sizeof(unsigned int)));
			offset += _numberOfIndicesPerFace[i];
		}

		glBindVertexArray(0);
	}
}
