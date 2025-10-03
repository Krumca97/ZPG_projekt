#pragma once
#include <GL/glew.h>
#include "Shape.h"
#include "Shader_program.h"

class Model
{
public:
	Model(Shape& shape, ShaderProgram& shader_program);

	void draw();

private:
	Shape& shape;
	ShaderProgram& shader_program;

};
