#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Shader shader_)
{
	spriteShader = shader_;

	vertices =
	{
		// position // texture coordinates
		0.0f, 1.0f, 0.0f, -1.0f,
		1.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, -1.0f,
		1.0f, 1.0f, -1.0f, -1.0f,
		1.0f, 0.0f, -1.0f, 0.0f
	};

	// Send the vertices to the GPU and configure the vertex attributes
	glGenVertexArrays(1, &spriteVAO);
	glGenBuffers(1, &spriteVBO);

	glBindBuffer(GL_ARRAY_BUFFER, spriteVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glBindVertexArray(spriteVAO);

	glEnableVertexAttribArray(position);
	glVertexAttribPointer(position, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(textureCoordinate);
	glVertexAttribPointer(textureCoordinate, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &spriteVAO);
	glDeleteBuffers(1, &spriteVBO);

	for (unsigned i = 0; i < vertices.size(); i++)
	{
		vertices[i] = NULL;
	}
}

void SpriteRenderer::DrawSprite(unsigned int texture_, vec2 position_, vec2 size_, float rotate_, vec3 color_)
{
	glUseProgram(spriteShader.shaderProgram);

	mat4 modelMatrix = mat4(1.0f);
	modelMatrix = translate(modelMatrix, vec3(position_, 0.0f));
	modelMatrix = rotate(modelMatrix, radians(rotate_), vec3(0.0, 0.0, 1.0));
	modelMatrix = scale(modelMatrix, vec3(size_, 1.0f));

	glUniformMatrix4fv(glGetUniformLocation(spriteShader.shaderProgram, "modelMatrix"), 1,
		GL_FALSE, value_ptr(modelMatrix));

	glUniform3f(glGetUniformLocation(spriteShader.shaderProgram, "spriteColor"), color_.x, color_.y, color_.z);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_);

	// Draw quad
	glBindVertexArray(spriteVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}