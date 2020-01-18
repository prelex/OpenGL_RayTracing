#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Triangle.h"

class Ray
{
public:
	Ray(glm::vec3 s, glm::vec3 v);
	bool hitsTriangle(Triangle &t);
private:
	glm::vec3 S; // starting point
	glm::vec3 V; // direction
	GLfloat t; // parameterises distance along v
};