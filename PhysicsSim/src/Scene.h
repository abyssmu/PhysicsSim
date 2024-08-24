// Shader and scene classes draw somewhat heavily from the Learn OpenGL tutorial
// https://learnopengl.com/Getting-started/OpenGL

#pragma once

#ifndef _SCENE_
#define _SCENE_

#define GL_SILENCE_DEPRECATION
#ifdef IMGUI_IMPL_OPENGL_ES2
#include <GLES2/gl2.h>
#endif
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;

namespace Scene
{
	class Texture
	{
	public:
		Texture() = delete;
		~Texture();
		Texture(const int& width, const int& height);

		GLuint& GetTexture();
		void Render(const int& width, const int& height, GLuint& shader, GLuint& vert_array);

	private:
		void SetupFramebufferAndTexture(const int& width, const int& height);

	private:
		int _width;
		int _height;
		GLuint _frame_buffer;
		GLuint _texture;
	};

	class Scene
	{
	public:
		Scene() = delete;
		Scene(const Scene& other) = delete;
		~Scene();
		Scene(const int& width, const int& height, const string& name);

		void RenderTexture(const int& width, const int& height);
		void DrawScene(const float& r, const float& g, const float& b, const float& a);
		const char* GetGlslVersion();
		GLFWwindow* GetWindow();
		void CheckForWindowResize();
		GLuint& GetTexture();

	public:
		int _width;
		int _height;

	private:
		void SetupGLFW();
		void SetupBufferData();

	private:
		const char* _glsl_version = nullptr;
		GLFWwindow* _window = nullptr;
		string _name;
		unique_ptr<Texture> _texture;
		GLuint _vertex_buffer = 0;
		GLuint _vertex_array = 0;

		GLuint _shader;
		const char* vertexShaderSource = R"(
			#version 330 core
			layout (location = 0) in vec3 aPos;
			void main() {
				gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
			}
		)";

		const char* fragmentShaderSource = R"(
			#version 330 core
			out vec4 FragColor;
			void main() {
				FragColor = vec4(0.0, 1.0, 0.0, 1.0); // Green color
			}
		)";
	};

	static void GLFWFramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	static void GLFWErrorCallback(int error, const char* description)
	{
		fprintf(stderr, "GLFW Error %d: %s\n", error, description);
	}
}

#endif