#ifndef UTILS_HPP
#define UTILS_HPP

enum Face {
    FRONT = 1U,
    BACK = 2U,
    LEFT = 4U,
    RIGHT = 8U,
    UP = 16U,
    DOWN = 32U,
};

struct Material {
	int diffuse;
	int specular;
	int emission;
	float shininess;
};

#endif // UTILS_HPP