#include "Scene.h"

#include "utils/GlfwAndDebugIncludes.h"
#include "graphics/RenderManager.h"
#include "graphics/WindowManager.h"
#include "objects/Object.h"

namespace Scene
{
	struct Scene::SceneImpl
	{
		//Deleted constructors
		SceneImpl() = delete;
		SceneImpl(const SceneImpl& other) = delete;
		SceneImpl& operator=(const SceneImpl& other) = delete;
		SceneImpl(const SceneImpl&& other) = delete;
		SceneImpl& operator=(const SceneImpl&& other) = delete;

		//Custom constructors
		SceneImpl(const std::string& name, const int& width, const int& height);

		//Default constructors/destructor
		~SceneImpl();

		//Member methods

		//Member variables
		std::string name;
		std::unique_ptr<WindowManager> window;
		std::unique_ptr<RenderManager> render;
	};

	Scene::SceneImpl::SceneImpl(
		const std::string& name,
		const int& width,
		const int& height) :
		name(name),
		window(std::make_unique<WindowManager>(name, width, height)),
		render(std::make_unique<RenderManager>(width, height))
	{}

	Scene::SceneImpl::~SceneImpl()
	{
		glfwTerminate();
	}

	Scene::Scene() = default;
	Scene::~Scene() = default;

	Scene::Scene(const std::string& name, const int& width, const int& height) :
		_impl(std::make_unique<Scene::SceneImpl>(name, width, height))
	{}

	void Scene::RenderTexture(
		std::vector<std::shared_ptr<Object::Object>>& objects,
		const int box_height_perc,
		const int box_width_perc)
	{
		_impl->render->RenderTexture(objects, box_height_perc, box_width_perc);
	}

	void Scene::Render(const float& r, const float& g, const float& b, const float& a)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		int display_w, display_h;
		glfwGetFramebufferSize(_impl->window->GetWindow(), &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);

		GLenum err = glGetError();
		if (err != GL_NO_ERROR) DebugMessage("Scene render failed: " + std::to_string(err), __func__);
	}

	const char* Scene::GetGlslVersion() const
	{
		return _impl->window->GetGlslVersion();
	}

	GLFWwindow* Scene::GetWindow() const
	{
		return _impl->window->GetWindow();
	}

	std::pair<int, int> Scene::GetWindowSize() const
	{
		return _impl->window->GetWindowSize();
	}

	std::shared_ptr<Texture> Scene::GetTexture() const
	{
		return _impl->render->GetTexture();
	}

	float Scene::GetTextureAspectRatio() const
	{
		return _impl->render->GetTextureAspectRatio();
	}

	bool Scene::WindowShouldClose() const
	{
		return _impl->window->ShouldClose();
	}

	void Scene::SwapBuffers() const
	{
		_impl->window->SwapBuffers();
	}
}