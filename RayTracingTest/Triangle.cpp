#include "Triangle.h"
#include <iostream>

TriangleRenderer::TriangleRenderer(Shader &s) : shader(s), VAO()
{
	GLuint VBO;
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	triangle.p0 = glm::vec3(vertices[0], vertices[1], vertices[2]);
	triangle.p1 = glm::vec3(vertices[3], vertices[4], vertices[5]);
	triangle.p2 = glm::vec3(vertices[6], vertices[7], vertices[8]);
	
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

void TriangleRenderer::Render(glm::vec3 position, glm::vec2 size, glm::vec3 rotAxis, GLfloat rotAngle, Ray* ray)
{
	shader.use();
	glm::mat4 model(1.0f);
	// Translate
	model = glm::translate(model, position);
	// Rotate
	model = glm::rotate(model, rotAngle, rotAxis);
	// Scale
	model = glm::scale(model, glm::vec3(size, 1.0f));

	shader.setMat4("model", model);

	glm::vec3 triangleColour(0.0f, 0.5f, 0.0f);
	if (ray != nullptr)
	{
		glm::vec3 newp0 = glm::vec3(model * glm::vec4(triangle.p0, 1.0f));
		glm::vec3 newp1 = glm::vec3(model * glm::vec4(triangle.p1, 1.0f));
		glm::vec3 newp2 = glm::vec3(model * glm::vec4(triangle.p2, 1.0f));
		Triangle tempTriangle = { newp0, newp1, newp2 };
		if (ray->hitsTriangle(tempTriangle))
		{
			triangleColour.y *= 2.0f;
		}
	}

	shader.setVec3("colour", triangleColour);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}