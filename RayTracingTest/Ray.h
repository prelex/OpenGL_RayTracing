#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Triangle.h"

struct Triangle;
class TriangleRenderer;

class Ray
{
public:
	Ray(glm::vec3 s, glm::vec3 v, Shader &sh);
	bool hitsTriangle(Triangle &triangle);
	glm::vec3 getS();
	glm::vec3 getV();
	void Render();
private:
	glm::vec3 S; // starting point
	glm::vec3 V; // direction
	GLfloat t; // parameterises distance along v
	GLuint VAO;
	Shader shader;
	bool visible;
};