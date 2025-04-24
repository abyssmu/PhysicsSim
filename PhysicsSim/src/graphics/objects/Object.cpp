/**
* @file Object.cpp
* @brief
* Function definitions for the Object class. Uses the PIMPL idiom to hide
* implementation details.
*/

#include "Object.hpp"
#include "utils/GlfwIncludes.hpp"

#include <glm/gtc/type_ptr.hpp>

/// @brief Object namespace
namespace Object
{
	/// @brief Object PIMPL implementation structure.
	struct Object::ObjectImpl
	{
		//Deleted constructors

		/// @brief Deleted default constructor.
		ObjectImpl() = delete;
		/// @brief Deleted copy constructor.
		ObjectImpl(const ObjectImpl& other) = delete;
		/// @brief Deleted copy assignment operator.
		ObjectImpl& operator=(const ObjectImpl& other) = delete;
		/// @brief Deleted move constructor.
		ObjectImpl(const ObjectImpl&& other) = delete;
		/// @brief Deleted move assignment operator.
		ObjectImpl& operator=(const ObjectImpl&& other) = delete;

		//Custom constructors

		/**
		* @brief Custom constructor for the ObjectImpl class.
		* @param pos The position of the object.
		* @param color The color of the object.
		*/
		ObjectImpl(glm::vec3 pos, glm::vec3 color);

		//Default constructors/destructor

		/// @brief Destructor for the ObjectImpl class.
		~ObjectImpl();

		//Member methods

		/**
		* @brief Set the vertices of the object.
		* @param vertices The vector of vertices to set.
		*/
		void SetVertices(std::vector<glm::vec2> vertices);

		//Member variables

		/// @brief Position of the object.
		glm::vec3 position;
		/// @brief Color of the object.
		glm::vec3 color;
		/// @brief Vector of vertices for the object.
		std::vector<glm::vec2> vertices;
		/// @brief Vertex array object.
		GLuint vao;
		/// @brief Vertex buffer object.
		GLuint vbo;
	};

	/**
	* @details
	* Custom constructor for the ObjectImpl class. Initializes the position and
	* the color of the object. Sets the vertices to an empty vector and the
	* vertex array object and vertex buffer object to 0.
	*/
	Object::ObjectImpl::ObjectImpl(glm::vec3 pos, glm::vec3 color) :
		position(pos),
		color(color),
		vertices(),
		vao(0),
		vbo(0)
	{}

	/**
	* @details
	* Destructor for the ObjectImpl class. Deletes the vertex array object and
	* deletes the buffers.
	*/
	Object::ObjectImpl::~ObjectImpl()
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}

	/**
	* @details
	* Sets the vertices for the object. Generates a vertex array object and a vertex
	* buffer array. Binds the vertex buffer and sets the vertex attribute pointers.
	*/
	void Object::ObjectImpl::SetVertices(std::vector<glm::vec2> verts)
	{
		vertices = std::move(verts);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(
			GL_ARRAY_BUFFER,
			vertices.size() * sizeof(glm::vec2),
			vertices.data(),
			GL_STATIC_DRAW);

		glVertexAttribPointer(
			0,
			2,
			GL_FLOAT,
			GL_FALSE,
			sizeof(glm::vec2),
			(void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/**
	* @details
	* Custom constructor for the Object class. Passes the position and color to
	* the PIMPL implementation.
	*/
	Object::Object(
		const float x,
		const float y,
		const float z,
		const float r,
		const float g,
		const float b) :
		_object_impl(
			std::make_unique<ObjectImpl>(glm::vec3(x,y,z), glm::vec3(r,g,b)))
	{}

	/**
	* @details
	* Default constructor for the Object class.
	*/
	Object::Object() = default;

	/**
	* @details
	* Default destructor for the Object class.
	*/
	Object::~Object() = default;

	/**
	* @details
	* Draws the object with the given shader. Sets the color and model matrix
	* and then binds the vertex array object. Draws the object using the triangle
	* fan.
	*/
	void Object::Draw(GLuint shader) const
	{
		glUseProgram(shader);

		GLint color_loc = glGetUniformLocation(shader, "inColor");
		glUniform3fv(color_loc, 1, glm::value_ptr(_object_impl->color));

		glm::mat4 model = glm::translate(glm::mat4(1.0f), _object_impl->position);
		GLuint model_loc = glGetUniformLocation(shader, "model");
		glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));

		glBindVertexArray(_object_impl->vao);
		glDrawArrays(GL_TRIANGLE_FAN, 0, _object_impl->vertices.size());
		glBindVertexArray(0);
	}

	/**
	* @details
	* Passes the vertices to the PIMPL implementation.
	*/
	void Object::SetVertices(std::vector<glm::vec2> vertices)
	{
		_object_impl->SetVertices(vertices);
	}

	/**
	* @details
	* Get the number of vertices in the object.
	*/
	int Object::GetNumVertices() const
	{
		return int(_object_impl->vertices.size());
	}

	/**
	* @details
	* Get the position of the object. Returns a reference to the position.
	*/
	glm::vec3& Object::GetPosition() const
	{
		return _object_impl->position;
	}

	/**
	* @details
	* Get the color of the object. Returns a reference to the color.
	*/
	glm::vec3& Object::GetColor() const
	{
		return _object_impl->color;
	}

	/**
	* @details
	* Gets the vertex buffer object. Returns a reference to the vertex buffer
	* object.
	*/
	GLuint& Object::GetVBO() const
	{
		return _object_impl->vbo;
	}

	/**
	* @details
	* Gets the vertex array object. Returns a reference to the vertex array
	* object.
	*/
	GLuint& Object::GetVAO() const
	{
		return _object_impl->vao;
	}
}