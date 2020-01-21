#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Ray.h"

struct Triangle
{
	glm::vec3 p0, p1, p2;
};

class TriangleRenderer
{
	friend class Ray;
public:
	TriangleRenderer(Shader &s);
	void Render(glm::vec3 position, glm::vec2 size, glm::vec3 rotAxis, GLfloat rotAngle, Ray* ray = nullptr);
private:
	Shader shader;
	GLuint VAO;
	Triangle triangle;
};