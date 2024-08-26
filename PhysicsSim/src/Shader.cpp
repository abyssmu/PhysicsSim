#include "Scene.h"

namespace Scene
{
	Shader::~Shader() {}

	Shader::Shader(const string& vs_file, const string& fs_file)
	{
		string vertex_code;
		string fragment_code;
		ifstream vertex_shader_file;
		ifstream fragment_shader_file;
		stringstream vertex_shader_stream;
		stringstream fragment_shader_stream;

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

			vertex_code = vertex_shader_stream.str();
			fragment_code = fragment_shader_stream.str();
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_READ: " << e.what() << std::endl;
		}

		vertex_code = vertex_shader_stream.str();
		fragment_code = fragment_shader_stream.str();

		const char* vertex_shader_code = vertex_code.c_str();
		const char* fragment_shader_code = fragment_code.c_str();

		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertex_shader_code, NULL);
		glCompileShader(vertex);
		CheckCompileErrors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragment_shader_code, NULL);
		glCompileShader(fragment);
		CheckCompileErrors(fragment, "FRAGMENT");

		_shader = glCreateProgram();
		glAttachShader(_shader, vertex);
		glAttachShader(_shader, fragment);
		glLinkProgram(_shader);
		CheckCompileErrors(_shader, "PROGRAM");

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void Shader::Terminate()
	{
		glDeleteProgram(_shader);
	}

	GLuint& Shader::GetShader()
	{
		return _shader;
	}

	void Shader::CheckCompileErrors(unsigned int shader, std::string type) const
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
}