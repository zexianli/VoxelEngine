#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader {
public:
	// Program ID
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);
	void useShader();
	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
};

#endif