#pragma once

#include <windows.h>
#include <gl/GL.h>
#include <string>

class Cubemap
{
public:
	Cubemap(std::string);
	~Cubemap();

	GLuint textureId;
};

