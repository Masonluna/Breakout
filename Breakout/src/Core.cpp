
#include "Core.h"
#include "Log.h"

void Breakout::GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool Breakout::GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError()) {
		BK_ERROR("{0}", error);
		return false;
	}

	return true;
}