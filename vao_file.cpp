#include "vao_file.h"
#include <cstddef>

GLuint createVAO(GLuint VBO)
{
	GLuint VAO = 0;
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO

	glEnableVertexAttribArray(0); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//index, pocet, typ, normalized, velikost jednoho vrcholu, pocatek
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);

	glBindVertexArray(0);

	return VAO;
}