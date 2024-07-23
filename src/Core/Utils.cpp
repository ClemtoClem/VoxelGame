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
