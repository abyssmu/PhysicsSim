#include "Box.h"
#include "utils/GlfwAndDebugIncludes.h"

namespace Object
{
	struct Box::BoxImpl
	{
		//Deleted constructors
		BoxImpl() = delete;
		BoxImpl(const BoxImpl& other) = delete;
		BoxImpl& operator=(const BoxImpl& other) = delete;
		BoxImpl(const BoxImpl&& other) = delete;
		BoxImpl& operator=(const BoxImpl&& other) = delete;

		//Custom constructors

		//Default constructors/destructor
		~BoxImpl() = default;

		//Member methods

		//Member variables
	};

	Box::Box(
		const int center_x,
		const int center_y,
		const int box_width_perc,
		const int box_height_perc,
		const int max_width,
		const int max_height)
	{

	}

	Box::Box() = default;
	Box::~Box() = default;
}