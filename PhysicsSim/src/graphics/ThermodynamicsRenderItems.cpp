/**
* @file ThermodynamicsRenderItems.cpp
* @brief
* Function definitions for the ThermodynamicsRenderItems. Uses the PIMPL idiom to
* hide implementation details.
*/

#include "ThermodynamicsRenderItems.hpp"

#include "graphics/objects/Circle.hpp"
#include "graphics/Shader.hpp"
#include "utils/GlfwIncludes.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "spdlog/spdlog.h"

/// @brief Graphics namespace
namespace Graphics
{
	/// @brief SimulationRenderStructs namespace
	namespace SimulationRenderStructs
	{
		/// @brief ThermodynamicsRenderItems PIMPL implementation structure.
		struct ThermodynamicsRenderItems::ThermodynamicsRenderItemsImpl
		{
			//Deleted constructors

			/// @brief Deleted default constructor.
			ThermodynamicsRenderItemsImpl() = delete;
			/// @brief Deleted copy constructor.
			ThermodynamicsRenderItemsImpl(const ThermodynamicsRenderItemsImpl& other) = delete;
			/// @brief Deleted copy assignment operator.
			ThermodynamicsRenderItemsImpl& operator=(const ThermodynamicsRenderItemsImpl& other) = delete;
			/// @brief Deleted move constructor.
			ThermodynamicsRenderItemsImpl(const ThermodynamicsRenderItemsImpl&& other) = delete;
			/// @brief Deleted move assignment operator.
			ThermodynamicsRenderItemsImpl& operator=(const ThermodynamicsRenderItemsImpl&& other) = delete;

			//Custom constructors

			/**
			* @brief Custom constructor for the ThermodynamicsRenderItemsImpl class.
			* @param particles Vector of particle data.
			* @param radius The radius of the particles.
			*/
			ThermodynamicsRenderItemsImpl(
				std::vector<float>& particles,
				const float radius);

			//Default constructors/destructor

			/// @brief Default destructor.
			~ThermodynamicsRenderItemsImpl();

			//Member methods

			//Member variables

			/// @brief Circle object.
			std::shared_ptr<Object::Circle> circle;
			/// @brief Instance buffer for OpenGL instancing.
			GLuint instance_buffer = 0;
			/// @brief Instance data for OpenGL instancing.
			std::vector<float> instance_data;
		};

		/**
		* @details
		* Custom constructor for the ThermodynamicsRenderItemsImpl class. Initializes
		* instance data and instance buffer for OpenGL instancing. Creates the
		* circle object for rendering.
		* Particle data is setup with the following format:
		* x, y, z, padding, red, green, blue, padding, x_scale, y_scale, z_scale, padding
		*/
		ThermodynamicsRenderItems::ThermodynamicsRenderItemsImpl::ThermodynamicsRenderItemsImpl(
			std::vector<float>& particles,
			const float radius) :
			circle(std::make_shared<Object::Circle>(
				radius,
				0.0f, // x
				0.0f, // y
				0.0f, // z
				1.0f, // red
				0.0f, // green
				0.0f)) // blue
		{
			spdlog::info(
				"Creating ThermodynamicsRenderItems with {} particles",
				particles.size() / 12);

			/*
			* Parse the particle data by adding a single padding value for each
			* of the three data types (position, color, and scale).
			*/
			instance_data = move(particles);

			// Create and bind instance buffer
			glGenBuffers(1, &instance_buffer);
			glBindBuffer(GL_ARRAY_BUFFER, instance_buffer);
			glBufferData(
				GL_ARRAY_BUFFER,
				instance_data.size() * sizeof(float),
				instance_data.data(),
				GL_STATIC_DRAW);

			// Setup instanced attribute pointers when we create the instance buffer
			GLuint vao = circle->GetVAO();
			glBindVertexArray(vao);

			// Position attribute (location 1)
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(
				1,
				4,
				GL_FLOAT,
				GL_FALSE,
				12 * sizeof(float),
				(void*)0);
			glVertexAttribDivisor(1, 1); // This makes it instanced

			// Color attribute (location 2)
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(
				2,
				4,
				GL_FLOAT,
				GL_FALSE,
				12 * sizeof(float),
				(void*)(4 * sizeof(float)));
			glVertexAttribDivisor(2, 1); // This makes it instanced

			// Scale attribute (location 3)
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(
				3,
				4,
				GL_FLOAT,
				GL_FALSE,
				12 * sizeof(float),
				(void*)(8 * sizeof(float)));
			glVertexAttribDivisor(3, 1); // This makes it instanced

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLuint err = glGetError();
			if (err != GL_NO_ERROR)
				spdlog::error("OpenGL error in ThermodynamicsRenderItemsImpl constructor: {}", err);

			spdlog::info(
				"ThermodynamicsRenderItems created with {} instanced particles",
				instance_data.size() / 12);
		}

		/**
		* @details
		* Default destructor for the ThermodynamicsRenderItemsImpl class.
		*/
		ThermodynamicsRenderItems::ThermodynamicsRenderItemsImpl::~ThermodynamicsRenderItemsImpl()
		{
			spdlog::info("Destroying ThermodynamicsRenderItemsImpl");

			if (instance_buffer)
			{
				glDeleteBuffers(1, &instance_buffer);
				instance_buffer = 0;
			}
		}

		/**
		* @details
		* Custom constructor for the ThermodynamicsRenderItems class. Passes the
		* particles and radius to the PIMPL implementation. Initializes the parent
		* class with the vertex and fragment shader file paths.
		*/
		ThermodynamicsRenderItems::ThermodynamicsRenderItems(
			std::vector<float>& particles,
			const float radius) :
			SimulationRenderItems(PARTICLE_VS_PATH, PARTICLE_FS_PATH),
			_impl(std::make_unique<ThermodynamicsRenderItemsImpl>(
				particles,
				radius))
		{}

		/**
		* @details
		* Default constructor for the ThermodynamicsRenderItems class.
		*/
		ThermodynamicsRenderItems::ThermodynamicsRenderItems() = default;

		/**
		* @details
		* Default destructor for the ThermodynamicsRenderItems class.
		*/
		ThermodynamicsRenderItems::~ThermodynamicsRenderItems() = default;

		/**
		* @details
		* Render the items in the simulation.
		*/
		void ThermodynamicsRenderItems::Render()
		{
			if (_impl->instance_data.empty() || !_impl->instance_buffer)
				return;

			GLuint shader = GetShader();

			if (shader == 0)
			{
				spdlog::error("Shader program is not valid");
				return;
			}

			glUseProgram(shader);

			glm::mat4 model = glm::mat4(1.0f);
			GLuint model_loc = glGetUniformLocation(shader, "model");
			glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));

			if (model_loc == -1)
			{
				spdlog::error("Model matrix uniform location not found");
				return;
			}

			glm::mat4 projection = glm::ortho(
				-1.0f, 1.0f,
				-1.0f, 1.0f,
				-1.0f, 1.0f);

			GLuint projection_loc = glGetUniformLocation(shader, "projection");
			glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(projection));

			if (projection_loc == -1)
			{
				spdlog::error("Projection matrix uniform location not found");
				return;
			}

			GLuint err = glGetError();
			if (err != GL_NO_ERROR)
				spdlog::error("OpenGL error in setting uniforms: {}", err);

			//Bind the instance buffer
			glBindBuffer(GL_ARRAY_BUFFER, _impl->instance_buffer);

			//Render all particles using OpenGL instancing
			glBindVertexArray(_impl->circle->GetVAO());

			glDrawArraysInstanced(
				GL_TRIANGLE_FAN,
				0,
				_impl->circle->GetNumVertices(),
				int(_impl->instance_data.size() / 12));

			glBindVertexArray(0);

			err = glGetError();
			if (err != GL_NO_ERROR)
				spdlog::error("OpenGL error in ThermodynamicsRenderItems::Render: {}", err);
		}
	}
}