#ifndef RENDERER_H
#define RENDERER_H

#include "../core/shader.h"
#include "../core/stb_image.h"

class Renderer {
private:
	Shader shaders;

	Shader loadShaders();
public:
	Renderer();
	~Renderer();
	Shader getShaders();
	void loadTextures(const char* texPath);
};

#endif
