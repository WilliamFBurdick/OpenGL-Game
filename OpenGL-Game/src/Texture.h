#pragma once

#include <glad/glad.h>

class Texture2D
{
public:
	unsigned int ID;
	unsigned int Width, Height;
	unsigned int Internal_Format, Image_Format;

	unsigned int Wrap_S, Wrap_T;
	unsigned int Filter_Min, Filter_Max;

	Texture2D();
	void Generate(unsigned int width, unsigned int height, unsigned char* data);
	void Bind() const;
};

