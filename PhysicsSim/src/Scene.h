// Shader and scene classes draw somewhat heavily from the Learn OpenGL tutorial
// https://learnopengl.com/Getting-started/OpenGL

#pragma once

#ifndef _SCENE_
#define _SCENE_

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace Scene
{
	class Shader
	{
	public:
		Shader() = delete;
		Shader(const char* vertexPath, const char* fragmentPath);

		void Use();
		void SetBool(const std::string& name, bool value) const;
		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float value) const;

	public:
		unsigned int _id;

	private:
		void CheckCompileErrors(unsigned int shader, std::string type);
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
		int _tex_width;
		int _tex_height;

	private:
		void SetupGLFW();
		void SetupBufferData();
		void SetupFramebufferAndTexture(const int& width, const int& height);

	private:
		const char* _glsl_version = nullptr;
		GLFWwindow* _window = nullptr;
		string _name;
		GLuint VBO = 0;
		GLuint VAO = 0;
		//Shader* _shader;

		GLuint framebuffer;
		GLuint texture;
		GLuint shaderProgram;
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