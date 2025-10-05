#pragma once
#include <GL/glew.h>
#include <vector>

class Model {
public:
	Model(int jump, int positionSize, int color);
	void load_Data(const std::vector<float>& new_Points);
	void draw_Model();

private:
	GLuint VAO;
	GLuint VBO;

	int jump;
	int positionSize;
	int color;

	std::vector<float> points;

	void setup_Model();
};