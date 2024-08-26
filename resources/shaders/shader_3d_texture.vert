#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 FragPos;
out vec4 ourColor;
out vec2 TexCoord;
out vec3 vertEyeSpacePos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    // Position du fragment dans l'espace du modèle
    FragPos = vec3(model * vec4(aPos, 1.0));
    
    // Transférer la couleur et les coordonnées de texture
    ourColor = aColor;
    TexCoord = aTexCoord;
    
    // Position du vertex en espace caméra (view space)
    vertEyeSpacePos = vec3(view * model * vec4(aPos, 1.0));
    
    // Calcul de la position finale du vertex en clip space
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
