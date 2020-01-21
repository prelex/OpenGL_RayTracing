#include "Ray.h"
#include <iostream>

Ray::Ray(glm::vec3 s, glm::vec3 v, Shader &sh) : S(s), V(glm::normalize(v)), t(0), VAO(), shader(sh), visible(false)
{
	GLfloat vertices[] = {
		0.0f, 0.0f, 0.0f
	};
	GLuint VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

bool Ray::hitsTriangle(Triangle &triangle)
{
	glm::vec3 N = glm::normalize(glm::cross(triangle.p1 - triangle.p0, triangle.p2 - triangle.p0));
	glm::vec4 L(N, -glm::dot(N, triangle.p0)); // L is the plane in which the triangle lies

	if (glm::dot(L, glm::vec4(V, 0)) == 0) // if L.V == 0, there is no intersection. V is a direction vector, so it has a w coordinate of 0.
		return false;
	t = -glm::dot(L, glm::vec4(S, 1)) / glm::dot(L, glm::vec4(V, 0)); // S is a position vector, so has a w coordinate of 1
	if (t < 0) // t is only allowed to be greater than or equal to zero
		return false;
	glm::vec3 p(S + t * V); // P(t) = S + tV gives the point of intersection of the ray with the plane L
	/* 
	Calculate the barycentric coordinates of P(t) with respect to the triangle vertices p0, p1, p2
	P(t) = w0*p0 + w1*p1 + w2*p2
	if w1 + w2 <= 1, then the ray intersects the triangle
	*/
	glm::vec3 R = p - triangle.p0;
	glm::vec3 Q1 = triangle.p1 - triangle.p0;
	glm::vec3 Q2 = triangle.p2 - triangle.p0;
	
	GLfloat denominator = glm::length(Q1) * glm::length(Q1) * glm::length(Q2) * glm::length(Q2) - glm::dot(Q1, Q2) * glm::dot(Q1, Q2);

	GLfloat w1 = (1 / denominator) * (glm::length(Q2)*glm::length(Q2) * glm::dot(R, Q1) - glm::dot(Q1, Q2)*glm::dot(R, Q2));
	GLfloat w2 = (1 / denominator) * (-glm::dot(Q1, Q2)*glm::dot(R, Q1) + glm::length(Q1)*glm::length(Q1)*glm::dot(R, Q2));

	if ((w1 + w2 <= 1) && w1 >= 0 && w2 >= 0)
	{
		visible = true;
		return true;
	}
	return false;
}

glm::vec3 Ray::getS()
{
	return S;
}

glm::vec3 Ray::getV()
{
	return V;
}

void Ray::Render()
{
	if (visible)
	{
		shader.use();
		glm::mat4 model(1.0f);
		// Translate
		model = glm::translate(model, S + t * V);

		shader.setMat4("model", model);

		glPointSize(5.0f);
		glBindVertexArray(VAO);
		glDrawArrays(GL_POINTS, 0, 1);
		glBindVertexArray(0);
	}
}