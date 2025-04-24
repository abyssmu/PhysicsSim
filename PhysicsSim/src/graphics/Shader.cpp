/**
* @file Shader.cpp
* @brief
* Function definitions for the Shader class. Uses the PIMPL idiom to hide
* implementation details.
*/

#include "Shader.hpp"

#include "utils/GlfwIncludes.hpp"

#include "spdlog/spdlog.h"

#include <fstream>
#include <sstream>

/// @brief Scene namespace
namespace Graphics
{
	/// @brief Shader PIMPL implementation structure.
	struct Shader::ShaderImpl
	{
		//Deleted constructors

		/// @brief Deleted default constructor.
		ShaderImpl() = delete;
		/// @brief Deleted copy constructor.
		ShaderImpl(const ShaderImpl& other) = delete;
		/// @brief Deleted copy assignment operator.
		ShaderImpl& operator=(const ShaderImpl& other) = delete;
		/// @brief Deleted move constructor.
		ShaderImpl(const ShaderImpl&& other) = delete;
		/// @brief Deleted move assignment operator.
		ShaderImpl& operator=(const ShaderImpl&& other) = delete;

		//Custom constructors

		/**
		* @brief Custom constructor for the ShaderImpl class.
		* @param vs_file The vertex shader file.
		* @param fs_file The fragment shader file.
		*/
		ShaderImpl(const std::string& vs_file, const std::string& fs_file);

		//Default constructors/destructor

		/// @brief Destructor.
		~ShaderImpl();

		//Member methods

		/**
		* @brief Check for shader compile errors.
		* @param shader The shader to check.
		* @param type The type of shader to check.
		*/
		void CheckCompileErrors(unsigned int& shader, std::string type);

		//Member variables

		/// @brief OpenGL shader ID.
		GLuint shader;
		/// @brief Error status of the shader.
		bool error_status = false;
	};

	/**
	* @details
	* Custom constructor for the ShaderImpl class. Reads the vertex and fragment
	* shader files and compiles them into an OpenGL shader program.
	*/
	Shader::ShaderImpl::ShaderImpl(
		const std::string& vs_file,
		const std::string& fs_file)
	{
		spdlog::info(
			"Creating OpenGL shader for files vs: {}, fs: {}",
			vs_file,
			fs_file);

		std::ifstream vertex_shader_file;
		std::ifstream fragment_shader_file;
		std::stringstream vertex_shader_stream;
		std::stringstream fragment_shader_stream;

		vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragment_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			vertex_shader_file.open(vs_file);
			fragment_shader_file.open(fs_file);

			vertex_shader_stream << vertex_shader_file.rdbuf();
			fragment_shader_stream << fragment_shader_file.rdbuf();

			vertex_shader_file.close();
			fragment_shader_file.close();
		}
		catch (std::ifstream::failure& e)
		{
			spdlog::error("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: {}", e.what());
			spdlog::error("Vertex shader file: {}", vs_file);
			spdlog::error("Fragment shader file: {}", fs_file);
			error_status = true;
			return;
		}

		std::string vertex_code = vertex_shader_stream.str();
		std::string fragment_code = fragment_shader_stream.str();
		const char* vertex_shader_code = vertex_code.c_str();
		const char* fragment_shader_code = fragment_code.c_str();

		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertex_shader_code, nullptr);
		glCompileShader(vertex);
		CheckCompileErrors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragment_shader_code, nullptr);
		glCompileShader(fragment);
		CheckCompileErrors(fragment, "FRAGMENT");

		shader = glCreateProgram();
		glAttachShader(shader, vertex);
		glAttachShader(shader, fragment);
		glLinkProgram(shader);
		CheckCompileErrors(shader, "PROGRAM");

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		GLenum err = glGetError();
		if (err != GL_NO_ERROR)
		{
			spdlog::error("Shader creation failed: {}", err);
			error_status = true;
		}

		spdlog::info("Successfully created OpenGL shader");
	}

	/**
	* @details
	* Destructor for the ShaderImpl class. Deletes the OpenGL shader program.
	*/
	Shader::ShaderImpl::~ShaderImpl()
	{
		spdlog::info("Destroying OpenGL shader");
		if (shader) glDeleteProgram(shader);
	}

	/**
	* @details
	* Check for shader compilation errors. If there are any, log it with spdlog.
	*/
	void Shader::ShaderImpl::CheckCompileErrors(unsigned int& shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
				spdlog::error(
					"ERROR::SHADER_COMPILATION_ERROR of type: {}\n{}",
					type,
					infoLog);
				error_status = true;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
				spdlog::error(
					"ERROR::PROGRAM_LINKING_ERROR of type: {}\n{}",
					type,
					infoLog);
				error_status = true;
			}
		}
	}

	/**
	* @details
	* Custom shader constructor. Passes the vertex and fragment shader files to
	* the PIMPL implementation.
	*/
	Shader::Shader(const std::string& vs_file, const std::string& fs_file) :
		_impl(make_unique<ShaderImpl>(vs_file, fs_file))
	{}

	/**
	* @details
	* Default shader constructor.
	*/
	Shader::Shader() = default;

	/**
	* @details
	* Default shader destructor.
	*/
	Shader::~Shader() = default;

	/**
	* @details
	* Get the error status of the shader.
	*/
	bool Shader::GetErrorStatus() const
	{
		return _impl->error_status;
	}

	/**
	* @details
	* Get the OpenGL shader ID.
	*/
	GLuint& Shader::GetGLFWShader()
	{
		return _impl->shader;
	}
}