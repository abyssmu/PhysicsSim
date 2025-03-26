#pragma once

#ifndef _BOX_
#define _BOX_

#include "Object.h"

#include <glm/glm.hpp>
#include <memory>

//External forward declarations

//Internal declarations
namespace Object
{
	//External forward declarations

	//Internal declarations
	class Box : public Object
	{
	public:
		//Deleted constructors
		Box(const Box& other) = delete;
		Box& operator=(const Box& other) = delete;
		Box(const Box&& other) = delete;
		Box& operator=(const Box&& other) = delete;

		//Custom constructors
		Box(
			const int center_x,
			const int center_y,
			const int box_width_perc,
			const int box_height_perc,
			const int max_width,
			const int max_height);

		//Default constructors/destructor
		Box();
		~Box();

		//Member methods

		//PIMPL idiom
	private:
		struct BoxImpl;
		std::unique_ptr<BoxImpl> _impl;
	};
}

#endif