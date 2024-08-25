/**
 *  __ _        _
 * / _\ |_ __ _(_)_ __ 
 * \ \| __/ _` | | '__|
 * _\ \ || (_| | | |   
 * \__/\__\__,_|_|_|   
 * 
 * @file Stair.hpp
 * @author @ClemtoClem (https://github.com/ClemtoClem)
 * @date 23/07/2024
 * @brief Stair class
 */

#ifndef STAIR_HPP
#define STAIR_HPP

#include "Object.hpp"

namespace Render3D {

inline const std::vector<float> STAIR_VERTICES = {
	// Points(x,y,z)		RGBA Colors(r,g,b,a)	Texture coords(x,y)

	// Front face
	//	Step 1
	-0.5f,  -0.5f,   0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.0f,
	 0.5f,  -0.5f,   0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	1.0f,  0.0f,
	 0.5f,  -0.25f,  0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	1.0f,  0.25f,
	-0.5f,  -0.25f,  0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.25f,
	//	Step 2
	-0.5f,  -0.25f,  0.25f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.25f,
	 0.5f,  -0.25f,  0.25f,	1.0f, 1.0f, 1.0f, 1.0f,	1.0f,  0.25f,
	 0.5f,   0.0f,   0.25f,	1.0f, 1.0f, 1.0f, 1.0f,	1.0f,  0.5f,
	-0.5f,   0.0f,   0.25f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.5f,
	//	Step 3
	-0.5f,   0.0f,   0.0f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.5f,
	 0.5f,   0.0f,   0.0f,	1.0f, 1.0f, 1.0f, 1.0f,	1.0f,  0.5f,
	 0.5f,   0.25f,  0.0f,	1.0f, 1.0f, 1.0f, 1.0f,	1.0f,  0.75f,
	-0.5f,   0.25f,  0.0f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.75f,
	//	Step 4
	-0.5f,   0.25f, -0.25f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.75f,
	 0.5f,   0.25f, -0.25f,	1.0f, 1.0f, 1.0f, 1.0f,	1.0f,  0.75f,
	 0.5f,   0.5f,  -0.25f,	1.0f, 1.0f, 1.0f, 1.0f,	1.0f,  1.0f,
	-0.5f,   0.5f,  -0.25f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  1.0f,

	// Back face
	-0.5f,  -0.5f,  -0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.0f,
	 0.5f,  -0.5f,  -0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	1.0f,  0.0f,
	 0.5f,   0.5f,  -0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	1.0f,  1.0f,
	-0.5f,   0.5f,  -0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  1.0f,

	// Left face
	//	Step 1
	-0.5f,  -0.5f,  -0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.0f,
	-0.5f,  -0.5f,   0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	1.0f,  0.0f,
	-0.5f,  -0.25f,  0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	1.0f,  0.25f,
	-0.5f,  -0.25f, -0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.25f,
	//	Step 2
	-0.5f,  -0.25f, -0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.25f,
	-0.5f,  -0.25f,  0.25f,	1.0f, 1.0f, 1.0f, 1.0f,	0.75f, 0.25f,
	-0.5f,  -0.0f,   0.25f,	1.0f, 1.0f, 1.0f, 1.0f,	0.75f, 0.5f,
	-0.5f,  -0.0f,  -0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.5f,
	//	Step 3
	-0.5f,   0.0f,  -0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.5f,
	-0.5f,   0.0f,   0.0f,	1.0f, 1.0f, 1.0f, 1.0f,	0.5f,  0.5f,
	-0.5f,   0.25f,  0.0f,	1.0f, 1.0f, 1.0f, 1.0f,	0.5f,  0.75f,
	-0.5f,   0.25f, -0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.75f,
	//	Step 4
	-0.5f,   0.25f, -0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.75f,
	-0.5f,   0.25f, -0.25f,	1.0f, 1.0f, 1.0f, 1.0f,	0.25f, 0.75f,
	-0.5f,   0.5f,  -0.25f,	1.0f, 1.0f, 1.0f, 1.0f,	0.25f, 1.0f,
	-0.5f,   0.5f,  -0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  1.0f,

	// Right face
	//	Step 1
	 0.5f,  -0.5f,  -0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.0f,
	 0.5f,  -0.5f,   0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	1.0f,  0.0f,
	 0.5f,  -0.25f,  0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	1.0f,  0.25f,
	 0.5f,  -0.25f, -0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.25f,
	//	Step 2
	 0.5f,  -0.25f, -0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.25f,
	 0.5f,  -0.25f,  0.25f,	1.0f, 1.0f, 1.0f, 1.0f,	0.75f, 0.25f,
	 0.5f,   0.0f,   0.25f,	1.0f, 1.0f, 1.0f, 1.0f,	0.75f, 0.5f,
	 0.5f,   0.0f,  -0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.5f,
	//	Step 3
	 0.5f,   0.0f,  -0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.5f,
	 0.5f,   0.0f,   0.0f,	1.0f, 1.0f, 1.0f, 1.0f,	0.5f,  0.5f,
	 0.5f,   0.25f,  0.0f,	1.0f, 1.0f, 1.0f, 1.0f,	0.5f,  0.75f,
	 0.5f,   0.25f, -0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.75f,
	//	Step 4
	 0.5f,   0.25f, -0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.75f,
	 0.5f,   0.25f, -0.25f,	1.0f, 1.0f, 1.0f, 1.0f,	0.25f, 0.75f,
	 0.5f,   0.5f,  -0.25f,	1.0f, 1.0f, 1.0f, 1.0f,	0.25f, 1.0f,
	 0.5f,   0.5f,  -0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  1.0f,

	// Top face
	//	Step 1
	-0.5f,   0.5f,  -0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.0f,
	 0.5f,   0.5f,  -0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	1.0f,  0.0f,
	 0.5f,   0.5f,  -0.25f,	1.0f, 1.0f, 1.0f, 1.0f,	1.0f,  0.25f,
	-0.5f,   0.5f,  -0.25f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.25f,
	//	Step 2
	-0.5f,   0.25f, -0.25f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.25f,
	 0.5f,   0.25f, -0.25f,	1.0f, 1.0f, 1.0f, 1.0f,	1.0f,  0.25f,
	 0.5f,   0.25f,  0.0f,	1.0f, 1.0f, 1.0f, 1.0f,	1.0f,  0.5f,
	-0.5f,   0.25f,  0.0f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.5f,
	//	Step 3
	-0.5f,   0.0f,   0.0f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.5f,
	 0.5f,   0.0f,   0.0f,	1.0f, 1.0f, 1.0f, 1.0f,	1.0f,  0.5f,
	 0.5f,   0.0f,   0.25f,	1.0f, 1.0f, 1.0f, 1.0f,	1.0f,  0.75f,
	-0.5f,   0.0f,   0.25f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.75f,
	//	Step 4
	-0.5f,  -0.25f,  0.25f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  0.75f,
	 0.5f,  -0.25f,  0.25f,	1.0f, 1.0f, 1.0f, 1.0f,	1.0f,  0.75f,
	 0.5f,  -0.25f,  0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	1.0f,  1.0f,
	-0.5f,  -0.25f,  0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f,  1.0f,

	// Bottom face
	-0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f, 1.0f,	0.0f, 1.0f,
};

inline const std::vector<unsigned int> STAIR_NUMBER_OF_VERTICES_PER_FACE = {
	16, 4, 16, 16, 16, 4
};

inline const std::vector<unsigned int> STAIR_INDICES = {
	// Front face
	//	Step 1
	0, 1, 2, 2, 3, 0,
	//	Step 2
	4, 5, 6, 6, 7, 4,
	//	Step 3
	8, 9, 10, 10, 11, 8,
	//	Step 4
	12, 13, 14, 14, 15, 12,

	// Back face
	16, 17, 18, 18, 19, 16,

	// Left face
	//	Step 1
	20, 21, 22, 22, 23, 20,
	//	Step 2
	24, 25, 26, 26, 27, 24,
	//	Step 3
	28, 29, 30, 30, 31, 28,
	//	Step 4
	32, 33, 34, 34, 35, 32,

	// Right face
	//	Step 1
	36, 37, 38, 38, 39, 36,
	//	Step 2
	40, 41, 42, 42, 43, 40,
	//	Step 3
	44, 45, 46, 46, 47, 44,
	//	Step 4
	48, 49, 50, 50, 51, 48,

	// Top face
	//	Step 1
	52, 53, 54, 54, 55, 52,
	//	Step 2
	56, 57, 58, 58, 59, 56,
	//	Step 3
	60, 61, 62, 62, 63, 60,
	//	Step 4
	64, 65, 66, 66, 67, 64,

	// Bottom face
	68, 69, 70, 70, 71, 68
};

inline const std::vector<unsigned int> STAIR_NUMBER_OF_INDICES_PER_FACE = {
	24, 6, 24, 24, 24, 6
};

class Stair : public Object {
public:
	Stair(const glm::vec3 &position, const std::vector<glm::vec4> facesColors);
	Stair(const glm::vec3 &position, const std::array<std::shared_ptr<Texture>, 6> textures);

private:
	std::vector<float> colorFaces(const std::vector<float> &vertices, const std::vector<glm::vec4> &facesColors);
};

}

#endif // STAIR_HPP