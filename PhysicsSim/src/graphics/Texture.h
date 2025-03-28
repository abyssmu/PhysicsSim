#pragma once

#ifndef _TEXTURE_
#define _TEXTURE_

#include <memory>
#include <vector>

//External forward declarations
typedef unsigned int GLuint;
namespace Object
{
	class Object;
}

//Internal declarations
namespace Scene
{
	//External forward declarations

	//Internal declarations
	class Texture
	{
	public:
		//Deleted constructors
		Texture(const Texture& other) = delete;
		Texture& operator=(const Texture& other) = delete;
		Texture(Texture&& other) = delete;
		Texture& operator=(const Texture&& other) = delete;

		//Custom constructors
		Texture(const int& width, const int& height);

		//Default constructors/destructor
		Texture();
		~Texture();

		//Member methods
		GLuint& GetTextureId();
		void Render(
			GLuint& shader,
			std::vector<std::shared_ptr<Object::Object>>& objects,
			const int box_height_perc,
			const int box_width_perc);
		void SetupFramebufferAndTexture(const int& width, const int& height);
		float GetAspectRatio() const;

		//PIMPL idiom
	private:
		struct TextureImpl;
		std::unique_ptr<TextureImpl> _impl;
	};
}

#endif