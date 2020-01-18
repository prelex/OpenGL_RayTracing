#include "Triangle.h"

Triangle::Triangle(Shader &s) : shader(s)
{
	GLuint VBO;
	GLfloat vertices[] = {
		// Position
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

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

void Triangle::Draw(glm::vec3 position, glm::vec3 size, glm::vec3 rotationAxis, GLfloat rotationAngle)
{
	shader.use();
	glm::mat4 model(1.0f);
	// Translate
	model = glm::translate(model, position);
	// Rotate
	model = glm::rotate(model, rotationAngle, rotationAxis);
	// Scale
	model = glm::scale(model, size);

	shader.setMat4("model", model);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}