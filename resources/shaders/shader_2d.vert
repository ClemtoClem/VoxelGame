#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 projection; // Matrice de projection
uniform mat4 transform; // Matrice de transformation

void main() {
	TexCoords = aTexCoords;
	gl_Position = projection * transform * vec4(aPos.xy, 0.0, 1.0);
}
