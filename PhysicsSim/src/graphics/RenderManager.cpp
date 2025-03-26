#include "RenderManager.h"

#include "utils/GlfwAndDebugIncludes.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Scene
{
	struct RenderManager::RenderManagerImpl
	{
		//Deleted constructors
		RenderManagerImpl() = delete;
		RenderManagerImpl(const RenderManagerImpl& other) = delete;
		RenderManagerImpl& operator=(const RenderManagerImpl& other) = delete;
		RenderManagerImpl(const RenderManagerImpl&& other) = delete;
		RenderManagerImpl& operator=(const RenderManagerImpl&& other) = delete;

		//Custom constructors
		RenderManagerImpl(const int& width, const int& height);

		//Default constructors/destructor
		~RenderManagerImpl() = default;

		//Member methods

		//Member variables
		std::shared_ptr<Texture> texture;
		std::unique_ptr<Shader> shader;
	};

	RenderManager::RenderManagerImpl::RenderManagerImpl(const int& width, const int& height) :
		texture(std::make_shared<Texture>(width, height)),
		shader(std::make_unique<Shader>("src/shader/VertexShader.vs", "src/shader/FragmentShader.fs"))
	{}

	RenderManager::RenderManager() = default;
	RenderManager::~RenderManager() = default;

	RenderManager::RenderManager(const int& width, const int& height) :
		_impl(std::make_unique<RenderManagerImpl>(width, height)) {}

	void RenderManager::RenderTexture(
		std::vector<std::shared_ptr<Object::Object>>& objects,
		const int box_height_perc,
		const int box_width_perc)
	{
		float aspect_ratio = _impl->texture->GetAspectRatio();
		float ortho_height = 1.0f;
		float ortho_width = ortho_height * aspect_ratio;

		glm::mat4 projection = glm::ortho(-ortho_width, ortho_width, -ortho_height, ortho_height, -1.0f, 1.0f);

		GLuint projection_loc = glGetUniformLocation(_impl->shader->GetShader(), "projection");
		glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(projection));

		GLenum err = glGetError();
		if (err != GL_NO_ERROR) DebugMessage("OpenGL error in RenderTexture: " + std::to_string(err), __func__);

		_impl->texture->Render(
			_impl->shader->GetShader(),
			objects,
			box_height_perc,
			box_width_perc);
	}

	std::shared_ptr<Texture> RenderManager::GetTexture()
	{
		return _impl->texture;
	}

	float RenderManager::GetTextureAspectRatio() const
	{
		return _impl->texture->GetAspectRatio();
	}
}