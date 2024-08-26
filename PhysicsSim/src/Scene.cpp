#include "Scene.h"

namespace Scene
{
	Scene::Scene(const string& name, const int& width, const int& height) : _name(name)
	{
		_window = make_unique<WindowManager>(name, width, height);
		_render = make_unique<RenderManager>(width, height);
	}

	void Scene::Terminate()
	{
		_render->Terminate();
		_window->Terminate();
		glfwTerminate();
	}

	void Scene::RenderTexture()
	{
		_render->RenderTexture();
	}

	void Scene::Render(const float& r, const float& g, const float& b, const float& a)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		int display_w, display_h;
		glfwGetFramebufferSize(_window->GetWindow(), &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	const char* Scene::GetGlslVersion() const
	{
		return _window->GetGlslVersion();
	}

	GLFWwindow* Scene::GetWindow() const
	{
		return _window->GetWindow();
	}

	GLuint& Scene::GetTexture() const
	{
		return _render->GetTexture();
	}

	void Scene::ResizeTexture(const int& width, const int& height)
	{
		_render->ResizeTexture(width, height);
	}

	float Scene::GetTextureAspectRatio() const
	{
		return _render->GetTextureAspectRatio();
	}

	bool Scene::WindowShouldClose() const
	{
		return _window->ShouldClose();
	}

	void Scene::SwapBuffers() const
	{
		_window->SwapBuffers();
	}
}