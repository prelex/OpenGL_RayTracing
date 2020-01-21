#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include <stb-master/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Triangle.h"
#include "Ray.h"

void processInput(GLFWwindow* window);

// Callback functions. Called whenever the user changes the window size, uses the mouse, or uses the scroll wheel
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

const unsigned int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;

// Used to make camera speed independent of framerate
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Used to smooth initial mouse input
float lastX = SCREEN_WIDTH / 2.0f, lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;

// set up the camera
Camera camera(glm::vec3(0.0f, 0.0f, 20.0f));

int main()
{
	// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw: create window
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Ray Tracing", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	Shader triangleShader("shaders/triangle_vs.txt", "shaders/triangle_fs.txt");
	Shader rayShader("shaders/ray_vs.txt", "shaders/ray_fs.txt");

	TriangleRenderer triangle(triangleShader);

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		glm::mat4 view = camera.getViewMatrix();
		glm::mat4 projection = glm::perspective(camera.Zoom, static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT), 0.1f, 100.0f);

		triangleShader.use();
		triangleShader.setMat4("view", view);
		triangleShader.setMat4("projection", projection);
		rayShader.use();
		rayShader.setMat4("view", view);
		rayShader.setMat4("projection", projection);

		Ray ray(camera.Position, camera.Front, rayShader);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		// clear the color buffer and depth buffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// render
		triangle.Render(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, &ray);
		ray.Render();
		
		// swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = static_cast<float>(xpos);
		lastY = static_cast<float>(ypos);
		firstMouse = false;
	}

	float xoffset = static_cast<float>(xpos) - lastX;
	float yoffset = lastY - static_cast<float>(ypos);
	lastX = static_cast<float>(xpos);
	lastY = static_cast<float>(ypos);

	camera.ProcessMouseMovement(xoffset, yoffset);
}