/**
* @file Texture.cpp
* @brief
* Function definitions for the Texture class. Uses the PIMPL idiom to hide
* implementation details.
*/

#include "Texture.hpp"
#include "utils/GlfwIncludes.hpp"

#include "spdlog/spdlog.h"

/// @brief Scene namespace
namespace Graphics
{
	/// @brief Texture PIMPL implementation structure.
	struct Texture::TextureImpl
	{
		//Deleted constructors

		/// @brief Deleted default constructor.
		TextureImpl() = delete;
		/// @brief Deleted copy constructor.
		TextureImpl(const TextureImpl& other) = delete;
		/// @brief Deleted copy assignment operator.
		TextureImpl& operator=(const TextureImpl& other) = delete;
		/// @brief Deleted move constructor.
		TextureImpl(TextureImpl&& other) = delete;
		/// @brief Deleted move assignment operator.
		TextureImpl& operator=(const TextureImpl&& other) = delete;

		//Custom constructors
		/**
		* @brief Custom constructor for the TextureImpl class.
		* @param width The width of the texture.
		* @param height The height of the texture.
		*/
		TextureImpl(const int& width, const int& height);

		//Default constructors/destructor

		/// @brief Default destructor.
		~TextureImpl();

		//Member methods

		/**
		* @brief Setup the frame buffer and texture for the texture object.
		* @param width The width of the texture.
		* @param height The height of the texture.
		*/
		void SetupFramebufferAndTexture(const int& width, const int& height);

		//Member variables

		/// @brief Width of the texture.
		int width;
		/// @brief Height of the texture.
		int height;
		/// @brief OpenGL frame buffer ID.
		GLuint frame_buffer;
		/// @brief OpenGL texture ID.
		GLuint texture;
		/// @brief Error status of the texture.
		bool error_status = false;
		/// @brief Aspect ratio of the texture.
		float aspect_ratio = 0.0f;
	};

	/**
	* @details
	* Custom constructor for the TextureImpl class. Sets up the frame buffer and
	* texture for the texture object.
	*/
	Texture::TextureImpl::TextureImpl(const int& width, const int& height)
	{
		spdlog::info("Setting up framebuffer and texture: {} x {}", width, height);
		SetupFramebufferAndTexture(width, height);
		spdlog::info("Framebuffer and texture setup complete");
	}

	/**
	* @details
	* Destructor for the TextureImpl class. Deletes the frame buffer and texture.
	*/
	Texture::TextureImpl::~TextureImpl()
	{
		spdlog::info("Destroying framebuffer and texture");
		glDeleteFramebuffers(1, &frame_buffer);
		glDeleteTextures(1, &texture);
	}

	/**
	* @details
	* Sets up the frame buffer and texture in OpenGL.
	*/
	void Texture::TextureImpl::SetupFramebufferAndTexture(const int& width, const int& height)
	{
		this->width = width;
		this->height = height;

		glDeleteFramebuffers(1, &frame_buffer);
		glDeleteTextures(1, &texture);

		glGenFramebuffers(1, &frame_buffer);
		glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			width,
			height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(
			GL_FRAMEBUFFER,
			GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_2D,
			texture,
			0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			spdlog::error("Framebuffer is not complete");
			error_status = true;
		}

		GLenum err = glGetError();
		if(err != GL_NO_ERROR)
		{
			spdlog::error("Texture setup failed: {}", err);
			error_status = true;
		}

		aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
	}

	/**
	* @details
	* Custom constructor for the Texture class. Passes the width and height to the
	* PIMPL implementation.
	*/
	Texture::Texture(const int& width, const int& height) :
		_impl(std::make_unique<TextureImpl>(width, height))
	{}

	/**
	* @details
	* Default constructor for the Texture class.
	*/
	Texture::Texture() = default;

	/**
	* @details
	* Default destructor for the Texture class.
	*/
	Texture::~Texture() = default;

	/**
	* @details
	* Get the error status of the texture.
	*/
	bool Texture::GetErrorStatus() const
	{
		return _impl->error_status;
	}

	/**
	* @details
	* Get the OpenGL texture ID.
	*/
	unsigned int& Texture::GetTextureId()
	{
		return _impl->texture;
	}

	/**
	* @details
	* Render the texture with the texture's variables.
	*/
	void Texture::Render()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _impl->frame_buffer);
		glViewport(0, 0, _impl->width, _impl->height);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		GLenum err = glGetError();
		if (err != GL_NO_ERROR) spdlog::error("Texture render failed: {}", err);
	}

	/**
	* @details
	* Pass the width and height to the PIMPL implementation to setup the frame
	* buffer and texture.
	*/
	void Texture::SetupFramebufferAndTexture(const int& width, const int& height)
	{
		spdlog::info("Setting up framebuffer and texture: {} x {}", width, height);
		_impl->SetupFramebufferAndTexture(width, height);
		spdlog::info("Framebuffer and texture setup complete");
	}

	/**
	* @details
	* Get the aspect ratio of the texture.
	*/
	float Texture::GetAspectRatio() const
	{
		return _impl->aspect_ratio;
	}
}