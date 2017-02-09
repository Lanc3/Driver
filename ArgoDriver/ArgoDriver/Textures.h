#pragma once

#ifndef TEXTURES_H
#define TEXTURES_H

#include <GL/glew.h>
#include <iostream>

class Textures
{
public:
	GLuint ID;

	GLuint Width;
	GLuint Height;

	GLuint Internal_Format;
	GLuint Image_Format;

	GLuint Wrap_S;
	GLuint Wrap_T;

	GLuint Filter_Min;
	GLuint Filter_Max;

	Textures();

	void Generate(GLuint width, GLuint height, unsigned char* data);

	void Bind() const;
};


#endif 
