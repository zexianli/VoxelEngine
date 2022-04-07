#version 330 core
in vec3 newColor;
out vec4 FragColor;

void main() {
	FragColor = vec4(newColor, 1.0);
}