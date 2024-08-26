#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec4 ourColor;
in vec2 TexCoord;
in vec3 vertEyeSpacePos;

uniform sampler2D ourTexture;

// Uniformes pour contrôler le brouillard
uniform float fogStart; // Distance à laquelle le brouillard commence
uniform float fogEnd;   // Distance à laquelle le brouillard devient maximal
uniform vec4 fogColor;  // Couleur du brouillard

void main() {
    // Calcul de la distance du fragment à la caméra dans l'espace caméra
    float dist = length(vertEyeSpacePos);

    // Calcul du facteur de brouillard en fonction de la distance
    float fogFactor = clamp((fogEnd - dist) / (fogEnd - fogStart), 0.0, 1.0);

    // Mélange de la couleur de la texture avec la couleur du brouillard
    vec4 texColor = texture(ourTexture, TexCoord) * ourColor;
    FragColor = mix(fogColor, texColor, fogFactor);
}
