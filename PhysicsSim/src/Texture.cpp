#include "Scene.h"

namespace Scene
{
	Texture::~Texture()
	{
		glDeleteFramebuffers(1, &_frame_buffer);
		glDeleteTextures(1, &_texture);
	}

	Texture::Texture(const int& width, const int& height)
	{
		SetupFramebufferAndTexture(width, height);
	}

	GLuint& Texture::GetTexture()
	{
		return _texture;
	}

	void Texture::Render(const int& width, const int& height, GLuint& shader, GLuint& vert_array)
	{
		if (width != _width || height != _height) SetupFramebufferAndTexture(width, height);

		glBindFramebuffer(GL_FRAMEBUFFER, _frame_buffer);
		glViewport(0, 0, _width, _height);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader);
		glBindVertexArray(vert_array);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void Texture::SetupFramebufferAndTexture(const int& width, const int& height)
	{
		glDeleteFramebuffers(1, &_frame_buffer);
		glDeleteTextures(1, &_texture);

		glGenFramebuffers(1, &_frame_buffer);
		glBindFramebuffer(GL_FRAMEBUFFER, _frame_buffer);

		glGenTextures(1, &_texture);
		glBindTexture(GL_TEXTURE_2D, _texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}