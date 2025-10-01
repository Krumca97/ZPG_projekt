#include "Model.h"

Model::Model(Shape& shape, ShaderProgram& shader_program)
	:shape(shape),shader_program(shader_program){}

void Model::draw()
{
	shader_program.set_shader();
	shape.draw_shape();
}