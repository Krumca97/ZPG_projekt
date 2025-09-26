#pragma once
#include <GL/glew.h>
#include <vector>

class Shape {
public:
	Shape(int jump, int positionSize, int color);
	void load_data(const std::vector<float>& new_Points);
	void draw_shape();

private:
	GLuint VAO;
	GLuint VBO;

	int jump;
	int positionSize;
	int color;

	std::vector<float> points;

	void setup_Shape();
};