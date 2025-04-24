/**
* @file SimulationRenderStructs.cpp
* @brief
* Render data structure implementations for individual simulations. Uses the PIMPL
* idiom to hide implementation details.
*/

#include "SimulationRenderItems.hpp"

#include "graphics/Shader.hpp"

/// @brief Graphics namespace
namespace Graphics
{
	/// @brief SimulationRenderStruts namespace
	namespace SimulationRenderStructs
	{
		/// @brief SimulationRenderItems PIMPL implementation structure.
		struct SimulationRenderItems::SimulationRenderItemsImpl
		{
			//Deleted constructors

			/// @brief Deleted default constructor.
			SimulationRenderItemsImpl() = delete;
			/// @brief Deleted copy constructor.
			SimulationRenderItemsImpl(const SimulationRenderItemsImpl& other) = delete;
			/// @brief Deleted copy assignment operator.
			SimulationRenderItemsImpl& operator=(const SimulationRenderItemsImpl& other) = delete;
			/// @brief Deleted move constructor.
			SimulationRenderItemsImpl(const SimulationRenderItemsImpl&& other) = delete;
			/// @brief Deleted move assignment operator.
			SimulationRenderItemsImpl& operator=(const SimulationRenderItemsImpl&& other) = delete;

			//Custom constructors

			/**
			* @brief Custom constructor for the SimulationRenderItemsImpl class.
			* @param vs_file The vertex shader file.
			* @param fs_file The fragment shader file.
			*/
			SimulationRenderItemsImpl(
				const std::string& vs_file,
				const std::string& fs_file);

			//Default constructors/destructor

			/// @brief Destructor.
			~SimulationRenderItemsImpl();

			//Member methods

			//Member variables

			/// @brief Pointer to the shader object.
			std::shared_ptr<Shader> shader;
		};

		/**
		* @details
		* Custom constructor for the SimulationRenderItemsImpl class. Initializes
		* the shader object with the vertex and fragment shader files.
		*/
		SimulationRenderItems::SimulationRenderItemsImpl::SimulationRenderItemsImpl(
			const std::string& vs_file,
			const std::string& fs_file) :
			shader(std::make_shared<Shader>(vs_file, fs_file))
		{}

		SimulationRenderItems::SimulationRenderItemsImpl::~SimulationRenderItemsImpl() = default;

		/**
		* @details
		* Custom constructor for the SimulationRenderItems class. Passes the
		* vertex and fragment to the PIMPL implementation.
		*/
		SimulationRenderItems::SimulationRenderItems(
			const std::string& vs_file,
			const std::string& fs_file) :
			_impl(
				std::make_unique<SimulationRenderItems::SimulationRenderItemsImpl>(
					vs_file,
					fs_file))
		{}

		/**
		* @details
		* Default constructor for the SimulationRenderItems class.
		*/
		SimulationRenderItems::SimulationRenderItems() = default;

		/**
		* @details
		* Default destructor for the SimulationRenderItems class.
		*/
		SimulationRenderItems::~SimulationRenderItems() = default;

		/**
		* @details
		* Get the GLFW shader object.
		*/
		unsigned int& SimulationRenderItems::GetShader() const
		{
			return _impl->shader->GetGLFWShader();
		}
	}
}