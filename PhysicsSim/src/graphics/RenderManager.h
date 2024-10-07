#pragma once

#ifndef _RENDERMANAGER_
#define _RENDERMANAGER_

#include <memory>
#include <vector>

//External forward declarations
namespace Object
{
	class Object;
}

//Internal declarations
namespace Scene
{
	//External forward declarations
	class Texture;
	class Shader;

	//Internal declarations
	class RenderManager
	{
	public:
		//Deleted constructors
		RenderManager(const RenderManager& other) = delete;
		RenderManager& operator=(const RenderManager& other) = delete;
		RenderManager(RenderManager&& other) = delete;
		RenderManager& operator=(const RenderManager&& other) = delete;

		//Custom constructors
		RenderManager(const int& width, const int& height);

		//Default constructors/destructor
		RenderManager();
		~RenderManager();

		//Member methods
		void RenderTexture(std::vector<std::shared_ptr<Object::Object>>& objects);
		std::shared_ptr<Texture> GetTexture();
		float GetTextureAspectRatio() const;

		//PIMPL idiom
	private:
		struct RenderManagerImpl;
		std::unique_ptr<RenderManagerImpl> _impl;
	};
}

#endif