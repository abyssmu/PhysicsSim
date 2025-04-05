/**
* @file Scene.cpp
* @brief
* Function definitions for the Scene class. Uses the PIMPL idiom to hide
* implementation details.
*/

#include "Scene.hpp"

#include "utils/GlfwIncludes.hpp"
#include "graphics/RenderManager.hpp"
#include "graphics/WindowManager.hpp"
#include "objects/Object.hpp"

/// @brief Scene namespace
namespace Scene
{
	/// @brief Scene PIMPL implementation structure.
	struct Scene::SceneImpl
	{
		//Deleted constructors

		/// @brief Deleted default constructor.
		SceneImpl() = delete;
		/// @brief Deleted copy constructor.
		SceneImpl(const SceneImpl& other) = delete;
		/// @brief Deleted copy assignment operator.
		SceneImpl& operator=(const SceneImpl& other) = delete;
		/// @brief Deleted move constructor.
		SceneImpl(const SceneImpl&& other) = delete;
		/// @brief Deleted move assignment operator.
		SceneImpl& operator=(const SceneImpl&& other) = delete;

		//Custom constructors

		/**
		* @brief Custom constructor for the SceneImpl class.
		* @param name The name of the scene.
		* @param width The width of the scene.
		* @param height The height of the scene.
		*/
		SceneImpl(const std::string& name, const int& width, const int& height);

		//Default constructors/destructor

		/// @brief Destructor.
		~SceneImpl();

		//Member methods

		//Member variables

		/// @brief Name of the scene.
		std::string name;
		/// @brief Unique pointer to the WindowManager.
		std::unique_ptr<WindowManager> window;
		/// @brief Unique pointer to the RenderManager.
		std::unique_ptr<RenderManager> render;
	};

	/**
	* @details
	* Custom constructor for the SceneImpl class. Initializes the name, window
	* manager, and render manager.
	*/
	Scene::SceneImpl::SceneImpl(
		const std::string& name,
		const int& width,
		const int& height) :
		name(name),
		window(std::make_unique<WindowManager>(name, width, height)),
		render(std::make_unique<RenderManager>(width, height))
	{}

	/**
	* @details
	* Destructor that terminates the GLFW library.
	*/
	Scene::SceneImpl::~SceneImpl()
	{
		glfwTerminate();
	}

	/**
	* @details
	* Default constructor for the Scene class.
	*/
	Scene::Scene() = default;

	/**
	* @details
	* Default destructor for the Scene class.
	*/
	Scene::~Scene() = default;

	/**
	* @details
	* Custom constructor for the Scene class. Passes the name, width, and height
	* to the PIMPL implementation.
	*/
	Scene::Scene(const std::string& name, const int& width, const int& height) :
		_impl(std::make_unique<Scene::SceneImpl>(name, width, height))
	{}

	/**
	* @details
	* Render the texture for the ImGui render window. Passes the objects to render
	* manager for rendering.
	*/
	void Scene::RenderTexture(
		std::vector<std::shared_ptr<Object::Object>>& objects,
		const int box_height_perc,
		const int box_width_perc)
	{
		_impl->render->RenderTexture(objects, box_height_perc, box_width_perc);
	}

	/**
	* @details
	* Passes the color values to the render manager for rendering the scene.
	*/
	void Scene::Render(const float& r, const float& g, const float& b, const float& a)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		int display_w, display_h;
		glfwGetFramebufferSize(_impl->window->GetWindow(), &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);

		GLenum err = glGetError();
		//if (err != GL_NO_ERROR) DebugMessage("Scene render failed: " + std::to_string(err), __func__);
	}

	/**
	* @details
	* Get the GLSL version from the window manager.
	*/
	const char* Scene::GetGlslVersion() const
	{
		return _impl->window->GetGlslVersion();
	}

	/**
	* @details
	* Get the pointer to the window handle from the window manager.
	*/
	GLFWwindow* Scene::GetWindow() const
	{
		return _impl->window->GetWindow();
	}

	/**
	* @details
	* Get the window size as a pair of ints from the window manager.
	*/
	std::pair<int, int> Scene::GetWindowSize() const
	{
		return _impl->window->GetWindowSize();
	}

	/**
	* @details
	* Get a pointer to the texture from the render manager.
	*/
	std::shared_ptr<Texture> Scene::GetTexture() const
	{
		return _impl->render->GetTexture();
	}

	/**
	* @details
	* Get the aspect ratio of the texture from the render manager.
	*/
	float Scene::GetTextureAspectRatio() const
	{
		return _impl->render->GetTextureAspectRatio();
	}

	/**
	* @details
	* Get whether the window should close from the window manager.
	*/
	bool Scene::WindowShouldClose() const
	{
		return _impl->window->ShouldClose();
	}

	/**
	* @details
	* Swap the buffers in the window manager.
	*/
	void Scene::SwapBuffers() const
	{
		_impl->window->SwapBuffers();
	}
}