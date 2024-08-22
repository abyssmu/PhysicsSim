#include "Scene.h"

namespace Scene
{
	Shader::Shader(const char* vertexPath, const char* fragmentPath)
	{
		
	}
	
	void Shader::Use()
	{
		glUseProgram(_id);
	}

	void Shader::SetBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value);
	}

	void Shader::SetInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
	}

	void Shader::SetFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
	}

	void Shader::CheckCompileErrors(unsigned int shader, std::string type)
	{
		int success;
		char infoLog[1024];

		if (type != "PROGRAM") glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		else glGetProgramiv(shader, GL_LINK_STATUS, &success);
	}


	
	Scene::~Scene()
	{
		glfwDestroyWindow(_window);

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteProgram(shaderProgram);
		glDeleteFramebuffers(1, &framebuffer);
		glDeleteTextures(1, &texture);

		glfwTerminate();

		//if (_shader) delete _shader;
		_window = nullptr;
		_glsl_version = nullptr;
	}

	Scene::Scene(const int& width, const int& height, const string& name) :
		_width(width), _height(height), _name(name), _tex_width(width), _tex_height(height)
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

		//_shader = new Shader("src/vertex_shader.vs", "src/fragment_shader.fs");

		SetupBufferData();

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		SetupFramebufferAndTexture(_tex_width, _tex_height);
	}

	void Scene::RenderTexture(const int& width, const int& height)
	{
		if (width != _tex_width || height != _tex_height) SetupFramebufferAndTexture(width, height);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glViewport(0, 0, _tex_width, _tex_height);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
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
		return texture;
	}

	void Scene::SetupGLFW()
	{
		glfwSetErrorCallback(GLFWErrorCallback);
		if (!glfwInit())
		{
			glfwTerminate();
			return;
		}

		// GL 3.0 + GLSL 130
		_glsl_version = "#version 130";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		_window = glfwCreateWindow(_width, _height, _name.c_str(), nullptr, nullptr);
	}

	void Scene::SetupBufferData()
	{
		// Create triangle VAO/VBO
		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	void Scene::SetupFramebufferAndTexture(const int& width, const int& height)
	{
		glDeleteFramebuffers(1, &framebuffer);
		glDeleteTextures(1, &texture); 
		
		glGenFramebuffers(1, &framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}