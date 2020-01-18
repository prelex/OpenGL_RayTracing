#pragma once
#include <glad/glad.h>
#include "Shader.h"

class Triangle
{
public:
	Triangle(Shader &s);
	void Draw(glm::vec3 position, glm::vec3 size, glm::vec3 rotationAxis, GLfloat rotationAngle);
private:
	GLuint VAO;
	Shader shader;
};