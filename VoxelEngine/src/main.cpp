#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core \n"
"layout (location = 0) in vec3 aPos; \n"
"void main() { \n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
"} \0";

const char* fragmentShaderSource = "#version 330 core \n"
"out vec4 FragColor; \n"
"void main() { \n"
"   FragColor = vec4(0.5f, 1.0f, 0.5f, 1.0f); \n"
"} \0";

int main() {
	std::cout << "Hello, World!" << std::endl;

	// Initialize GLFW
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW \n";
		return -1;
	}

	const int winWidth = 1280;
	const int winHeight = 720;
	const char* winTitle = "Voxel Engine";

	// Create a windowed mode window and its OpenGL context
	GLFWwindow* window = glfwCreateWindow(
		winWidth,
		winHeight,
		winTitle,
		NULL,
		NULL
	);

	if (!window)
	{
		std::cout << "Failed to create window \n";
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Initialize Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize Glad \n";
		return -1;
	}

	glViewport(0, 0, winWidth, winHeight);


	// ----------------------------------
	// Declaring vertex shader glsl
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Vertex shader compilation
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER VERTEX COMPILATION FAILED\n" << infoLog << std::endl;
	}

	// Declaring fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Fragment shader compilation
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::FRAGMENT VERTEX COMPILATION FAILED\n" << infoLog << std::endl;
	}

	// Linking shader programs
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER PROGRAM LINKING FAILED\n" << infoLog << std::endl;
	}

	// Clean up
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// ----------------------------------

	// Triangle
	/*float positions[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};*/

	// Square
	float positions[] = {
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	// VBO
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// First bind the VAO before modifying the VBO
	glBindVertexArray(VAO);

	// Copy data into OpenGL array buffer using VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	// Copy data into OpenGL element array buffer using EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Set vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
	glEnableVertexAttribArray(0);

	// Unbinding the buffer and vertex array
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window)) {

		// Render here
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Bind the VAO before draw
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		// Draw using the indices to point back to positions
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}