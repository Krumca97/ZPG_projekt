#pragma once
#include <GL/glew.h>
#include <vector>

class Model {
public:
	Model(int jump, int positionSize, int color);
	void loadData(const std::vector<float>& newPoints);
	void drawModel();

private:
	GLuint VAO;
	GLuint VBO;

	int jump;
	int positionSize;
	int color;

	std::vector<float> points;

	void setupModel();
};