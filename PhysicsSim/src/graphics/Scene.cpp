/**
* @file Scene.cpp
* @brief
* Function definitions for the Scene class. Uses the PIMPL idiom to hide
* implementation details.
*/

#include "Scene.hpp"
#include "SimulationRenderItems.hpp"
#include "ThermodynamicsRenderItems.hpp"

#include "utils/GlfwIncludes.hpp"
#include "graphics/Shader.hpp"
#include "graphics/Texture.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "spdlog/spdlog.h"

/// @brief Scene namespace
namespace Graphics
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
		* @param bg_color The background color of the scene.
		*/
		SceneImpl(
			const std::string& name,
			const int& width,
			const int& height,
			const float* bg_color);

		//Default constructors/destructor

		/// @brief Destructor.
		~SceneImpl();

		//Member methods

		/// @brief Apply the background color (clear color) to the window.
		void ApplyClearColor() const;

		/**
		* @brief Callback function for GLFW error handling.
		* @param error The error code.
		* @param description The error description.
		*/
		static void GLFWErrorCallback(int error, const char* description);

		/**
		* @brief Set the window size in OpenGL.
		* @param window The window handle.
		* @param width The width of the window.
		* @param height The height of the window.
		*/
		static void GLFWFramebufferSizeCallback(
			GLFWwindow* window,
			int width,
			int height);

		///@brief Poll for and process GLFW events.
		void PollEvents();

		/**
		* @brief Check if the window should close.
		* @return True if the window should close, false otherwise.
		*/
		bool WindowShouldClose() const;

		/// @brief Swap the buffers for the window.
		void SwapBuffers() const;

		//Member variables

		/// @brief Name of the scene.
		std::string name;
		/// @brief GLSL version.
		const char* glsl_version = nullptr;
		/// @brief Pointer to the window handle.
		GLFWwindow* window = nullptr;
		/// @brief Width of the window.
		int width;
		/// @brief Height of the window.
		int height;
		/// @brief Background color.
		float bg_color[4];
		/// @brief Shared pointer to the Texture.
		std::shared_ptr<Texture> texture;
		/// @brief Unique pointer to the shader.
		std::unique_ptr<Shader> shader;
		/// @brief Unique pointer to the thermodynamic simulation render structure.
		std::unique_ptr<SimulationRenderStructs::SimulationRenderItems> sim_render;
		/// @brief Error status of the scene.
		bool error_status = false;
	};

	/**
	* @details
	* Custom constructor for the SceneImpl class. Initializes the name, window
	* manager, and render manager.
	*/
	Scene::SceneImpl::SceneImpl(
		const std::string& name,
		const int& width,
		const int& height,
		const float* bg_color) :
		name(name),
		width(width),
		height(height),
		bg_color{ bg_color[0], bg_color[1], bg_color[2], bg_color[3] }
	{
		spdlog::info("Creating OpenGL window: {} ({}, {})", name, width, height);

		if (!glfwInit())
		{
			spdlog::error("Failed to initialize GLFW");
			glfwTerminate();
			return;
		}

		glsl_version = "#version 130";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		window = glfwCreateWindow(
			this->width,
			this->height,
			this->name.c_str(),
			nullptr,
			nullptr);

		if (window == nullptr)
		{
			spdlog::error("Failed to create GLFW window");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, GLFWFramebufferSizeCallback);
		glfwSetErrorCallback(GLFWErrorCallback);
		glfwSwapInterval(1);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			spdlog::error("Failed to initialize OpenGL context");
			glfwTerminate();
			return;
		}

		shader = std::make_unique<Shader>(BASE_VS_PATH, BASE_FS_PATH);
		texture = std::make_shared<Texture>(width, height);

		error_status = texture->GetErrorStatus() || shader->GetErrorStatus();

		spdlog::info(
			"Successfully created OpenGL window: {} ({}, {})",
			name,
			width,
			height);
	}

	/**
	* @details
	* Destructor that terminates the GLFW library.
	*/
	Scene::SceneImpl::~SceneImpl()
	{
		spdlog::info("Destroying OpenGL scene: {}", name);

		glfwDestroyWindow(window);
		glfwTerminate();

		window = nullptr;
		glsl_version = nullptr;
	}

	/**
	* @details
	* Apply the background color (clear color) to the window.
	*/
	void Scene::SceneImpl::ApplyClearColor() const
	{
		glClearColor(
			bg_color[0],
			bg_color[1],
			bg_color[2],
			bg_color[3]);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	/**
	* @details
	* OpenGL error callback function. Logs the error with spdlog.
	*/
	void Scene::SceneImpl::GLFWErrorCallback(int error, const char* description)
	{
		spdlog::error("GLFW Error ({0}): {1}", error, description);
	}

	/**
	* @details
	* OpenGL frame buffer callback function. Sets the viewport to the new width
	* and height.
	*/
	void Scene::SceneImpl::GLFWFramebufferSizeCallback(
		GLFWwindow* window,
		int width,
		int height)
	{
		glViewport(0, 0, width, height);
	}

	/**
	* @details
	* Poll for and process GLFW events.
	*/
	void Scene::SceneImpl::PollEvents()
	{
		glfwPollEvents();
	}

	/**
	* @details
	* Get whether the window should close from OpenGL.
	*/
	bool Scene::SceneImpl::WindowShouldClose() const
	{
		return glfwWindowShouldClose(window);
	}

	/**
	* @details
	* Swap the buffers in OpenGL.
	*/
	void Scene::SceneImpl::SwapBuffers() const
	{
		glfwSwapBuffers(window);
	}

	/**
	* @details
	* Custom constructor for the Scene class. Passes the name, width, and height
	* to the PIMPL implementation.
	*/
	Scene::Scene(
		const std::string& name,
		const int& width,
		const int& height,
		const float* bg_color) :
		_impl(std::make_unique<Scene::SceneImpl>(name, width, height, bg_color))
	{}

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
	* Get the error status of the scene.
	*/
	bool Scene::GetErrorStatus() const
	{
		return _impl->error_status;
	}

	/**
	* @details
	* Get the OpenGL shader ID..
	*/
	unsigned int Scene::GetShaderID() const
	{
		return _impl->shader->GetGLFWShader();
	}

	/**
	* @details
	* Get the aspect ratio of the texture from the render manager.
	*/
	float Scene::GetTextureAspectRatio() const
	{
		return _impl->texture->GetAspectRatio();
	}

	/**
	* @details
	* Get the window size as a pair of ints from the window manager.
	*/
	std::pair<int, int> Scene::GetWindowSize() const
	{
		return std::pair<int, int>(_impl->width, _impl->height);
	}

	/**
	* @details
	* Initialize the given simulation render items.
	*/
	void Scene::InitializeSimulationRenderItems(
		SimulationTypes type,
		std::vector<float>& particles,
		const float radius)
	{
		std::string name = "";

		switch (type)
		{
		case SimulationTypes::THERMODYNAMICS:
			name = "Thermodynamics";
		}

		spdlog::info("Initializing simulation render items: {}", name);

		if (type == SimulationTypes::THERMODYNAMICS)
		{
			_impl->sim_render =
				std::make_unique<SimulationRenderStructs::ThermodynamicsRenderItems>(
					particles,
					radius);
		}
		else
		{
			spdlog::error("Unknown simulation type: {}", name);
			return;
		}

		spdlog::info("Successfully initialized simulation render items: {}", name);
	}

	/**
	* @details
	* Passes the color values to the render manager for rendering the scene.
	*/
	void Scene::Render()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		int display_w, display_h;
		glfwGetFramebufferSize(_impl->window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		_impl->ApplyClearColor();

		GLenum err = glGetError();
		if (err != GL_NO_ERROR) spdlog::error("OpenGL error in Render: {}", err);
	}

	/**
	* @details
	* Render the simulation items.
	*/
	void Scene::RenderSimulationItems()
	{
		if (_impl->sim_render) _impl->sim_render->Render();
	}

	/**
	* @details
	* Render the texture for the ImGui render window.
	*/
	void Scene::RenderTexture()
	{
		if(_impl->texture)
		{
			//Grab the aspect ratio and calculate the orthographic projection
			float aspect_ratio = _impl->texture->GetAspectRatio();
			float ortho_width = 1.0f;
			float ortho_height = ortho_width / aspect_ratio;

			glm::mat4 projection = glm::ortho(
				-ortho_width, ortho_width,
				-ortho_height, ortho_height,
				-1.0f, 1.0f);

			GLuint shader = _impl->shader->GetGLFWShader();

			glUseProgram(shader);

			//Use the shader program
			GLuint projection_loc = glGetUniformLocation(shader, "projection");
			glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(projection));

			//Grab the OpenGL error and pass it to the error handler if there is one
			GLenum err = glGetError();
			if (err != GL_NO_ERROR)
				spdlog::error("OpenGL error in RenderTexture: {}", err);

			//Render the objects and texture
			_impl->texture->Render();
		}
	}

	/**
	* @details
	* Poll the OpenGL events and process them.
	*/
	void Scene::PollEvents()
	{
		_impl->PollEvents();
	}

	/**
	* @details
	* Swap the buffers in the window manager.
	*/
	void Scene::SwapBuffers() const
	{
		_impl->SwapBuffers();
	}

	/**
	* @details
	* Get whether the window should close.
	*/
	bool Scene::WindowShouldClose() const
	{
		return _impl->WindowShouldClose();
	}
}