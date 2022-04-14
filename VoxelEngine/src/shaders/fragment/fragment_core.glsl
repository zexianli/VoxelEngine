#version 330 core
//in vec3 newColor;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D texture1;

void main() {
	FragColor = texture2D(texture1, texCoord);
}