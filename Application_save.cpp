#include "app.h"
#include <cstdio>
#include <cstdlib>

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include mojich knihoven
#include "vao_file.h"
#include "vbo_file.h"
#include "shader_program.h"

//trojuhelnik
float points_triangle[] = 
{
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f
};

//ctverec
float points_square[] = 
{
	-0.95f, -0.95f, 0.0f,
	-0.95f, -0.75f, 0.0f,
	-0.75f, -0.95f, 0.0f,
	-0.75f, -0.75f, 0.0f
};


//vertex shader
const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"void main () {"
"     gl_Position = vec4 (vp, 1.0);"
"}";

//fragment shader
const char* fragment_shader =
"#version 330\n"
"out vec4 fragColor;"
"void main () {"
"     fragColor = vec4 (0.5, 0.0, 0.5, 1.0);"
"}";

//fragment shader ctverec
const char* fragment_shader1 =
"#version 330\n"
"out vec4 fragColor;"
"void main () {"
"     fragColor = vec4 (1.0, 1.0, 0.0, 1.0);"
"}";

int directory = 1;

void Application::error_callback(int error, const char* description) 
{ 
	fputs(description, stderr); 
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		directory *= -1;

	}
}

void Application::window_focus_callback(GLFWwindow* window, int focused)
{ 
	printf("window_focus_callback \n"); 
}

void Application::window_iconify_callback(GLFWwindow* window, int iconified)
{ 
	printf("window_iconify_callback \n"); 
}

void Application::window_size_callback(GLFWwindow* window, int width, int height) 
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Application::cursor_callback(GLFWwindow* window, double x, double y)
{ 
	printf("cursor_callback \n"); 
}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}
Application::~Application()
{
}

int Application::Start()
{
	Application app;
	if (!app.initialization())
	{
		return -1;
	}
	app.createShaders();
	app.createBuffers();
	app.run();
	return 0;
}

bool Application::initialization()
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	return true;
}

void Application::createShaders()
{
	prog_triangle = createShaderProgram(vertex_shader, fragment_shader);
	prog_square = createShaderProgram(vertex_shader, fragment_shader1);
}

void Application::createBuffers()
{
	vboTriangle = createVBO(points_triangle, sizeof(points_triangle) / sizeof(float));
	vaoTriangle = createVAO(vboTriangle);

	vboSquare = createVBO(points_square, sizeof(points_square) / sizeof(float));
	vaoSquare = createVAO(vboSquare);
}

void Application::run()
{
	while (!glfwWindowShouldClose(window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw triangles
		glUseProgram(prog_triangle);
		glBindVertexArray(vaoTriangle);
		glDrawArrays(GL_TRIANGLES, 0, 3); //mode,first,count

		//draw rectangles
		glUseProgram(prog_square);
		glBindVertexArray(vaoSquare);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); //mode,first,count

		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);
	}
}

////GLM test
//
//// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
//glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);
//
//// Camera matrix
//glm::mat4 View = glm::lookAt(
//	glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
//	glm::vec3(0, 0, 0), // and looks at the origin
//	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
//);
//// Model matrix : an identity matrix (model will be at the origin)
//glm::mat4 Model = glm::mat4(1.0f);

