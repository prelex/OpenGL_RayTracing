#pragma once
#include <glad/glad.h>
#include "Shader.h"
#include "Triangle.h"
#include "Ray.h"

class Renderer
{
public:
	Renderer(Shader &s);
	void DrawTriangle(glm::vec3 pos, glm::vec2 size, glm::vec3 rotationAxis, GLfloat rotationAngle, Ray* ray = nullptr);
private:
	Shader shader;
	GLuint VAO;
};