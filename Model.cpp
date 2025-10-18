#include "Model.h"

Model::Model(int jump, int positionSize, int color)
{
	this->jump = jump;
	this->positionSize = positionSize;
	this->color = color;
	this->VAO = 0;
	this->VBO = 0;
}

void Model::loadData(const std::vector<float>& points)
{
	this->points = points;
	setupModel();
}

void Model::setupModel()
{
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO

	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);
	
	//pozice
	//index, pocet, typ, normalized, velikost jednoho vrcholu, pocatek
	glVertexAttribPointer(0, positionSize, GL_FLOAT, GL_FALSE, jump * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	//barva
	if (color)
	{
		glVertexAttribPointer(1, color, GL_FLOAT, GL_FALSE, jump * sizeof(float), (void*)(positionSize * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBindVertexArray(0);
}

void Model::drawModel()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, points.size() / jump);
	glBindVertexArray(0);
}