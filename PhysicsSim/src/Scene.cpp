#include "Scene.h"

namespace Scene
{
	Scene::~Scene()
	{
		glfwDestroyWindow(_window);

		glDeleteVertexArrays(1, &_vertex_array);
		glDeleteBuffers(1, &_vertex_buffer);
		glDeleteProgram(_shader);

		glfwTerminate();

		_window = nullptr;
		_glsl_version = nullptr;
	}

	Scene::Scene(const int& width, const int& height, const string& name) :
		_width(width), _height(height), _name(name)
	{
		SetupGLFW();
		if (_window == nullptr) return;

		glfwMakeContextCurrent(_window);
		glfwSetFramebufferSizeCallback(_window, GLFWFramebufferSizeCallback);
		glfwSetErrorCallback(GLFWErrorCallback);
		glfwSwapInterval(1);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			return;
		}

		SetupBufferData();

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		_shader = glCreateProgram();
		glAttachShader(_shader, vertexShader);
		glAttachShader(_shader, fragmentShader);
		glLinkProgram(_shader);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		_texture = make_unique<Texture>(width, height);
	}

	void Scene::RenderTexture(const int& width, const int& height)
	{
		_texture->Render(width, height, _shader, _vertex_array);
	}

	void Scene::DrawScene(const float& r, const float& g, const float& b, const float& a)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		int display_w, display_h;
		glfwGetFramebufferSize(_window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	const char* Scene::GetGlslVersion()
	{
		return _glsl_version;
	}

	GLFWwindow* Scene::GetWindow()
	{
		return _window;
	}

	void Scene::CheckForWindowResize()
	{
		int width = 0, height = 0;
		glfwGetWindowSize(_window, &width, &height);

		if (width != _width || height != _height)
		{
			_width = width;
			_height = height;
		}
	}

	GLuint& Scene::GetTexture()
	{
		return _texture->GetTexture();
	}

	void Scene::SetupGLFW()
	{
		glfwSetErrorCallback(GLFWErrorCallback);
		if (!glfwInit())
		{
			glfwTerminate();
			return;
		}

		_glsl_version = "#version 130";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		_window = glfwCreateWindow(_width, _height, _name.c_str(), nullptr, nullptr);
	}

	void Scene::SetupBufferData()
	{
		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		glGenVertexArrays(1, &_vertex_array);
		glGenBuffers(1, &_vertex_buffer);
		glBindVertexArray(_vertex_array);
		glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}
}