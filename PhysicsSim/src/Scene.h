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

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <fstream>
#include <sstream>
#include <memory>
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::ifstream;
using std::stringstream;

namespace Scene
{
	class WindowManager
	{
	public:
		WindowManager() = delete;
		WindowManager(const WindowManager& other) = delete;
		WindowManager& operator=(const WindowManager& other) = delete;
		WindowManager(WindowManager&& other) = delete;
		WindowManager& operator=(const WindowManager&& other) = delete;

		WindowManager(const string& name, const int& width, const int& height);

		~WindowManager() = default;

		void Terminate();
		GLFWwindow* GetWindow() const;
		const char* GetGlslVersion() const;
		bool ShouldClose() const;
		void SwapBuffers();

	private:
		string _name;
		const char* _glsl_version = nullptr;
		GLFWwindow* _window = nullptr;
		int _width;
		int _height;
	};

	class Shader
	{
	public:
		Shader() = delete;
		Shader(const Shader& other) = delete;
		~Shader();
		Shader(const string& vs_file, const string& fs_file);

		void Terminate();
		GLuint& GetShader();

	private:
		void CheckCompileErrors(unsigned int shader, std::string type) const;

	private:
		GLuint _shader;
	};

	class Texture
	{
	public:
		Texture() = delete;
		~Texture();
		Texture(const int& width, const int& height);

		void Terminate();
		GLuint& GetTexture();
		void Render(GLuint& shader, GLuint& vert_array);
		void SetupFramebufferAndTexture(const int& width, const int& height);
		float GetAspectRatio() const;

	private:
		int _width;
		int _height;
		GLuint _frame_buffer;
		GLuint _texture;
	};

	class RenderManager
	{
	public:
		RenderManager() = delete;
		RenderManager(const RenderManager& other) = delete;
		RenderManager& operator=(const RenderManager& other) = delete;
		RenderManager(RenderManager&& other) = delete;
		RenderManager& operator=(const RenderManager&& other) = delete;

		RenderManager(const int& width, const int& height);

		~RenderManager() = default;

		void Terminate();
		void RenderTexture();
		void ResizeTexture(const int& width, const int& height);
		GLuint& GetTexture();
		float GetTextureAspectRatio() const;

	private:
		unique_ptr<Texture> _texture;
		unique_ptr<Shader> _shader;
		GLuint _vertex_buffer = 0;
		GLuint _vertex_array = 0;
	};

	class Scene
	{
	public:
		Scene() = delete;
		Scene(const Scene& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene&& other) = delete;

		Scene(const string& name, const int& width, const int& height);

		~Scene() = default;

		void Terminate();
		void RenderTexture();
		void Render(const float& r, const float& g, const float& b, const float& a);
		const char* GetGlslVersion() const;
		GLFWwindow* GetWindow() const;
		GLuint& GetTexture() const;
		void ResizeTexture(const int& width, const int& height);
		float GetTextureAspectRatio() const;
		bool WindowShouldClose() const;
		void SwapBuffers() const;

	private:
		string _name;
		unique_ptr<WindowManager> _window;
		unique_ptr<RenderManager> _render;
	};

	static void GLFWFramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	};

	static void GLFWErrorCallback(int error, const char* description)
	{
		fprintf(stderr, "GLFW Error %d: %s\n", error, description);
	};
}

#endif