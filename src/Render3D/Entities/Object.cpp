#include "Object.hpp"
#include "../../Core/Logger.hpp"
#include "../../Core/CustomException.hpp"
#include "../../Core/Utils.hpp"

namespace Render3D {

Object::Object(const std::string &typeName, const glm::vec3 &position, const std::vector<glm::vec4> &facesColors, const std::vector<float> &vertices, const std::vector<unsigned int> &indices, const std::vector<unsigned int> &numberOfIndicesPerFace) 
	: Entity(typeName), _drawType(DrawType::Colored), _position(position), _angle(0.0f), _rotateAxis(glm::vec3(0.0f, 1.0f, 0.0f)), _facesColor(facesColors) {
	setupMesh(vertices, indices, numberOfIndicesPerFace);
	updateModelMatrix();
}

Object::Object(const std::string &typeName, const glm::vec3 &position, const std::array<std::shared_ptr<Texture>, 6> &facesTextures, const std::vector<float> &vertices, const std::vector<unsigned int> &indices, const std::vector<unsigned int> &numberOfIndicesPerFace) 
	: Entity(typeName), _drawType(DrawType::Textured), _position(position), _angle(0.0f), _rotateAxis(glm::vec3(0.0f, 1.0f, 0.0f)), _facesTextures(facesTextures) {
	setupMesh(vertices, indices, numberOfIndicesPerFace);
	updateModelMatrix();
}

Object::Object(const std::string &typeName, const glm::vec3 &position, const std::array<std::shared_ptr<Texture>, 6> &facesTextures, const std::string &filename, FormatFile format)
	: Entity(typeName), _drawType(DrawType::Textured), _position(position), _angle(0.0f), _rotateAxis(glm::vec3(0.0f, 1.0f, 0.0f)), _facesTextures(facesTextures) {
	
	if (!loadMeshFromFile(filename, format)) {
		LOG(Error) << "Mesh could not be loaded from file: " << filename;
		_typeName = "Object:Error";
		_drawType = DrawType::Colored;
	}
	updateModelMatrix();
}

Object::~Object() {
	free();
}

void Object::setupMesh(std::vector<float> vertices, std::vector<unsigned int> indices, std::vector<unsigned int> numberOfIndicesPerFace) {
	/*
					┌───────────────────────────────────────────────────┐───────────────────────────────────────────────────┐
					|                 vertex 1 bit map                  |                 vertex 2 bit map                  |
					├───┬───┬───┬───┬───┬───┬───┬───────────┬───────────┼───┬───┬───┬───┬───┬───┬───┬───────────┬───────────┤
					| x | y | z | R | G | B | A | texCoordX | texCoordY | x | y | z | R | G | B | A | texCoordX | texCoordY |
					└───┴───┴───┴───┴───┴───┴───┴───────────┴───────────┘───┴───┴───┴───┴───┴───┴───┴───────────┴───────────┘
					0   4   8   12  16  20  24  28         32          36  40  44  48  52  56  60  64          68          72
		position:	├─────────────────────STRIDE:36────────────────────>
		color:		├offset:12─>├─────────────────────STRIDE:36────────────────────>
		texCoords:	├─────────offset:28────────>├─────────────────────STRIDE:36────────────────────>
	*/

	// Vérifier si le tableau de vertices a une taille règlementaire
	if (vertices.size() % 36 != 0) {
		LOG(Error) << getTypeName() << ": Vertices array size is not a multiple of 36";
		_isMeshSetup = false;
	}

	// Stocker le nombre d'indices par face
	_numberOfIndicesPerFace = numberOfIndicesPerFace;

	// Générer les buffers et l'array object
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	// Lier le Vertex Array Object
	glBindVertexArray(_vao);

	// Charger les vertices dans un GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	// Charger les indices dans un GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	// Attribut de position (x, y, z)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 36, (void*)(0));
	glEnableVertexAttribArray(0);

	// Attribut de couleur (R, G, B, A)
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 36, (void*)(12));
	glEnableVertexAttribArray(1);

	// Attribut de coordonnées de texture (texCoordX, texCoordY)
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 36, (void*)(28));
	glEnableVertexAttribArray(2);

	// Délier le VAO
	glBindVertexArray(0);

	// Indiquer que le mesh est configuré
	_isMeshSetup = true;
}

bool Object::loadMeshFromFile(const std::string &meshFile, FormatFile format) {

	return true;
}

bool Object::setupSuccessfully() const {
    return _isMeshSetup;
}

void Object::free() {
	if (_isMeshSetup) {
		glDeleteVertexArrays(1, &_vao);
		glDeleteBuffers(1, &_vbo);
		glDeleteBuffers(1, &_ebo);
		_isMeshSetup = false;
	}
}

void Object::setFacesColors(const std::vector<glm::vec4> &facesColors) {
	_facesColor = facesColors;
	_drawType = DrawType::Colored;
}

void Object::setFacesTextures(const std::array<std::shared_ptr<Texture>, 6> &facesTextures) {
	_facesTextures = facesTextures;
	_drawType = DrawType::Textured;
}

glm::vec3 &Object::position() {
	return _position;
}

const glm::vec3 &Object::position() const {
	return _position;
}

void Object::position(const glm::vec3 &point) {
	_position = point;
	updateModelMatrix();
}

void Object::rotate(float angle, const glm::vec3 &axis) {
	_angle = angle;
	_rotateAxis = axis;
	updateModelMatrix();
}

float &Object::angle() {
	return _angle;
}

const float &Object::angle() const {
	return _angle;
}

void Object::angle(float angle) {
	_angle = angle;
	updateModelMatrix();
}

glm::vec3 &Object::rotateAxis() {
	return _rotateAxis;
}

const glm::vec3 &Object::rotateAxis() const {
	return _rotateAxis;
}

void Object::rotateAxis(const glm::vec3 &axis) {
	_rotateAxis = axis;
	updateModelMatrix();
}

const glm::mat4 &Object::modelMatrix() const {
	return _modelMatrix;
}

void Object::updateModelMatrix() {
	_modelMatrix = glm::mat4(1.0f);
	_modelMatrix = glm::translate(_modelMatrix, _position);
	_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_angle), _rotateAxis);
}

std::vector<glm::vec3> Object::getBoundingBoxCorners() const {
	glm::vec3 minCorner = _position - glm::vec3(0.5f);
	glm::vec3 maxCorner = _position + glm::vec3(0.5f);
	
	std::vector<glm::vec3> boundingBoxCorners(8);
	boundingBoxCorners[0] = minCorner;
	boundingBoxCorners[1] = glm::vec3(minCorner.x, minCorner.y, maxCorner.z);
	boundingBoxCorners[2] = glm::vec3(minCorner.x, maxCorner.y, minCorner.z);
	boundingBoxCorners[3] = glm::vec3(maxCorner.x, minCorner.y, minCorner.z);
	boundingBoxCorners[4] = glm::vec3(maxCorner.x, maxCorner.y, minCorner.z);
	boundingBoxCorners[5] = glm::vec3(maxCorner.x, minCorner.y, maxCorner.z);
	boundingBoxCorners[6] = glm::vec3(minCorner.x, maxCorner.y, maxCorner.z);
	boundingBoxCorners[7] = maxCorner;

	// Appliquer la matrice de transformation à chaque coin.
	for (auto& corner : boundingBoxCorners) {
		corner = glm::vec3(_modelMatrix * glm::vec4(corner, 1.0f));
	}

	return boundingBoxCorners;
}

void Object::update(float dt) {
	updateModelMatrix();
}

void Object::render(const Shader &shader) const {
	if (!_isMeshSetup) {
		LOG(Error) << "Mesh is not setup";
		return;
	}

	glBindVertexArray(_vao);

	unsigned int offset = 0;
	for (int i = 0; i < 6; ++i) {
		_facesTextures[i]->use();
		glDrawElements(GL_TRIANGLES, _numberOfIndicesPerFace[i], GL_UNSIGNED_INT, (void*)(offset * sizeof(unsigned int)));
		offset += _numberOfIndicesPerFace[i];
	}

	glBindVertexArray(0);
}

} // namespace Render3D
