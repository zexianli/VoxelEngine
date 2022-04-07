#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../shader.h"

int main() {
	std::cout << "Hello, World!" << std::endl;

	// Initialize GLFW
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW \n";
		return -1;
	}

	const int winWidth = 1080;
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

	// Create my shader object
	Shader myShader("src/shaders/vertex/vertex_core.glsl", "src/shaders/fragment/fragment_core.glsl");
	// myShader.useShader();

	// Triangle
	float positions[] = {
		// Positions		// Colors
		 0.0f,  0.5f, 0.0f,	1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	};

	unsigned int indices[] = {
		0, 1, 2
	};

	// GPU memory arrays
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
	// -Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glEnableVertexAttribArray(0);

	// -Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbinding the buffer and vertex array
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Draw in wireframe mode
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window)) {

		// Render here
		// glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Bind the VAO before draw
		myShader.useShader();
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