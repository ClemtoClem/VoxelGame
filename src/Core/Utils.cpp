#include "Utils.hpp"

float modulo2Pi(float value) {
	// Utiliser fmod pour trouver le reste de value / (2 * M_PI)
	double result = std::fmod(value, 2.0f * M_PI);
	
	// Assurer que le résultat est dans la plage [0, 2π)
	if (result < 0) {
		result += 2.0f * M_PI;
	}
	return result;
}

float modulo360(float value) {
	// Utiliser fmod pour trouver le reste de value / (2 * M_PI)
	double result = std::fmod(value, 360.0f);
	
	// Assurer que le résultat est dans la plage [0, 2π)
	if (result < 0) {
		result += 360.0f;
	}
	return result;
}

std::string glErrorToString(GLenum constant) {
	switch (constant) {
		case GL_NO_ERROR : return "GL_NO_ERROR";
		case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
		case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
		case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
		case GL_STACK_OVERFLOW: return "GL_STACK_OVERFLOW";
		case GL_STACK_UNDERFLOW: return "GL_STACK_UNDERFLOW";
		case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
	}
    return "";
}
