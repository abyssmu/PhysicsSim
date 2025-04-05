/**
* @file RenderManager.cpp
* @brief
* Function definitions for the RenderManager class. Uses the PIMPL idiom to hide
* implementation details.
*/

#include "RenderManager.hpp"

#include "utils/GlfwIncludes.hpp"
#include "graphics/Shader.hpp"
#include "graphics/Texture.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

/// @brief Scene namespace
namespace Scene
{
	/// @brief RenderManager PIMPL implementation structure.
	struct RenderManager::RenderManagerImpl
	{
		//Deleted constructors

		/// @brief Deleted default constructor.
		RenderManagerImpl() = delete;
		/// @brief Deleted copy constructor.
		RenderManagerImpl(const RenderManagerImpl& other) = delete;
		/// @brief Deleted copy assignment operator.
		RenderManagerImpl& operator=(const RenderManagerImpl& other) = delete;
		/// @brief Deleted move constructor.
		RenderManagerImpl(const RenderManagerImpl&& other) = delete;
		/// @brief Deleted move assignment operator.
		RenderManagerImpl& operator=(const RenderManagerImpl&& other) = delete;

		//Custom constructors

		/**
		* @brief Custom constructor for the RenderManagerImpl class.
		* @param width The width of the texture.
		* @param height The height of the texture.
		*/
		RenderManagerImpl(const int& width, const int& height);

		//Default constructors/destructor

		/// @brief Default destructor.
		~RenderManagerImpl() = default;

		//Member methods

		//Member variables

		/// @brief Shared pointer to the Texture.
		std::shared_ptr<Texture> texture;
		/// @brief Unique pointer to the Shader.
		std::unique_ptr<Shader> shader;
	};

	/**
	* @details
	* Custom constructor for the RenderManagerImpl class. Passes parameters to the
	* texture and shader classes for initialization.
	*/
	RenderManager::RenderManagerImpl::RenderManagerImpl(const int& width, const int& height) :
		texture(std::make_shared<Texture>(width, height)),
		shader(std::make_unique<Shader>("src/shader/VertexShader.vs", "src/shader/FragmentShader.fs"))
	{}

	/**
	* @details
	* Default constructor for the RenderManager class.
	*/
	RenderManager::RenderManager() = default;

	/**
	* @details
	* Default destructor for the RenderManager class.
	*/
	RenderManager::~RenderManager() = default;

	/**
	* @details
	* Custom constructor for the RenderManager class. Passes parameters to the
	* PIMPL pointer for initialization.
	*/
	RenderManager::RenderManager(const int& width, const int& height) :
		_impl(std::make_unique<RenderManagerImpl>(width, height)) {}

	/**
	* @details
	* Render the texture for the ImGui render window. Calculates the OpenGL parameters
	* for rendering the texture. Then calls the texture render method.
	*/
	void RenderManager::RenderTexture(
		std::vector<std::shared_ptr<Object::Object>>& objects,
		const int box_height_perc,
		const int box_width_perc)
	{
		//Grab the aspect ratio and calculate the orthographic projection
		float aspect_ratio = _impl->texture->GetAspectRatio();
		float ortho_height = 1.0f;
		float ortho_width = ortho_height * aspect_ratio;

		glm::mat4 projection = glm::ortho(-ortho_width, ortho_width, -ortho_height, ortho_height, -1.0f, 1.0f);

		//Use the shader program
		GLuint projection_loc = glGetUniformLocation(
			_impl->shader->GetShader(),
			"projection");
		glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(projection));

		//Grab the OpenGL error and pass it to the error handler if there is one
		GLenum err = glGetError();
		//if (err != GL_NO_ERROR) DebugMessage("OpenGL error in RenderTexture: " + std::to_string(err), __func__);

		//Render the objects and texture
		_impl->texture->Render(
			_impl->shader->GetShader(),
			objects,
			box_height_perc,
			box_width_perc);
	}

	/**
	* @details
	* Retrieve the texture from the RenderManager.
	*/
	std::shared_ptr<Texture> RenderManager::GetTexture()
	{
		return _impl->texture;
	}

	/**
	* @details
	* Retrieve the aspect ratio of the texture.
	*/
	float RenderManager::GetTextureAspectRatio() const
	{
		return _impl->texture->GetAspectRatio();
	}
}