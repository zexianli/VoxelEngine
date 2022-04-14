#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "core/shader.h"
#include "core/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "render/renderer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Vectors for camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// Camera free look
bool firstFocus = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 1080.0f / 2;
float lastY = 720.0f / 2;


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
	// Resize viewport if window size changes
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// Tell OpenGL to capture mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Call everytime the mouse moves
	glfwSetCursorPosCallback(window, mouse_callback);


	// Initialize Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize Glad \n";
		return -1;
	}

	// Create my shader object
	/*Shader myShader("src/shaders/vertex/vertex_core.glsl", "src/shaders/fragment/fragment_core.glsl");*/
	Renderer render;

	float textureCoords[] = {
		0.0f, 0.0f,

	};

	// The texture image is 256 * 256
	// Should start at 0, but texture image is janky
	float positions[] = {
		// Front
		-0.5f, -0.5f, -0.5f,  49.0f / 256.0f, 241.0f / 256.0f, // 0
		0.5f, -0.5f, -0.5f,  64.0f / 256.0f, 241.0f / 256.0f, // 1
		0.5f,  0.5f, -0.5f,  64.0f / 256.0f, 256.0f / 256.0f, // 2
		0.5f,  0.5f, -0.5f,  64.0f / 256.0f, 256.0f / 256.0f, // 3
		-0.5f,  0.5f, -0.5f,  49.0f / 256.0f, 256.0f / 256.0f, // 4
		-0.5f, -0.5f, -0.5f,  49.0f / 256.0f, 241.0f / 256.0f, // 5

		// Back
		-0.5f, -0.5f,  0.5f,  49.0f / 256.0f, 241.0f / 256.0f, // 0
		0.5f, -0.5f,  0.5f,  64.0f / 256.0f, 241.0f / 256.0f, // 1
		0.5f,  0.5f,  0.5f,  64.0f / 256.0f, 256.0f / 256.0f, // 2
		0.5f,  0.5f,  0.5f,  64.0f / 256.0f, 256.0f / 256.0f, // 3
		-0.5f,  0.5f,  0.5f,  49.0f / 256.0f, 256.0f / 256.0f, // 4
		-0.5f, -0.5f,  0.5f,  49.0f / 256.0f, 241.0f / 256.0f, // 5

		// Left
		-0.5f, -0.5f,  0.5f,  49.0f / 256.0f, 241.0f / 256.0f, // 0
		-0.5f, -0.5f, -0.5f,  64.0f / 256.0f, 241.0f / 256.0f, // 1
		-0.5f,  0.5f, -0.5f,  64.0f / 256.0f, 256.0f / 256.0f, // 2
		-0.5f,  0.5f, -0.5f,  64.0f / 256.0f, 256.0f / 256.0f, // 3
		-0.5f,  0.5f,  0.5f,  49.0f / 256.0f, 256.0f / 256.0f, // 4
		-0.5f, -0.5f,  0.5f,  49.0f / 256.0f, 241.0f / 256.0f, // 5

		// Right side
		0.5f, -0.5f,  0.5f,  49.0f / 256.0f, 241.0f / 256.0f, // 0
		0.5f, -0.5f, -0.5f,  64.0f / 256.0f, 241.0f / 256.0f, // 1
		0.5f,  0.5f, -0.5f,  64.0f / 256.0f, 256.0f / 256.0f, // 2
		0.5f,  0.5f, -0.5f,  64.0f / 256.0f, 256.0f / 256.0f, // 3
		0.5f,  0.5f,  0.5f,  49.0f / 256.0f, 256.0f / 256.0f, // 4
		0.5f, -0.5f,  0.5f,  49.0f / 256.0f, 241.0f / 256.0f, // 5

		 // Bottom
		 -0.5f, -0.5f, -0.5f,  33.0f / 256.0f, 241.0f / 256.0f, // 0
		  0.5f, -0.5f, -0.5f,  48.0f / 256.0f, 241.0f / 256.0f, // 1
		  0.5f, -0.5f,  0.5f,  48.0f / 256.0f, 256.0f / 256.0f, // 2
		  0.5f, -0.5f,  0.5f,  48.0f / 256.0f, 256.0f / 256.0f, // 3
		 -0.5f, -0.5f,  0.5f,  33.0f / 256.0f, 256.0f / 256.0f, // 4
		 -0.5f, -0.5f, -0.5f,  33.0f / 256.0f, 241.0f / 256.0f, // 5

		 // Top
		 -0.5f,  0.5f, -0.5f,  0.0f / 256.0f, 241.0f / 256.0f, // 0
		  0.5f,  0.5f, -0.5f,  16.0f / 256.0f, 241.0f / 256.0f, // 1
		  0.5f,  0.5f,  0.5f,  16.0f / 256.0f, 256.0f / 256.0f, // 2
		  0.5f,  0.5f,  0.5f,  16.0f / 256.0f, 256.0f / 256.0f, // 3
		 -0.5f,  0.5f,  0.5f,  0.0f / 256.0f, 256.0f / 256.0f, // 4
		 -0.5f,  0.5f, -0.5f,  0.0f / 256.0f, 241.0f / 256.0f, // 5
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glEnableVertexAttribArray(0);

	// -Texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Textures
	// Texture 1
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

	// Unbinding the buffer and vertex array
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Draw in wireframe mode
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	render.getShaders().useShader();
	render.getShaders().setInt("texture1", 0);

	// Enable depth testing. Z/Depth buffer is created by glfw
	glEnable(GL_DEPTH_TEST);

	const float cameraSpeed = 0.05f;

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window)) {
		// Render logic
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		// Render here
		// Clear depth buffer otherwise it will have old depth information
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Bind texture to texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);


		// ---------
		// Going 3D
		// ---------
		glm::mat4 viewMatrix;
		viewMatrix = glm::lookAt(
			cameraPos,
			cameraPos + cameraFront,
			cameraUp
		);

		// Projection matrix to add perspective
		// Also needs to take care of aspect ration,
		// in case the window size is changed
		glm::mat4 projectionMatrix;
		int newWidth, newHeight;
		glfwGetFramebufferSize(window, &newWidth, &newHeight);
		projectionMatrix = glm::perspective(glm::radians(47.0f), static_cast<float>(newWidth) / static_cast<float>(newHeight), 0.1f, 100.0f);

		render.getShaders().setMat4("view", viewMatrix);
		render.getShaders().setMat4("projection", projectionMatrix);

		// Bind the VAO before draw
		glBindVertexArray(VAO);
		// Draw using the indices to point back to positions
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		for (size_t i = 0; i < 16; i++) {
			for (size_t j = 0; j < 16; j++) {
				for (size_t k = 0; k < 60; k++) {
					glm::mat4 modelMatrix = glm::mat4(1.0f);
					modelMatrix = glm::translate(modelMatrix, glm::vec3(static_cast<float>(i), static_cast<float>(k), static_cast<float>(j)));
					modelMatrix = glm::rotate(modelMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
					// Pass in the cube to draw
					render.getShaders().setMat4("model", modelMatrix);
					glDrawArrays(GL_TRIANGLES, 0, 36);
				}
			}
		}


		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	float cameraSpeed = static_cast<float>(2.5f * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
	float xPos = static_cast<float>(xposIn);
	float yPos = static_cast<float>(yposIn);

	// Prevent mouse jump when focusing on app the first time
	if (firstFocus) {
		lastX = xPos;
		lastY = yPos;
		firstFocus = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos; // reversed since y axis starts at bottom
	lastX = xPos;
	lastY = yPos;

	float sensitivity = 0.1f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	// Limit y axis camera movement;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}