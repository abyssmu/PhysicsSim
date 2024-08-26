#include "Scene.h"

namespace Scene
{
	RenderManager::RenderManager(const int& width, const int& height)
	{
		_shader = make_unique<Shader>("src/vertex_shader.vs", "src/fragment_shader.fs");
		_texture = make_unique<Texture>(width, height);

		float vertices[] =
		{
			// positions        // colors
			 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // top
			-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom left
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // bottom right
		};

		glGenVertexArrays(1, &_vertex_array);
		glGenBuffers(1, &_vertex_buffer);
		glBindVertexArray(_vertex_array);
		glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	void RenderManager::Terminate()
	{
		glDeleteVertexArrays(1, &_vertex_array);
		glDeleteBuffers(1, &_vertex_buffer);

		_shader->Terminate();
		_texture->Terminate();
	}

	void RenderManager::RenderTexture()
	{
		float aspect_ratio = _texture->GetAspectRatio();
		float ortho_height = 1.0f;
		float ortho_width = ortho_height * aspect_ratio;

		glm::mat4 projection = glm::ortho(-ortho_width, ortho_width, -ortho_height, ortho_height, -1.0f, 1.0f);

		GLuint projection_loc = glGetUniformLocation(_shader->GetShader(), "projection");
		glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(projection));

		_texture->Render(_shader->GetShader(), _vertex_array);

		GLenum err = glGetError();
		if (err != GL_NO_ERROR) std::cout << "OpenGL error in RenderTexture: " << err << std::endl;

	}

	void RenderManager::ResizeTexture(const int& width, const int& height)
	{
		_texture->SetupFramebufferAndTexture(width, height);
	}

	GLuint& RenderManager::GetTexture()
	{
		return _texture->GetTexture();
	}

	float RenderManager::GetTextureAspectRatio() const
	{
		return _texture->GetAspectRatio();
	}
}