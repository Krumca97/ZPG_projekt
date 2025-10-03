#include "Application.h"
#include "Model.h"
#include "Shape.h"
#include "Shader_program.h"
#include "Models/bushes.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

	-0.75f, -0.95f, 0.0f,
	-0.95f, -0.75f, 0.0f,
	-0.75f, -0.75f, 0.0f
};

//krychle
float points_rectangle[] =
{
	0.0f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  
	-0.5f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
	0.5f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,

	-0.5f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
	0.5f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
	0.0f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f
};


//vertex shader
const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"void main () {"
"     gl_Position = vec4 (vp, 1.0);"
"}";

//vertex shader obdelnik
const char* vertex_shader_rectangle =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 vc;"
"out vec3 color;"
"void main () {"
"     gl_Position = vec4 (vp, 1.0);"
"	  color = vc;"
"}";

//vertex shader bush
const char* vertex_shader_bush =
"#version 330\n"
"layout(location = 0) in vec3 aPos;"
"layout(location = 1) in vec3 aNormal;"
"uniform mat4 u_MVP;"
"uniform mat4 u_Model;"
"out vec3 Normal;"
"out vec3 FragPos;"
"void main() {"
"    FragPos = vec3(u_Model * vec4(aPos, 1.0));"
"    Normal = mat3(transpose(inverse(u_Model))) * aNormal;"
"    gl_Position = u_MVP * vec4(aPos, 1.0);"
"}";

//tocici ctverec
const char* vertex_shader_rectangle_rotate =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 vc;"
"out vec3 color;"
"uniform mat4 u_MVP;"
"void main () {"
"     gl_Position = u_MVP * vec4(vp, 1.0);"
"     color = vc;"
"}";

//fragment shader trojuhelnik
const char* fragment_shader_triangle =
"#version 330\n"
"out vec4 fragColor;"
"void main () {"
"     fragColor = vec4 (0.5, 0.0, 0.5, 1.0);"
"}";

//fragment shader ctverec
const char* fragment_shader_square =
"#version 330\n"
"out vec4 fragColor;"
"void main () {"
"     fragColor = vec4 (1.0, 1.0, 0.0, 1.0);"
"}";

//fragment shader obdelnik
const char* fragment_shader_rectangle =
"#version 330\n"
"in vec3 color;\n"
"out vec4 fragColor;\n"
"void main() {\n"
"    fragColor = vec4(color, 1.0);\n"
"}";

//fragment shader bush
const char* fragment_shader_bush =
"#version 330\n"
"in vec3 Normal;"
"in vec3 FragPos;"
"out vec4 FragColor;"
"const vec3 lightDir = vec3(-0.5, -1.0, -0.3);"
"void main() {"
"    float diff = max(dot(normalize(Normal), -lightDir), 0.0);"
"    vec3 color = vec3(0.2, 0.8, 0.2) * diff;"
"    FragColor = vec4(color, 1.0);"
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
	shaderTriangle = new ShaderProgram(vertex_shader, fragment_shader_triangle);
	shaderSquare = new ShaderProgram(vertex_shader, fragment_shader_square);
	shaderRectangle = new ShaderProgram(vertex_shader_rectangle_rotate, fragment_shader_rectangle);
	shaderBush = new ShaderProgram(vertex_shader_bush,fragment_shader_bush);
}

void Application::createBuffers()
{
	shapeTriangle = new Shape(3, 3, 0);
	std::vector<float>triangle(points_triangle, points_triangle + sizeof(points_triangle) / sizeof(float));
	shapeTriangle->load_data(triangle);

	shapeSquare = new Shape(3, 3, 0);
	std::vector<float>square(points_square, points_square + sizeof(points_square) / sizeof(float));
	shapeSquare->load_data(square);

	shapeRectangle = new Shape(6, 3, 3);
	std::vector<float>rectangle(points_rectangle, points_rectangle + sizeof(points_rectangle) / sizeof(float));
	shapeRectangle->load_data(rectangle);

	//bushes
	shapeBush = new Shape(6,3,3);
	std::vector<float>bush(bushes,bushes + sizeof(bushes)/sizeof(float));
	shapeBush->load_data(bush);


	modelTriangle = new Model(*shapeTriangle, *shaderTriangle);
	modelSquare = new Model(*shapeSquare, *shaderSquare);
	modelRectangle = new Model(*shapeRectangle, *shaderRectangle);
	modelBush = new Model(*shapeBush,*shaderBush);
}

float angle= 0.0f;

void Application::run()
{
	while (!glfwWindowShouldClose(window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// // draw triangle
		// modelTriangle->draw();

		// //draw square
		// modelSquare->draw();

		//draw rectangle
		angle += 0.1f; 

		glm::mat4 model = glm::mat4(1.0f);  
		model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f)); 
		glm::mat4 view = glm::mat4(1.0f);   
		glm::mat4 proj = glm::mat4(1.0f);   
		glm::mat4 mvp = proj * view * model;

		shaderRectangle->set_shader();
		shaderRectangle->setMat4("u_MVP", mvp);
		modelRectangle->draw();

		// //draw bush
		// shaderBush->set_shader();
		// shaderBush->setMat4("u_Model", glm::mat4(1.0f));
		// shaderBush->setMat4("u_MVP", glm::mat4(1.0f));
		// shaderBush->setVec3("lightDir", glm::vec3(-0.5f, -1.0f, -0.3f));
		// modelBush->draw();

		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);
	}
}


