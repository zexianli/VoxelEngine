#include "renderer.h"

Renderer::Renderer() {
	shaders = loadShaders();
}

Renderer::~Renderer() {

}

Shader Renderer::loadShaders() {
	return Shader("src/shaders/vertex/vertex_core.glsl", "src/shaders/fragment/fragment_core.glsl");
}

Shader Renderer::getShaders() {
	return shaders;
}

void Renderer::loadTextures(const char* textPath) {
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Setting texture filtering mode to nearest since we are using pixelated style
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// Load in texture from image
	stbi_set_flip_vertically_on_load(true);
	int width, height, colorChannels;
	unsigned char* data = stbi_load("src/terrain.png", &width, &height, &colorChannels, 0);
	// Create texture
	if (data) {
		// Generate texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "Texture width and height: " << width << " " << height << '\n';
	}
	else {
		std::cout << "FAILED TO LOAD TEXTURE 1" << '\n';
	}

	// Free data from loading image
	stbi_image_free(data);
}
