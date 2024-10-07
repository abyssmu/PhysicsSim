#include "Object.h"
#include "utils/GlfwAndDebugIncludes.h"

#include <glm/gtc/type_ptr.hpp>

namespace Object
{
	struct Object::ObjectImpl
	{
		//Deleted constructors
		ObjectImpl() = delete;
		ObjectImpl(const ObjectImpl& other) = delete;
		ObjectImpl& operator=(const ObjectImpl& other) = delete;
		ObjectImpl(const ObjectImpl&& other) = delete;
		ObjectImpl& operator=(const ObjectImpl&& other) = delete;

		//Custom constructors
		ObjectImpl(glm::vec3 pos, glm::vec3 color);

		//Default constructors/destructor
		~ObjectImpl();

		//Member methods
		void SetVertices(std::vector<glm::vec2> vertices);

		//Member variables
		glm::vec3 position;
		glm::vec3 color;
		std::vector<glm::vec2> vertices;
		GLuint vao;
		GLuint vbo;
	};

	Object::ObjectImpl::ObjectImpl(glm::vec3 pos, glm::vec3 color) :
		position(pos),
		color(color),
		vertices(),
		vao(0),
		vbo(0)
	{}

	Object::ObjectImpl::~ObjectImpl()
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}

	void Object::ObjectImpl::SetVertices(std::vector<glm::vec2> verts)
	{
		vertices = std::move(verts);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Object::Object(
		const float x,
		const float y,
		const float z,
		const float r,
		const float g,
		const float b) :
		_object_impl(std::make_unique<ObjectImpl>(glm::vec3(x,y,z), glm::vec3(r,g,b)))
	{}

	Object::Object() = default;
	Object::~Object() = default;

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

	void Object::SetVertices(std::vector<glm::vec2> vertices)
	{
		_object_impl->SetVertices(vertices);
	}

	glm::vec3& Object::GetPosition() const
	{
		return _object_impl->position;
	}
}