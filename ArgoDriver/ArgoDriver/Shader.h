//#ifndef SHADER_H
//#define SHADER_H
//
//#include <string>
//#include <fstream>
//#include <sstream>
//#include <iostream>
//
//#include <GL/glew.h>
//
//class Shader
//{
//public:
//
//	GLuint ID;
//	GLuint Program;
//	Shader() {}
//	// Constructor generates the shader on the fly
//	Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
//	{
//		// 1. Retrieve the vertex/fragment source code from filePath
//		std::string vertexCode;
//		std::string fragmentCode;
//		std::ifstream vShaderFile;
//		std::ifstream fShaderFile;
//		// ensures ifstream objects can throw exceptions:
//		vShaderFile.exceptions(std::ifstream::badbit);
//		fShaderFile.exceptions(std::ifstream::badbit);
//		try
//		{
//			// Open files
//			vShaderFile.open(vertexPath);
//			fShaderFile.open(fragmentPath);
//			std::stringstream vShaderStream, fShaderStream;
//			// Read file's buffer contents into streams
//			vShaderStream << vShaderFile.rdbuf();
//			fShaderStream << fShaderFile.rdbuf();
//			// close file handlers
//			vShaderFile.close();
//			fShaderFile.close();
//			// Convert stream into string
//			vertexCode = vShaderStream.str();
//			fragmentCode = fShaderStream.str();
//		}
//		catch (std::ifstream::failure e)
//		{
//			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
//		}
//		const GLchar* vShaderCode = vertexCode.c_str();
//		const GLchar * fShaderCode = fragmentCode.c_str();
//		// 2. Compile shaders
//		GLuint vertex, fragment;
//		GLint success;
//		GLchar infoLog[512];
//		// Vertex Shader
//		vertex = glCreateShader(GL_VERTEX_SHADER);
//		glShaderSource(vertex, 1, &vShaderCode, NULL);
//		glCompileShader(vertex);
//		// Print compile errors if any
//		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
//		if (!success)
//		{
//			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
//			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//		}
//		// Fragment Shader
//		fragment = glCreateShader(GL_FRAGMENT_SHADER);
//		glShaderSource(fragment, 1, &fShaderCode, NULL);
//		glCompileShader(fragment);
//		// Print compile errors if any
//		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
//		if (!success)
//		{
//			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
//			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//		}
//		// Shader Program
//		this->Program = glCreateProgram();
//		glAttachShader(this->Program, vertex);
//		glAttachShader(this->Program, fragment);
//		glLinkProgram(this->Program);
//		// Print linking errors if any
//		glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
//		if (!success)
//		{
//			glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
//			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//		}
//		// Delete the shaders as they're linked into our program now and no longer necessery
//		glDeleteShader(vertex);
//		glDeleteShader(fragment);
//
//	}
//	// Uses the current shader
//	void Use()
//	{
//		glUseProgram(this->Program);
//	}
//};
//
//#endif


#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace std;

class Shader
{
public:
	GLuint ID;

	Shader() { }

	Shader & Use();

	void Compile(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *geometrySource = nullptr);

	void SetFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
	void SetInteger(const GLchar *name, GLint value, GLboolean useShader = false);
	void SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
	void SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
	void SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	void SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
	void SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	void SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
	void SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);

private:
	void CheckCompileErrors(GLuint object, std::string type);
};

#endif