/**
* @file Texture.cpp
* @brief
* Function definitions for the Texture class. Uses the PIMPL idiom to hide
* implementation details.
*/

#include "Texture.hpp"
#include "utils/GlfwIncludes.hpp"

#include "objects/Object.hpp"

/// @brief Scene namespace
namespace Scene
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
		/// @brief Destructor.
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
	};

	/**
	* @details
	* Custom constructor for the TextureImpl class. Sets up the frame buffer and
	* texture for the texture object.
	*/
	Texture::TextureImpl::TextureImpl(const int& width, const int& height)
	{
		SetupFramebufferAndTexture(width, height);
	}

	/**
	* @details
	* Destructor for the TextureImpl class. Deletes the frame buffer and texture.
	*/
	Texture::TextureImpl::~TextureImpl()
	{
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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			//DebugMessage("Framebuffer is not complete!", __func__);
		}

		GLenum err = glGetError();
		//if (err != GL_NO_ERROR) DebugMessage("Framebuffer and texture creation failed: " + std::to_string(err), __func__);
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
	* Get the OpenGL texture ID.
	*/
	GLuint& Texture::GetTextureId()
	{
		return _impl->texture;
	}

	/**
	* @details
	* Render the texture with the given shader and objects. Use the box width and
	* height percentages to render a bounding box if needed.
	*/
	void Texture::Render(
		GLuint& shader,
		std::vector<std::shared_ptr<Object::Object>>& objects,
		const int box_height_perc,
		const int box_width_perc)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _impl->frame_buffer);
		glViewport(0, 0, _impl->width, _impl->height);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader);

		//Render all the simulation related objects
		for (size_t i = 0; i < objects.size(); ++i)
		{
			objects[i]->Draw(shader);
		}

		//If the simulation requires a bounding box, render it here
		if (box_height_perc > 0 && box_width_perc > 0)
		{
			//Render the bounding box using OpenGL3

		}

		GLenum err = glGetError();
		//if (err != GL_NO_ERROR) DebugMessage("Texture failed to render: " + std::to_string(err), __func__);
	}

	/**
	* @details
	* Pass the width and height to the PIMPL implementation to setup the frame
	* buffer and texture.
	*/
	void Texture::SetupFramebufferAndTexture(const int& width, const int& height)
	{
		_impl->SetupFramebufferAndTexture(width, height);
	}

	/**
	* @details
	* Get the aspect ratio of the texture.
	*/
	float Texture::GetAspectRatio() const
	{
		return static_cast<float>(_impl->width) / static_cast<float>(_impl->height);
	}
}