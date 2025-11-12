#pragma once
#include <GL/glew.h>
#include <vector>
#include <iostream>

class Model {
public:
	Model(int jump, int positionSize, int normal);
	Model(const char* name);
	void loadData(const std::vector<float>& newPoints);
	void drawModel();

private:
	GLuint VAO;
	GLuint VBO;

	int jump;
	int positionSize;
	int normal;

	std::vector<float> points;

	void setupModel();
};